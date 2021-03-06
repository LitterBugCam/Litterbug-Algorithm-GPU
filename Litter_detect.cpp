#include "edge_grouping.h"
#include "scoring.h"
#include "parameters.h"
#include <map>
#include <functional>
#include "cl/matproxy.h"
#include "cl/kernels.h"
#include <memory>

#ifndef NO_GUI
    #include <opencv/highgui.h>
#endif

//fixme: all those DECLARE_PARAM can be rewritten using C++17 and std::variant
//see here: https://habr.com/post/415737/

//this must be once per program - this allocates actual memory
#define DECLARE_PARAM(TYPE, NAME) TYPE NAME = 0
//important parameters
DECLARE_PARAM(float, staticness_th) ; // Staticness score threshold (degree of the object being static)
DECLARE_PARAM(double, objectness_th); //  Objectness score threshold (probability that the rectangle contain an object)
DECLARE_PARAM(uint8_t, aotime); //aotime*framemod2= number of frames the objects must be  static// if set too low, maybe cause false detections !!
DECLARE_PARAM(uint8_t, aotime2); // Half or more of aotime
DECLARE_PARAM(double, alpha); // background scene learning rate
DECLARE_PARAM(double, fore_th); // Threshold moving edges segmentation


//Less important parameters
DECLARE_PARAM(bool, low_light); // if night scene
DECLARE_PARAM(fullbits_int_t, frameinit); // Frames needed for learning the background
DECLARE_PARAM(fullbits_int_t, framemod);
DECLARE_PARAM(fullbits_int_t, framemod2);
DECLARE_PARAM(fullbits_int_t, minsize); // Static object minimum size
DECLARE_PARAM(float, resize_scale); // Image resize scale
DECLARE_PARAM(float, fps_life); // activeness of candidates = fps * fps_life
#undef DECLARE_PARAM


//and 1 more copy-paste (MUST BE SAME AS ABOVE!) which defines relation between string-name and variables above
#define DECLARE_PARAM(TYPE, NAME) {#NAME, [](const std::string& src){setParam<TYPE>(src, &NAME);}}
const static std::map<std::string, std::function<void(const std::string& src)>> param_setters =
{
    //important parameters
    DECLARE_PARAM(float, staticness_th), // Staticness score threshold (degree of the object being static)
    DECLARE_PARAM(double, objectness_th), //  Objectness score threshold (probability that the rectangle contain an object)
    DECLARE_PARAM(uint8_t, aotime), //aotime*framemod2= number of frames the objects must be  static// if set too low, maybe cause false detections !!
    DECLARE_PARAM(uint8_t, aotime2), // Half or more of aotime
    DECLARE_PARAM(double, alpha), // background scene learning rate
    DECLARE_PARAM(double, fore_th), // Threshold moving edges segmentation


    //Less important parameters
    DECLARE_PARAM(bool, low_light), // if night scene
    DECLARE_PARAM(fullbits_int_t, frameinit), // Frames needed for learning the background
    DECLARE_PARAM(fullbits_int_t, framemod),
    DECLARE_PARAM(fullbits_int_t, framemod2),
    DECLARE_PARAM(fullbits_int_t, minsize), // Static object minimum size
    DECLARE_PARAM(float, resize_scale), // Image resize scale
    DECLARE_PARAM(float, fps_life), // activeness of candidates = fps * fps_life
};
#undef DECLARE_PARAM

std::shared_ptr<openCl> cl(nullptr);

static int align16(int v)
{
    if (v % 16 == 0)
        return v;
    return (1 + v / 16) * 16;
}

