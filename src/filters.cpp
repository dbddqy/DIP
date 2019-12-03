//
// Created by yue on 29.11.19.
//

#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

using namespace std;
using namespace cv;
using namespace Eigen;

int main()
{
    Mat myImage = imread("../../images/piece01_1200x900.jpg");
    cvtColor(myImage, myImage, CV_BGR2GRAY);
    Mat dst_blur, dst_blur_median, dst_filter2d, dst_laplacian, dst_sobel;
    blur(myImage, dst_blur, Size(5, 5));
    medianBlur(myImage, dst_blur_median, 5);
    Laplacian(myImage, dst_laplacian, -1, 3);
    Sobel(myImage, dst_sobel, -1, 1, 0, 3);

    Matrix<char, 3, 3> m;
    m << 0, 1, 0, 1, -4, 1, 0, 1, 0; // Laplacian filter
    m << -1, -1, -1, -1, 9, -1, -1, -1, -1; // Laplacian filter
    m << -1, -2, -1, 0, 0, 0, 1, 2, 1; // Sobel filter x_dir
//    m.fill(1.0/9);
    Mat kernel;
    eigen2cv(m, kernel);
    cout << typeToString(kernel.type());
    filter2D(myImage, dst_filter2d, -1, kernel);

    imshow("myImage", myImage);
//    imshow("dst_blur", dst_blur);
//    imshow("dst_blur_median", dst_blur_median);
    imshow("dst_laplacian", dst_laplacian);
    imshow("dst_sobel", dst_sobel);
    imshow("dst_filter2d", dst_filter2d);
    waitKey(0);
    return 0;
}