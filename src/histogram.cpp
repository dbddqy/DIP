//
// Created by yue on 29.11.19.
//

#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat getHistGreyScale(Mat img){
    const int channels[1]={0};
    const int histSize[1]={256};
    float hranges[2]={0,255};
    const float* ranges[1]={hranges};
    Mat hist;
    calcHist(&img,1,channels,Mat(),hist,1,histSize,ranges);
    return hist;
}

Mat getHistImage(Mat hist){
    Mat histImg(256, 256, CV_8U, Scalar(255));
    double max;
    minMaxLoc(hist, 0, &max);
    for(int h=0; h<256; h++)
    {
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*256/max);
        line(histImg, Point(h, 256), Point(h,256-intensity), Scalar::all(0));
    }
    return histImg;
}

int main()
{
    Mat myImage = imread("../../images/01.jpg");
    cvtColor(myImage, myImage, CV_BGR2GRAY);

    Mat hist = getHistGreyScale(myImage);
    Mat histImg = getHistImage(hist);

    imshow("myImageRaw", myImage);
    imshow("histImg", histImg);
    cout << hist.at<float>(80);
    waitKey(0);
    return 0;
}