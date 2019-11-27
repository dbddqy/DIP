//
// Created by yue on 26.11.19.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat nearestNeighborInterpolation(Mat rawImage, float scaleFactor){
    int rows = (int)(rawImage.rows*scaleFactor);
    int cols = (int)(rawImage.cols*scaleFactor);
    int channels = rawImage.channels();
    Mat newImage(rows, cols, rawImage.type());
    for (int i = 0; i < rows; ++i) {
        uchar *p = newImage.ptr<uchar>(i);
        for (int j = 0; j < cols; ++j) {
            float index_i = float(i) / scaleFactor;
            float index_j = float(j) / scaleFactor;
            int index_i_floor = floor(index_i);
            int index_j_floor = floor(index_j);
            Vec3b oldPixel = rawImage.at<Vec3b>(index_i_floor, index_j_floor);
            p[j*channels] = oldPixel[0];
            p[j*channels+1] = oldPixel[1];
            p[j*channels+2] = oldPixel[2];
        }
    }
    return newImage;
}

Mat bilinearInterpolation(Mat rawImage, float scaleFactor){
    int rows = (int)(rawImage.rows*scaleFactor);
    int cols = (int)(rawImage.cols*scaleFactor);
    int channels = rawImage.channels();
    Mat newImage(rows, cols, rawImage.type());
    for (int i = 0; i < rows; ++i) {
        uchar *p = newImage.ptr<uchar>(i);
        for (int j = 0; j < cols; ++j) {
            float index_i = float(i) / scaleFactor;
            float index_j = float(j) / scaleFactor;
            int index_i_floor = floor(index_i);
            int index_j_floor = floor(index_j);
            Vec3b oldPixel = rawImage.at<Vec3b>(index_i_floor, index_j_floor);
            p[j*channels] = oldPixel[0];
            p[j*channels+1] = oldPixel[1];
            p[j*channels+2] = oldPixel[2];
        }
    }
    return newImage;
}

int main()
{
    Mat myImage = imread("../../images/01.jpg");
    cout << "size before scaling" << myImage.size << endl;
    Mat newImage = nearestNeighborInterpolation(myImage, 1.2);
    cout << "size after scaling" << newImage.size << endl;

    imshow("myImage", myImage);
    imshow("newImage", newImage);
    waitKey(0);
    return 0;
}