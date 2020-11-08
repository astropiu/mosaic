#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>
#include <string_view>
using namespace cv;
using namespace std;


int main(){
    String name,pref,path;
    int per_video_frames,freq,imgs_count=0;
    double fcount;
    VideoCapture vc;
    Mat frame;
    for(int i=1;i<=13;i++){
        vc.release();
        pref="../life on earth/";
        name="loe"+to_string(i)+".avi";
        path=pref+name;
        bool vcopen=vc.open(path);
        if(!vcopen)
          return 1;
        fcount=vc.get(CAP_PROP_FRAME_COUNT);
        per_video_frames = static_cast<int>(5000/13);
        freq = static_cast<int>(fcount/per_video_frames);
        for(int i = freq; i<fcount; i+=freq){
            vc.set(CAP_PROP_POS_FRAMES,i);
            bool suc=vc.read(frame);  
            if(isface(frame))
                 imwrite("faces/loe"+to_string( ++imgs_count)+".jpg",frame);
            else {
                resize_frame(frame);
                imwrite("images/loe"+to_string( ++imgs_count)+".jpg",frame);
            }
            
    }

    }
}