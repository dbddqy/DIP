//
// Created by yue on 29.11.19.
//

#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat myImage = imread("../../images/01.jpg");
    Mat mask = Mat::zeros(myImage.size(), CV_8UC1);

    Rect r1(0, 256, 256, 512);
    Rect r2(600, 50, 128, 128);
    mask(r1).setTo(255);
    mask(r2).setTo(255);

    Mat imageWithMask;
    myImage.copyTo(imageWithMask, mask);

    imshow("myImageRaw", myImage);
    imshow("imageWithMask", imageWithMask);
    imshow("mask", mask);
    waitKey(0);
    return 0;
}