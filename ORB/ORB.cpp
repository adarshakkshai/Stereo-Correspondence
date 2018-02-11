#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int levels = 0;
int maxlevels = 1;

void on_change(int, void*){
	cout << "Changed" << endl;
	}

int main(int arg, char * argcv[]){

int nfeatures=500;
float scaleFactor=1.2f; 
int nlevels=8; 
int edgeThreshold=31; 
int firstLevel=0; 
int WTA_K=2; 
int scoreType=ORB::HARRIS_SCORE;
int patchSize=31;
int fastThreshold = 20;

Mat imgleft, imgright, grayleft, grayright;
Mat grayrightfull,grayleftfull;
Mat imleftkeypoints, imrightkeypoints;

imgleft = imread("im0.png");
imgright = imread("im1.png");

if ( !imgleft.data || !imgright.data){
	cout << " Image could not be loaded " << endl;
	}

cvtColor(imgleft, grayleft, cv::COLOR_BGR2GRAY);
cvtColor(imgright, grayright, cv::COLOR_BGR2GRAY); 

Ptr<Feature2D> f2dptr = cv::ORB::create(nfeatures, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize, fastThreshold);

std::vector<KeyPoint> keypoint_left, keypoint_right;

f2dptr->detect(grayright,keypoint_right);
f2dptr->detect(grayleft,keypoint_left);

drawKeypoints(grayleft, keypoint_left, imleftkeypoints, Scalar::all(-1),cv::DrawMatchesFlags::DEFAULT);

drawKeypoints(grayright, keypoint_right, imrightkeypoints, Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);

namedWindow("Frame" , WINDOW_NORMAL);
createTrackbar("Stereo","Frame", &levels, maxlevels, on_change);

for(int i=0;;i++){
	if (levels ==0){
		imshow("Frame", imleftkeypoints);
	}
	else if(levels > 0) {
		imshow("Frame", imrightkeypoints);
		}

	if (waitKey(33) == 27){
		destroyWindow("Frame");
		break;
		}
}
imwrite("viewLeftORB.png",imleftkeypoints);
imwrite("viewRightORB.png",imrightkeypoints);
return 0;
}
