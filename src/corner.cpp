//
// Created by yue on 11.01.20.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void useFast(Mat &img, int threshold) {
    vector<KeyPoint> keyPoints;
    FAST(img, keyPoints, threshold, true);
    drawKeypoints(img, keyPoints, img, Scalar::all(255), DrawMatchesFlags::DRAW_OVER_OUTIMG);
    cout << keyPoints.size() << " corner points detected." << endl;
}

int main() {
    Mat img = imread("../../images/piece05_1200x900.jpg");
    cvtColor(img, img, CV_BGR2GRAY);
    medianBlur(img, img, 5);

    useFast(img, 40);
    imshow("img", img);
    waitKey(0);
    return 0;
}
