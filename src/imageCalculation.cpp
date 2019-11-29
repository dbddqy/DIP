//
// Created by yue on 29.11.19.
//

#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat myInversion(Mat rawImage){
    return Vec3b(255, 255, 255) - rawImage;
}

Mat myLog(Mat rawImage){
    Mat dst;
    rawImage.convertTo(dst, CV_32FC3);
    log(Vec3f(1., 1., 1.)+dst, dst);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    dst.convertTo(dst, CV_8UC3);
    return dst;
}

Mat myGamma(Mat rawImage, float gamma){
    Mat dst;
    rawImage.convertTo(dst, CV_32FC3);
    pow(dst, gamma, dst);
    normalize(dst, dst, 0, 255, NORM_MINMAX);
    dst.convertTo(dst, CV_8UC3);
    return dst;
}

int main()
{
    clock_t start, end;
    Mat myImage = imread("../../images/01.jpg");

    start = clock();
    Mat newImage = myGamma(myImage, 0.5);
    end = clock();
    cout << "size after scaling: " << newImage.size << " time used: " << (double)(end-start)/CLOCKS_PER_SEC << endl;

    imshow("myImage", myImage);
    imshow("newImage", newImage);
    waitKey(0);
    return 0;
}