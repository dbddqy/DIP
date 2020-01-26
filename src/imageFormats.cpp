//
// Created by yue on 26.01.20.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat myImage = (Mat_<uint16_t>(3, 3)
            << 8, 0, 65533
            , 0, 8, 2397
            , 0, 0, 1);
//    Mat myImage2Save(myImage.rows, myImage.cols, CV_8UC1, myImage.data);
    imwrite("../../images/myImage.png", myImage);
    cout << myImage.type() << endl;

    Mat img = imread("../../images/myImage.png", -1);
    cout << img << endl;
    cout << img.type() << endl;
    return 0;
}