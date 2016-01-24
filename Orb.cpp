// Orb.cpp

#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/features2d.hpp>

#include<iostream>
#include<conio.h>           // it may be necessary to change or remove this line if not using Windows

///////////////////////////////////////////////////////////////////////////////////////////////////
int main(void) {

    cv::Mat imgObject = cv::imread("object.png");
    cv::Mat imgScene = cv::imread("scene.png");

    if (imgObject.empty() || imgScene.empty()) {			    // if unable to open image
        std::cout << "error: image not read from file\n\n";		// show error message on command line
        _getch();                    // it may be necessary to change or remove this line if not using Windows
        return(0);												// and exit program
    }

    cv::Ptr<cv::ORB> orb = cv::ORB::create();

    std::vector<cv::KeyPoint> objectKeypoints;
    std::vector<cv::KeyPoint> sceneKeypoints;

    cv::Mat objectDescriptors;
    cv::Mat sceneDescriptors;

    orb->detectAndCompute(imgObject, cv::noArray(), objectKeypoints, objectDescriptors);
    orb->detectAndCompute(imgScene, cv::noArray(), sceneKeypoints, sceneDescriptors);

    cv::BFMatcher bfMatcher;

    std::vector<cv::DMatch> matches;

    bfMatcher.match(objectDescriptors, sceneDescriptors, matches);

    cv::Mat imgFinal;

    cv::drawMatches(imgObject, objectKeypoints, imgScene, sceneKeypoints, matches, imgFinal);

    cv::imshow("imgFinal", imgFinal);

    cv::waitKey(0);

    return(0);

}





