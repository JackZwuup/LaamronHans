#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
using namespace cv;
using namespace std;



int main(int argc, char** argv) {

	Mat img1 = imread("c:\\OpenCVimage\\box.png", IMREAD_COLOR);
	Mat img2 = imread("c:\\OpenCVimage\\box_in_scene.png", IMREAD_COLOR);

	Ptr<Feature2D> surf = SURF::create();
	vector<KeyPoint> keypoints1;
	Mat descriptors1;
	surf->detectAndCompute(img1, Mat(), keypoints1, descriptors1);

	Ptr<Feature2D> surf = SURF::create();
	vector<KeyPoint> keypoints2;
	Mat descriptors2;
	surf->detectAndCompute(img2, Mat(), keypoints1, descriptors1);

	// matching descriptors
	BruteForceMatcher<L2<float> > matcher;
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	namedWindow("matches", 1);
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
	imshow("matches", img_matches);
	waitKey(0);

	Mat H = findHomography(Mat(points1), Mat(points2), RANSAC, ransacReprojThreshold);
	Mat points1Projected; perspectiveTransform(Mat(points1), points1Projected, H);
}
