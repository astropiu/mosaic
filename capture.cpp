#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <iostream>
#include <string>
#include "isface.h"
using namespace cv;
using namespace std;
using namespace cv::dnn;
//using namespace cv::chrono;

int main(){
    String name,pref,path;
    int per_video_frames,freq,imgs_count=0;
    double fcount;
    VideoCapture vc;
    Mat frame;
    bool suc,success;
    std::string modelConfiguration = "data/deploy.prototxt";
    std::string modelweights = "data/res10_300x300_ssd_iter_140000.caffemodel";
    Net net = cv::dnn::readNetFromCaffe(modelConfiguration, modelweights);
    net.setPreferableBackend(DNN_BACKEND_CUDA);
    net.setPreferableTarget(DNN_TARGET_CUDA);
    #ifdef timer
    auto start = high_resolution_clock::now();
    #endif
    for(int j=1;j<=13;j++){
       
        vc.release();
        pref="../life on earth/";
        name="loe"+to_string(j)+".avi";
        path=pref+name;
        bool vcopen=vc.open(path);
        if(!vcopen)
          return -1;
        fcount=vc.get(CAP_PROP_FRAME_COUNT);
        per_video_frames = static_cast<int>(5000/13);
        freq = static_cast<int>(fcount/per_video_frames);
        for(int i = freq; i<fcount; i+=freq){
            vc.set(CAP_PROP_POS_FRAMES,i);
            suc=vc.read(frame); 
            success= false; 
            if(isface(frame,net,success)&& success)
                 imwrite("faces/loe"+to_string( ++imgs_count)+".jpg",frame);
            else {
                resize(frame,frame,Size(184,104));
                imwrite("nonfaces/loe"+to_string( ++imgs_count)+".jpg",frame);
                }
            
            }

        }
      #ifdef timer
       auto stop= high_resolution_clock::now();
       auto duration = duration_cast<microseconds>(stop-start);
       cout<< '\n'<<duration.count()<<"ms";
      #endif
    
}