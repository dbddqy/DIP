//
// Created by yue on 01.02.20.
//

#include <iostream>
#include <stack>
#include <cassert>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const cv::Point PointShift2D[8] =
        {
                cv::Point(1, 0),
                cv::Point(1, -1),
                cv::Point(0, -1),
                cv::Point(-1, -1),
                cv::Point(-1, 0),
                cv::Point(-1, 1),
                cv::Point(0, 1),
                cv::Point(1, 1)
        };

void grow(cv::Mat& src, cv::Mat& mask, cv::Point seed, int threshold) {
    /* apply "seed grow" in a given seed
     * Params:
     *   src: source image
     *   dest: a matrix records which pixels are determined/undtermined/ignored
     *   mask: a matrix records the region found in current "seed grow"
     */
    stack<cv::Point> point_stack;
    point_stack.push(seed);

    while(!point_stack.empty()) {
        cv::Point center = point_stack.top();
        mask.at<uchar>(center) = 1;
        point_stack.pop();

        for (int i=0; i<8; ++i) {
            cv::Point estimating_point = center + PointShift2D[i];
            if (estimating_point.x < 0
                || estimating_point.x > src.cols-1
                || estimating_point.y < 0
                || estimating_point.y > src.rows-1) {
                // estimating_point should not out of the range in image
                continue;
            } else {
//                uchar delta = (uchar)abs(src.at<uchar>(center) - src.at<uchar>(estimating_point));
                // delta = (R-R')^2 + (G-G')^2 + (B-B')^2
                int delta = int(pow(src.at<cv::Vec3b>(center)[0] - src.at<cv::Vec3b>(estimating_point)[0], 2)
                                + pow(src.at<cv::Vec3b>(center)[1] - src.at<cv::Vec3b>(estimating_point)[1], 2)
                                + pow(src.at<cv::Vec3b>(center)[2] - src.at<cv::Vec3b>(estimating_point)[2], 2));
                if (mask.at<uchar>(estimating_point) == 0
                    && delta < threshold) {
                    mask.at<uchar>(estimating_point) = 1;
                    point_stack.push(estimating_point);
                }
            }
        }
    }
}

int main (){
    Mat img = imread("../../images/piece02_1200x900.jpg");
    Mat dest = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);
    Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    Point p(600, 450);
    grow(img, mask, p, 100);

    Mat imageWithMask;
    img.copyTo(imageWithMask, mask);
    imshow("imageWithMask", imageWithMask);
    waitKey();
}