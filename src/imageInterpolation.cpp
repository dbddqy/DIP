//
// Created by yue on 26.11.19.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    cout << CV_VERSION << endl;
    Mat myImage = imread("../../images/01.jpg");
    imshow("myImage", myImage);
    waitKey(0);
    return 0;
}