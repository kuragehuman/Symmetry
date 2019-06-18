#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

//結局シンメトリーじゃなくなりました

int main(int argc, char const *argv[]){
	
	VideoCapture cap(0);
	Mat image;
	Mat sqimage;
	while (1) {
		cap >> image;

		Rect roi(Point(image.cols/2 - image.rows/2, 0), Size(image.rows, image.rows));
		sqimage = image(roi);

		for(int i=0; i <= sqimage.cols/2; i++){
			for(int j=i; j <= sqimage.rows/2; j++){
				sqimage.at<cv::Vec3b>(j, i) = sqimage.at<cv::Vec3b>(i, j);//image(j, image.cols/2 - i)[0];
			}
		}
/*
		for(int i= image.cols/2 - image.rows/2; i < image.cols/2; i++){
			for(int j= i - image.cols/2 + image.rows/2; j < image.rows/2; j++){
//			image.at<cv::Vec3b>(j, i) = image.at<cv::Vec3b>(i - image.cols/2 + image.rows/2, j + image.cols/2 - image.rows/2);//image(j, image.cols/2 - i)[0];
			}
		}
*/
		for(int i = sqimage.cols/2; i < sqimage.cols; i++){
			for(int j = 0; j < sqimage.rows; j++){
				sqimage.at<cv::Vec3b>(j, i) = sqimage.at<cv::Vec3b>(j, sqimage.cols - i);//image(j, image.cols/2 - i)[0];
			}
		}

		for(int i = 0;i < sqimage.cols; i++){
			for(int j = sqimage.rows/2; j < sqimage.rows; j++){
				sqimage.at<cv::Vec3b>(j, i) = sqimage.at<cv::Vec3b>(sqimage.rows - j, i);//image(j, image.cols/2 - i)[0];
			}
		}

		imshow("kaleidoscorp", sqimage);
		int key = waitKey(1);
		if(key == 's'){
			imwrite("./ss.png", sqimage);
		}

	}
	cap.release();

	return 0;
}