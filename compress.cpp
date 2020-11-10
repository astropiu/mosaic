#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
using namespace cv;
int main(){
    Mat img= imread("final.png");
    std::vector<int>params;
    params.push_back(IMWRITE_JPEG_QUALITY);
    params.push_back(10);
    cv::imwrite("compressed.jpeg",img,params);


}