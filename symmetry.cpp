#include <opencv2/opencv.hpp>
#include <iostream>

#define IMGSMALL 0.25

using namespace std;
using namespace cv;

Mat detectFaceInImage(Mat &image,string &cascade_file){
	CascadeClassifier cascade;
	cascade.load(cascade_file);

	vector<Rect> faces;
	cascade.detectMultiScale(image, faces, 1.1,3,0,Size(20,20));

	for (int i = 0; i < faces.size(); i++){
		rectangle(image, Point(faces[i].x,faces[i].y),Point(faces[i].x + faces[i].width,faces[i].y + faces[i].height),Scalar(0,200,0),3,CV_AA);
	}
	return image;
}

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