//
//  main.cpp
//  OpenCVTest
//
//  Created by Daniel Gallagher on 16/03/2016.
//  Copyright (c) 2016 Developer Co. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

Mat paintingImage, img_gray;
Mat dst, detectedEdges;

int edgeThresh = 1;
int lowThreshold;
const int max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
std::string windowName = "Edge map";

void CannyThreshold(int, void*)
{
    //Reduce noise with a kernel 3x3
    blur(img_gray, detectedEdges, Size(3,3));
    
    Canny(detectedEdges, detectedEdges, lowThreshold, lowThreshold*ratio, kernel_size);
    
    dst = Scalar::all(0); //convert a dst image to all zeros (completely zeros)
    
    paintingImage.copyTo(dst, detectedEdges); // maps only areas that are edges onto picture
    imshow(windowName, dst);
}

int main(int, char**)
{
    std::string paintingName = "/Users/dannyg/Desktop/OpenCV/OpenCVTest/Resources/StarryNightRGB.jpg";
    
    paintingImage = imread(paintingName);
    
    if (!paintingImage.data)
        return -1;
    
    dst.create(paintingImage.size(), paintingImage.type());
    
    cvtColor(paintingImage, img_gray, CV_BGR2GRAY);
    
    namedWindow(paintingName, CV_WINDOW_AUTOSIZE);
    //namedWindow("Gray painting", WINDOW_AUTOSIZE);
    
    createTrackbar("Min threshold: ", windowName, &lowThreshold, max_lowThreshold, CannyThreshold);
    
    CannyThreshold(0, 0);
    
    RNG rng(12345);
    int maxClusters = 5;
    
    for(;;)
    {
        Scalar colourTab[] =
        {
            Scalar(0, 0, 255),
            Scalar(0, 255, 0),
            Scalar(255, 100, 100),
            Scalar(255, 0, 255),
            Scalar(0, 255, 255),
        };
        
        int k, clusterCount = rng.uniform(2,maxClusters+1);
        int i, sampleCount = rng.uniform(1,1001);
        
        Mat points(sampleCount, 1, CV_32FC2), labels;
        
        clusterCount = MIN(clusterCount,sampleCount);
        
        Mat centers;
        
        for (k = 0;k < clusterCount;k++)
        {
            Point center;
            center.x = rng.uniform(0, paintingImage.cols);
            center.y = rng.uniform(0, paintingImage.rows);
            
            Mat pointChunk = points.rowRange(k*samp]leCount/clusterCount,
                                             k == clusterCount?
                                             sampleCount : (k+1)*sampleCount/clusterCount);
            
            rng.fill(pointChunk, RNG::NORMAL, Scalar(center.x, center.y),
                     Scalar(paintingImage.cols*0.05, paintingImage.rows*0.05));
        }
        randShuffle(points, 1, &rng);
        
        kmeans(points, clusterCount, labels, TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 10, 1.0), 3, KMEANS_PP_CENTERS, centers);
        
        //paintingImage = Scalar::all(0);
        
        for(i = 0; i < sampleCount; i++)
        {
            int clusterIdx = labels.at<int>(i);
            Point ipt = points.at<Point2f>(i);
            circle(paintingImage, ipt, 2, colourTab[clusterIdx], FILLED, LINE_AA);
        }
        
        imshow("Clusters", paintingImage);
    }
    
    waitKey(0);
    
    return 0;
    
}






