#include<opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
int main(){
    Mat src = imread("destination.jpg");
    Mat out;
    resize(src,out,Size(5152,2912));
    imwrite("resized.jpg",out);
    Mat med;
    medianBlur(out,med,9);
    imwrite("med.jpg",med);
}