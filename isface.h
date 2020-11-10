#if !defined isfacee
#define isfacee
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <chrono>
#include <string>
/*using namespace cv;
using namespace std;

using namespace std::chrono;*/
using namespace cv::dnn;



bool resize_face(cv::Mat &frame);
bool isface(cv::Mat &frame,Net &net, bool &success);


#endif