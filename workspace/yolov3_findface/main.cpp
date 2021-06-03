#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <bitset>
#include <algorithm>
#include <vector>
#include <numeric>
#include "yoloface.h"

using namespace cv;
using namespace std;

int main()
{
	YOLOv3::Detecting detector;
	vector<YOLOv3::yoloresult> result;
	namedWindow("test");
        cv::Mat src = imread("../data/test.jpg");
        detector.Detect(src, result);
        detector.DrawResult(src, result);
        imshow("test", src);
        waitKey(0);  
}

