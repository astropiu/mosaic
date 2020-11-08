#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <chrono>
#include <string>
using namespace cv;
using namespace std;
using namespace cv::dnn;
using namespace std::chrono;

float confidenceThreshold = 0.7;
String modelConfiguration = "data/deploy.prototxt";
String modelweights = "data/res10_300x300_ssd_iter_140000.caffemodel";
const size_t inWidth = 300;
const size_t inHeight = 300;
const double inScaleFactor = 1.0;
const Scalar meanVal(104.0, 177.0, 123.0);
dnn::Net net;
void resize_face(Mat &frame, int xlt , int ylt, int xrb , int yrb , Size res_size){

}
int main(){
    dnn::Net net = readNetFromCaffe(modelConfiguration, modelweights);
    net.setPreferableBackend(DNN_BACKEND_CUDA);
    net.setPreferableTarget(DNN_TARGET_CUDA);
    auto start = high_resolution_clock::now();
    for (int i=1;i<933;i++){
    String name= "images/loe" + to_string(i) + ".jpg";
    Mat frame = imread(name);
    
    
    Mat inblob= blobFromImage(frame,inScaleFactor,Size(inWidth,inHeight),meanVal,false,false);
    net.setInput(inblob, "data");
    Mat detection= net.forward("detection_out");
    //cout<<detection.size;

     Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

        for(int i = 0; i < detectionMat.rows; i++)
        {
            float confidence = detectionMat.at<float>(i, 2);

            if(confidence > confidenceThreshold)
            {
                int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

               
            }
        }}
       auto stop= high_resolution_clock::now();
       auto duration = duration_cast<microseconds>(stop-start);
       cout<< '\n'<<duration.count()<<"ms";
    }


