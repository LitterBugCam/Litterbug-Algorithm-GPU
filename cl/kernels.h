#ifndef KERNELS_H
#define KERNELS_H
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class openCl
{
private:

public:
    openCl();
    void atan2(cv::Mat&x, cv::Mat& y, cv::Mat& angle);
};


#define CATCHCL catch(cl::Error& err) {std::cerr << __FILE__ << " at " << __LINE__<<": "<<err.what() <<", code: "<<err.err()<<std::endl; exit(255);}


#endif // KERNELS_H