static void execute(const char* videopath, std::ofstream& results)
{
    std::cout << "Video file: " << videopath << std::endl;
    cv::VideoCapture capture(videopath);
    const auto framesCount = static_cast<long>(capture.get(CV_CAP_PROP_FRAME_COUNT));
    const auto fps         = std::max(1l, static_cast<long>(capture.get(CV_CAP_PROP_FPS)));
    capture.set(CV_CAP_PROP_BUFFERSIZE, 1);

    cv::Mat image;
    cv::Mat frame;

    capture >> image;
    if (image.empty())
    {
        std::cerr << "Something wrong. 1st frame is empty. Cant continue." << std::endl;
        exit(3);
    }

    if (resize_scale != 1)
        resize(image, image, cv::Size(image.cols * resize_scale, image.rows * resize_scale));


    const auto aw = align16(image.cols);
    const auto ah = align16(image.rows);

    const auto dw = aw - image.cols;
    const auto dh = ah - image.rows;
    const bool useOrigin = (dw == 0) && (dh == 0);


    const static float alpha_init = 0.01;
    auto alpha_S = alpha_init;

    //2nd param shows how long object should live initially (it was 40 by default)
    //however, lets say 1 second of real time video
    objects abandoned_objects(framesCount, fps * std::max(fps_life, 0.01f));

    cv::Mat grad_x, grad_y;
    cv::Mat D_Sx, D_Sy;

    ZeroedArray<uint8_t> canny(0);
    ZeroedArray<uint8_t> object_map(0);
    ZeroedArray<float> angles(0);
    cv::Mat not_used;
#ifndef NO_FPS
    float meanfps = 0;
#endif

    cv::Mat abandoned_map  = cv::Mat(ah, aw, CV_8UC1, cv::Scalar(0));

    for (fullbits_int_t i = 0; !image.empty(); ++i, (capture >> image))
    {
        //const size_t pixels_size    = image.cols * image.rows;
#ifndef NO_FPS
        auto t = static_cast<double>(cv::getTickCount());
#endif
        if (i > frameinit) alpha_S = alpha;
        if (i % framemod != 0 && i > frameinit)
            continue;

        if (resize_scale != 1)
            cv::resize(image, image, cv::Size(aw, ah));

        cv::cvtColor(image, not_used, CV_BGR2GRAY);
        cv::blur(not_used, not_used, cv::Size(3, 3));
        if (low_light)
            not_used = not_used.mul(1.5f);

        //making aligned to 16 width & height
        static cv::Mat aligned(ah, aw, not_used.depth());
        cv::Mat& gray = (useOrigin) ? not_used : aligned;
        if (!useOrigin)
            cv::copyMakeBorder(not_used, aligned, 0, dh, 0, dw, cv::BORDER_CONSTANT, cv::Scalar(0));

        assert(abandoned_map.isContinuous());
        auto plain_map_ptr  = abandoned_map.ptr<uchar>();

        //ok, original sobel + magic takes 550 - 650 ms

        cl->sobel2magic(i % framemod2 == 0, i > frameinit && i % framemod2 == 0, i == 0, alpha_S, fore_th, gray,
                        angles.getStorage(), abandoned_map, canny.getStorage());

        //        {
        //            TimeMeasure tm("Canny only");
        //cv::Canny(gray, canny.getStorage(), 30, 30 * 3, 3); //Canny only took (ms): 156
        //        }


        if (i > frameinit && i % framemod2 == 0)
        {
            for (fullbits_int_t j = 1; j < abandoned_map.rows - 1; ++j)
            {
                plain_map_ptr  += abandoned_map.cols;

                for (fullbits_int_t k = 1; k < abandoned_map.cols - 1; ++k)
                {
                    auto point  = plain_map_ptr + k;
                    //hmm, this code can be removed for test image - same result
                    if (*point > aotime2 && *point < aotime)
                        for (fullbits_int_t c0 = -1; c0 <= 1; ++c0)
                        {
                            if ((c0 && *(point + c0) > aotime) || *(point + abandoned_map.cols + c0) > aotime || *(point - abandoned_map.cols + c0) > aotime ) //excluding c0 = 0 which is meself
                            {
                                *point = aotime;
                                break;
                            }
                        }
                }
            }
        }
        cv::threshold(abandoned_map, frame, aotime, 255, cv::THRESH_BINARY);
        cv::threshold(abandoned_map, object_map.getStorage(), aotime2, 255, cv::THRESH_BINARY);


        abandoned_objects.populateObjects(frame, i);

#ifndef NO_GUI
        //!!!!!!!!!!!!!!VISUAL CONTROL HERE, make copy of needed Mat to frame and comment others
        //! to see pictures of what's going on (to display frame itself - just comment all)
        //abandoned_map.copyTo(frame);
        //image.copyTo(frame);

        canny.getStorage().copyTo(frame);
#endif

        for (auto& atu : abandoned_objects.candidat)
        {
            if (!atu.isTooSmall(minsize))
            {
                es_param_t params = atu.getScoreParams(image.rows, image.cols);
                edge_segments(object_map, angles, canny, params);
                if (params.score > staticness_th && params.circularity > objectness_th && params.circularity < 1000000)
                {
                    //hm, lets do cheat, if we display object then +1 to life
                    atu.extraLife();
                    results << " x: " << params.rr << " y: " << params.cc << " w: " << params.w << " h: " << params.h << std::endl;
#ifndef NO_GUI
                    const static cv::Scalar color(255, 255, 255);
                    cv::rectangle(frame, cv::Rect(atu.origin, atu.endpoint), color, 2);
#endif
                }
            }
        }

#ifndef NO_GUI
#ifndef NO_FPS
        const std::string text = "FPS: " + std::to_string(meanfps / (i + 1)) + ", candidats count: " + std::to_string(abandoned_objects.candidat.size());
#else
        const std::string text = "Candidats count: " + std::to_string(abandoned_objects.candidat.size());
#endif
        cv::putText(frame,
                    text,
                    cv::Point(5, 20), // Coordinates
                    cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                    1.0, // Scale. 2.0 = 2x bigger
                    cv::Scalar(255, 255, 255), // BGR Color
                    1, // Line Thickness
                    CV_AA); // Anti-alias

        cv::imshow("output", frame);
        if (27 == cv::waitKey(10))
            break;
#endif


#ifndef NO_FPS
        t = ((double) cv::getTickCount() - t) / cv::getTickFrequency();
        meanfps =  (1 / t) + meanfps;
        //print out only with no gui
#ifdef NO_GUI
        if (i % 10 == 0 )
            std::cerr << "FPS  " << meanfps / (i + 1) << ", Objects: " << abandoned_objects.candidat.size() << std::endl;
#endif
#endif
    }
}


