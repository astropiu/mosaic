#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace cv;
using namespace std;

const int hx=23;
const int hy = 13;
const int img_count=4994;
int main(){
    Mat src= imread("med.jpg");
    #ifdef hsv
    cvtColor(src,src,COLOR_BGR2HSV);
    #endif
    array<short,img_count> fi = {0};
    ifstream myf("face_indices.txt");
    int c,count=0;
    while(myf>>c){
        fi[c-1]=1;
        count++;
    }
    
    int src_hx=size(src).width;
    int src_hy= size(src).height;
    int sc=4;
    Mat dest = Mat(src_hy*sc,src_hx*sc,CV_8UC3);
    int nox = (src_hx)/hx;
    int noy= (src_hy)/hy;
    //cout<<nox<<noy;
    ///*
    array <Mat,img_count> imgs,imgso;
    for (int k=0; k<img_count; k++){
        String path= "combined/loe"+to_string(k+1)+".jpg";
        imgs[k]= imread(path);
        medianBlur(imgs[k],imgs[k],3);
        imgs[k].copyTo(imgso[k]);
        resize(imgso[k],imgso[k],Size(hx*sc,hy*sc));
        resize(imgs[k],imgs[k],Size(hx,hy));
       
        #ifdef hsv
        cvtColor(imgs[k],imgs[k],COLOR_BGR2HSV);
        #endif
    }
    int min_index[nox][noy];
    Mat frame,outframe,diff;
    Scalar su;
    double mindiff,score;
    for (int i=0; i<nox; i++){
        for (int j=0; j< noy; j++){
            frame=src(Rect(i*hx,j*hy,hx,hy));
            outframe=dest(Rect(i*hx*sc,j*hy*sc,hx*sc,hy*sc));
            mindiff= INFINITY;
            for(int k=0; k<img_count; k++){
                absdiff(frame,imgs[k],diff);
                su=sum(diff);
                score = su[0]+su[1]+su[2];
                //checking if its face 
                if(fi[k]==1)
                    score*=.4;
                if(score<mindiff){
                    mindiff=score;
                    min_index[i][j]=k;
                 }
             }
             imgso[min_index[i][j]].copyTo(outframe);
        }

    }
    #ifdef hsv
    cvtColor(dest,dest,COLOR_HSV2BGR);
    #endif
    imwrite("final.jpg",dest);
    //*/
}