//
// Created by yue on 26.11.19.
//

#include <iostream>
#include <time.h>
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
            uchar *pNew = rawImage.ptr<uchar>(index_i_floor);
            p[j*channels] = pNew[index_j_floor*channels];
            p[j*channels+1] = pNew[index_j_floor*channels+1];
            p[j*channels+2] = pNew[index_j_floor*channels+2];
        }
    }
    return newImage;
}

Mat bilinearInterpolation(Mat rawImage, float scaleFactor){
    int rows = (int)(rawImage.rows*scaleFactor);
    int cols = (int)(rawImage.cols*scaleFactor);
    int ch = rawImage.channels(); // channels
    Mat newImage(rows, cols, rawImage.type());
    for (int i = 0; i < rows; ++i) {
        uchar *p = newImage.ptr<uchar>(i);
        for (int j = 0; j < cols; ++j) {
            float index_i = float(i) / scaleFactor;
            float index_j = float(j) / scaleFactor;
            int i_f = floor(index_i); // index_i_floor
            int j_f = floor(index_j); // index_j_floor
            float u = index_i - i_f; // remainder row
            float v = index_j - j_f; // remainder column
            uchar *pRaw = rawImage.ptr<uchar>(i_f);
            uchar *pRawNext = rawImage.ptr<uchar>(i_f + 1);
            for (int k = 0; k < ch; ++k)
                p[j*ch+k] = pRaw[j_f*ch+k]*(1-u)*(1-v) + pRaw[(j_f+1)*ch+k]*(1-u)*v
                    + pRawNext[j_f*ch+k]*u*(1-v) + pRawNext[(j_f+1)*ch+k]*u*v;
        }
    }
    return newImage;
}

int main()
{
    clock_t start, end;
    Mat myImage = imread("../../images/01.jpg");
    cout << "size before scaling: " << myImage.size << endl;

    start = clock();
    Mat newImage = bilinearInterpolation(myImage, 1.2);
//    Mat newImage;
//    resize(myImage, newImage, Size(360, 216), (0, 0), (0, 0), INTER_CUBIC);
    end = clock();
    cout << "size after scaling: " << newImage.size << " time used: " << (double)(end-start)/CLOCKS_PER_SEC << endl;

    imshow("myImage", myImage);
    imshow("newImage", newImage);
    waitKey(0);
    return 0;
}