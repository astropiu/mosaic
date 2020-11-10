#include "isface.h"
#include <exception>
using namespace cv;
using namespace std;
using namespace cv::dnn;

float confidenceThreshold = 0.8;
int img_height = 416, img_width = 720;
const size_t inWidth = 300;
const size_t inHeight = 300;
const double inScaleFactor = 1.0;
const cv::Scalar meanVal(104.0, 177.0, 123.0);
auto req_size = cv::Size(184,104);
int xLeftTop,yLeftTop,xRightBottom,yRightBottom;

bool resize_face(Mat &frame){
    int height,width;
    height=yRightBottom-yLeftTop;
    width= xRightBottom-xLeftTop;
    if(xLeftTop>0 && xLeftTop<img_width && yLeftTop>0 && yLeftTop<img_height && xRightBottom >0 && xRightBottom < img_width && yRightBottom >0 && yRightBottom < img_width){
    if(height>=52 && width >= 90 && xLeftTop>65 && yLeftTop>25 && (xLeftTop+width+130)<img_width && (yLeftTop+height+50)<img_height){
    try{
    Rect object((int)(xLeftTop-65), (int)(yLeftTop-25),int(width+130),int(height+50));
    frame = frame(object);
    resize(frame,frame,req_size);
    return true;}
    catch(Exception ex){
     cout << xLeftTop << '\t'<< yLeftTop <<'\t'<< xRightBottom << '\t' << yRightBottom << '\n';   
        }
      }}
    return false;
    }

bool isface(Mat &frame,Net &net,bool &success){
   
   
    Mat inblob= cv::dnn::blobFromImage(frame,inScaleFactor,Size(inWidth,inHeight),meanVal,false,false);
    net.setInput(inblob, "data");
    Mat detection= net.forward("detection_out");
    //cout<<detection.size;

    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    for(int i = 0; i < detectionMat.rows; i++)
        {
            float confidence = detectionMat.at<float>(i, 2);
            if(confidence > confidenceThreshold)
            {
                xLeftTop = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
                yLeftTop = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
                xRightBottom = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
                yRightBottom = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
                //cout << xLeftTop << '\t'<< yLeftTop <<'\t'<< xRightBottom << '\t' << yRightBottom << '\n';
                success=resize_face(frame);
                return true;
               
            }
        }
      
    return false;
    }


