#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[]){
	
	VideoCapture cap(0);
	Mat image;
	
	while (1) {
		cap >> image;

		for(int i = image.cols/2; i < image.cols; i++){
			for(int j = 0; j < image.rows; j++){
				image.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(j, image.cols - i);//image(j, image.cols/2 - i)[0];
			}
		}
		imshow("symmetry", image);
		waitKey(1);

	}
	cap.release();

	return 0;
}