//
// Created by yue on 14.01.20.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>

using namespace std;
using namespace cv;

void useHough(Mat img, Mat &originalImg) {
    // detect lines
    vector<cv::Vec2f> lines;
    HoughLines(img, lines, 1.0, 1.0*CV_PI/180, 100);
    vector<cv::Vec2f>::const_iterator it= lines.begin();
    while (it!=lines.end())
    {
        float rho= (*it)[0]; // first element is distance rho
        float theta= (*it)[1]; // second element is angle theta
        if (theta < CV_PI/4. || theta > 3.*CV_PI/4.)// ~vertical line
        {
            // point of intersection of the line with first row
            Point pt1(rho/cos(theta), 0);
            // point of intersection of the line with last row
            Point pt2((rho - img.rows * sin(theta))/cos(theta), img.rows);
            // draw a white line
            line( originalImg, pt1, pt2, cv::Scalar(255), 1);
        }
        else
        { // ~horizontal line
            // point of intersection of the
            // line with first column
            Point pt1(0,rho/sin(theta));
            // point of intersection of the line with last column
            Point pt2(img.cols, (rho - img.cols * cos(theta))/sin(theta));
            // draw a white line
            line(originalImg, pt1, pt2, Scalar(255), 1);
        }
        ++it;
    }
}

void useHoughP(Mat img, Mat &originalImg) {
    vector<cv::Vec4i> lines;
    HoughLinesP(img, lines, 1.0, 1.0*CV_PI/180, 110,  50.0, 100.0);
    std::vector<cv::Vec4i>::const_iterator it = lines.begin();
    while (it != lines.end())
    {
        cv::Point pt1((*it)[0], (*it)[1]);
        cv::Point pt2((*it)[2], (*it)[3]);
        cv::line( originalImg, pt1, pt2, Scalar(0, 0, 255), 1);
        ++it;
    }
}

int main() {
    Mat img = imread("../../images/thick_lines01.png");
    Mat originalImg = img.clone();
    cvtColor(img, img, CV_BGR2GRAY);
//    GaussianBlur(img, img, Size(9, 9), 2);
//    Canny(img, img, 80, 240);
    threshold(img, img, 200, 255, THRESH_BINARY_INV);
    ximgproc::thinning(img, img, ximgproc::THINNING_GUOHALL);
    useHough(img, originalImg);

    imshow("img", originalImg);
    waitKey(0);
    return 0;
}
