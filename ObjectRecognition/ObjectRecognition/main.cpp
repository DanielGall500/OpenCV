//
//  main.cpp
//  ObjectRecognition
//
//  Created by Daniel Gallagher on 17/03/2016.
//  Copyright (c) 2016 Developer Co. All rights reserved.
//


#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    VideoCapture cap(0); //capture the video from webcam
    
    if (!cap.isOpened())
    {
        cout << "Cannot open the webcam" << endl;
        return -1;
    }
    
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called control
    
    int iLowH = 0, iHighH = 179;
    
    int iLowS = 0, iHighS = 255;
    
    int iLowV = 0, iHighV = 255;
    
    cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", "Control", &iHighH, 179);
    
    cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &iHighS, 255);
    
    cvCreateTrackbar("LowV", "Control", &iLowH, 255); //Hue (0 - 255)
    cvCreateTrackbar("HighV", "Control", &iHighH, 255);
    
    while(true)
    {
        Mat imgOriginal;
        
        bool bSuccess = cap.read(imgOriginal); //read a new frame from the video
        
        if(!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }
        
        Mat imgHSV;
        
        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //converts the captured frame from BGR to HSV
        
        Mat imgThresholded;
        
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
        
        //morphological opening (remove small objects from the foreground)
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        
        //morhpological closing (fill small holes inthe foreground)
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        
        imshow("Thresholded Image", imgThresholded); // show the thresholded image
        imshow("Original", imgOriginal); // show the original image
        
        if(waitKey(30) == 27) //wait for escape key
        {
            cout << "Escape key pressed by user" << endl;
            break;
        }
        
    }
    
    return 0;
    
}






















