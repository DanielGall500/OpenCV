//
//  main.cpp
//  OpenCVTest
//
//  Created by Daniel Gallagher on 16/03/2016.
//  Copyright (c) 2016 Developer Co. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat src, src_gray;
Mat dst, detectedEdges;

int edgeThresh = 1;
int lowThreshold;
const int max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
std::string windowName = "Edge map";

int main(int, char**)
{
    std::string paintingName = "/Users/dannyg/Desktop/OpenCV/OpenCVTest/Resources/StarryNightRGB.jpg";
    
    Mat paintingImage = imread(paintingName, 1);
    
    Mat gray_painting;
    cvtColor(paintingImage, gray_painting, COLOR_BGR2GRAY);
    
    imwrite("/Users/dannyg/Desktop/OpenCV/OpenCVTest/Resources/Grayscale_StarryNight.jpg", gray_painting);
    
    namedWindow(paintingName, WINDOW_AUTOSIZE);
    namedWindow("Gray painting", WINDOW_AUTOSIZE);
    
    imshow(paintingName, paintingImage);
    imshow("Grey painting", gray_painting);
    
    waitKey(0);
    
    return 0;
    
}