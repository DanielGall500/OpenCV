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