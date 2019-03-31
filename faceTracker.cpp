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
	Mat def_omen = imread("Omen.png");
	
	CascadeClassifier cascade;
	cascade.load("haarcascade_frontalface_alt.xml");
	Mat grayimage;

	while (1) {
		cap >> image;

		//処理時間短縮のためのサイズ変更
		Mat smallImage;
		resize(image, smallImage, Size(), IMGSMALL, IMGSMALL);
		cvtColor(smallImage, grayimage, CV_RGB2GRAY);

		vector<Rect> faces;
		cascade.detectMultiScale(grayimage, faces, 1.1, 3, 0, Size(20, 20));

		for(int i=0; i<faces.size(); i++){
			faces[i].x -= 5/IMGSMALL;
			faces[i].y -= 5/IMGSMALL;
			faces[i].width += 10/IMGSMALL;
			faces[i].height += 10/IMGSMALL;
			faces[i].x /= IMGSMALL;
			faces[i].y /= IMGSMALL;
			faces[i].width /= IMGSMALL;
			faces[i].height /= IMGSMALL;
			Mat omen;
			resize(def_omen, omen, Size(faces[i].width, faces[i].height));
	
			if((faces[i].x >= 0) && (faces[i].x + omen.cols <= image.cols) && (faces[i].y >= 0) && (faces[i].y + omen.rows <= image.rows)){
				Mat roi = image(Rect(faces[i].x, faces[i].y, omen.cols, omen.rows));
				omen.copyTo(roi);
			}
		}
		imshow("Virtual YouTuber", image);
		waitKey(1);

	}
	cap.release();

	return 0;
}