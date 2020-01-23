//
// Created by yue on 29.11.19.
//

#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/ximgproc.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

using namespace std;
using namespace cv;
using namespace Eigen;

int main()
{
    Mat myImage = imread("../../images/piece01_1200x900.jpg");
    Mat myImageGrey;
    cvtColor(myImage, myImageGrey, CV_BGR2GRAY);
    Mat dst_blur, dst_blur_median, dst_filter2d, dst_laplacian, dst_sobel, dst_diffusion;
    blur(myImageGrey, dst_blur, Size(5, 5));
    medianBlur(myImageGrey, dst_blur_median, 5);
    Laplacian(myImageGrey, dst_laplacian, -1, 3);
    Sobel(myImageGrey, dst_sobel, -1, 1, 0, 3);
    ximgproc::anisotropicDiffusion(myImage, dst_diffusion, 0.15, 100, 10);

    Matrix<char, 3, 3> m;
    m << 0, 1, 0, 1, -4, 1, 0, 1, 0; // Laplacian filter
    m << -1, -1, -1, -1, 9, -1, -1, -1, -1; // Laplacian filter
    m << -1, -2, -1, 0, 0, 0, 1, 2, 1; // Sobel filter x_dir
//    m.fill(1.0/9);
    Mat kernel;
    eigen2cv(m, kernel);
    cout << typeToString(kernel.type());
    filter2D(myImageGrey, dst_filter2d, -1, kernel);

    imshow("myImageGrey", myImageGrey);
//    imshow("dst_blur", dst_blur);
//    imshow("dst_blur_median", dst_blur_median);
    imshow("dst_laplacian", dst_laplacian);
    imshow("dst_sobel", dst_sobel);
    imshow("dst_filter2d", dst_filter2d);
    imshow("dst_diffusion", dst_diffusion);
    waitKey(0);
    return 0;
}