int main(int argc, char * argv[])
{
    cl = std::make_shared<openCl>();

    std::ofstream results;
    results.open ("detected_litters.txt");
    results << "        detected litters \n\n";
    std::ifstream paramsFile( "parameters.txt" );

    if (!paramsFile.is_open())
    {
        std::cerr << "Cannot load parameters.txt" << std::endl;
        exit(2);
    }

    for (std::string tmp; !paramsFile.eof();)
    {
        std::getline(paramsFile, tmp);
        auto peq = tmp.find_first_of('=');
        if (peq != std::string::npos)
        {
            auto name = trim_copy(tmp.substr(0, peq ));
            auto val  = trim_copy(tmp.substr(peq + 1));
            std::cout << "Parsing: " << name << " = " << val << std::endl;
            if (param_setters.count(name))
                param_setters.at(name)(val);
            else
                std::cerr << "Unknown parameter line: " << tmp << std::endl;
        }
    }

    if (std::abs(fps_life) < 0.00001f)
        fps_life = 40. / 25.; //thats is default test value for my test video

    if (aotime <= aotime2)
    {
        std::cerr << "aotime must be greater then aotime2" << std::endl;
        exit(5);
    }

#ifndef NO_FPS
    std::cout << "Using FPS" << std::endl;
#else
    std::cout << "NOT using FPS" << std::endl;
#endif

#ifndef NO_GUI
    std::cout << "Using GUI" << std::endl;
#else
    std::cout << "NOT using GUI" << std::endl;
#endif
    std::cout.flush();



    const char * videopath = (argc < 2) ? nullptr : argv[1];

    if (!videopath)
    {
        std::cout << "please specify the video path" << std::endl;
        exit(1);
    }
    try
    {
        execute(videopath, results);
    }
    catch (const std::runtime_error& re)
    {
        std::cerr << "Runtime error: " << re.what() << std::endl;
        return 255;
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error occurred: " << ex.what() << std::endl;
        return 255;
    }
    catch (...)
    {
        std::cerr << "Unknown failure occurred. Possible memory corruption" << std::endl;
        return 255;
    }

#ifndef NO_FPS
    std::cout << "All Calculations are done." << std::endl;
#endif
    return 0;
}
