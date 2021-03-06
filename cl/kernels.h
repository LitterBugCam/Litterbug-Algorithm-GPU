#ifndef KERNELS_H
#define KERNELS_H
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

class openCl
{
private:

public:
    openCl();
    void atan2(cv::Mat&x, cv::Mat& y, cv::Mat& angle);
    void sobel2magic(bool is_minus1, bool is_plus2, bool first_run, const float alpha_s, const float fore_th, cv::Mat &gray, cv::Mat& angle, cv::Mat& mapR, cv::Mat &canny);
};


class TimeMeasure
{
private:
    int32_t start;
    std::string text;
public:
    static int32_t now();
    TimeMeasure(std::string&& text):
        text(std::move(text))
    {
        start = now();
    }
    void print()
    {
        std::cout << text << " took (ms): " << now() - start << std::endl;
    }
    ~TimeMeasure()
    {
        print();
    }
};



#define CATCHCL catch(cl::Error& err) {std::cerr << __FILE__ << " at " << __LINE__<<": "<<err.what() <<", code: "<<err.err()<<std::endl; exit(255);}


#endif // KERNELS_H
