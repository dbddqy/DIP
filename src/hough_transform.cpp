//
// Created by yue on 11.01.20.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#define PI 3.14159265358979

using namespace std;
using namespace cv;

void useHough(Mat &img) {
    // detect lines
    vector<cv::Vec2f> lines;
    HoughLines(img, lines, 3.5, 3.5*PI/180, 125);
    vector<cv::Vec2f>::const_iterator it= lines.begin();
    while (it!=lines.end())
    {
        float rho= (*it)[0]; // first element is distance rho
        float theta= (*it)[1]; // second element is angle theta
        if (theta < PI/4. || theta > 3.*PI/4.)// ~vertical line
        {
            // point of intersection of the line with first row
            cv::Point pt1(rho/cos(theta), 0);
            // point of intersection of the line with last row
            cv::Point pt2((rho - img.rows * sin(theta))/cos(theta), img.rows);
            // draw a white line
            cv::line( img, pt1, pt2, cv::Scalar(255), 1);
        }
        else
        { // ~horizontal line
            // point of intersection of the
            // line with first column
            cv::Point pt1(0,rho/sin(theta));
            // point of intersection of the line with last column
            cv::Point pt2(img.cols, (rho - img.cols * cos(theta))/sin(theta));
            // draw a white line
            cv::line(img, pt1, pt2, Scalar(255), 1);
        }
        ++it;
    }
}

void useHoughP(Mat img, Mat &originalImg) {
    vector<cv::Vec4i> lines;
    HoughLinesP(img, lines, 3.5, 3.5*PI/180, 50,  0.0, 100.0);
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
    Mat img = imread("../../images/piece05_1200x900.jpg");
    Mat originalImg = img.clone();
    cvtColor(img, img, CV_BGR2GRAY);
    GaussianBlur(img, img, Size(9, 9), 2);
    Canny(img, img, 80, 240);
//    threshold(img, img, 3, 50, THRESH_BINARY);
//    cout << img << endl;
//    medianBlur(img, img, 9);
//    Laplacian(img, img, -1, 3);
//    blur(img, img, Size(9, 9));
    useHoughP(img, originalImg);

    imshow("img", originalImg);
    waitKey(0);
    return 0;
}
