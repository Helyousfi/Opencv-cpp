#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream> 
#include <fstream>
#include <string>
#include <cmath>
#define S 3

using namespace std;
using namespace cv;

int argmin(float distance[S][S]) {
	float min = distance[0][0];
	int argmin_i = 0;
	int argmin_j = 0;
	for (int i = 1; i < S; i++) {
		for (int j = 1; j < S; j++) {
			if (min > distance[i][j]) {
				argmin_i = i;
				argmin_j = j;
				min = distance[i][j];
			}
		}
	}
	return argmin_i, argmin_j;
}

float distancePixels(int pixel1[], int pixel2[], float m){
	float d_lab = sqrt((pixel1[2] - pixel2[2]) * (pixel1[2] - pixel2[2]));
	float d_xy = sqrt((pixel1[0] - pixel2[0])*(pixel1[0] - pixel2[0]) +
						(pixel1[1] - pixel2[1])*(pixel1[1] - pixel2[1]));
	float D_s = d_lab + (float)(m / S) * d_xy;
	return D_s;
}

int plot_image(cv::Mat image){
	std::cout << "--------------------" << std::endl;
	if (image.empty()) { return -1; };
	cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Image", image);
	cv::waitKey(0);
}

string type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}



int main(int argc, char** argv) {
	std::string path = "Resources/dog.jpg";
	cv::Mat image = cv::imread(path, cv::IMREAD_GRAYSCALE);
	
	int rows = image.rows;
	int cols = image.cols;
	
	// Test
	std::cout << type2str(image.type()) << std::endl;
	
	/*
	// Convert to 5 dimension image
	cv::Mat image_pixel3D = cv::Mat::zeros(image.size(), CV_8UC3);
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			image_pixel3D.at<Vec3b>(i, j)[0] = i;
			image_pixel3D.at<Vec3b>(i, j)[1] = j;
			image_pixel3D.at<Vec3b>(i, j)[2] = image.at<uchar>(i, j);
		}
	}

	//Tests
	std::cout << "------------" << image_pixel3D.size() << std::endl;

	unsigned char pixel1[3] = {0,0,0}, pixel2[3] = { 0,0,0 };
	pixel1[0] = image_pixel3D.at<Vec3b>(1, 2)[0];
	pixel1[1] = image_pixel3D.at<Vec3b>(1, 2)[1];
	pixel1[2] = image_pixel3D.at<Vec3b>(1, 2)[2];

	pixel2[0] = image_pixel3D.at<Vec3b>(6, 3)[0];
	pixel2[1] = image_pixel3D.at<Vec3b>(6, 3)[1];
	pixel2[2] = image_pixel3D.at<Vec3b>(6, 3)[2];

	std::cout << distancePixels(pixel1, pixel2, 2) << std::endl;
	*/
	
	///////////////////////////////////////
	int image_pixel3D[330][332][3];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			image_pixel3D[i][j][0] = i;
			image_pixel3D[i][j][1] = j;
			image_pixel3D[i][j][2] = image.at<uchar>(i, j);
		}
	}
	cout << " ------------------------------ " << endl;
	

	// Initialize the clusters 
	/*
	cv::Mat Clusters = cv::Mat::zeros(Size(S+1, S+1), CV_8UC3);
	int index_i = 0;
	int index_j;
	for (int i = 0; i < rows; i = i + int(rows / S)) {
		index_j = 0;
		for (int j = 0; j < cols; j = j + int(cols / S)) {
			Clusters.at<Vec3b>(index_i, index_j)[0] = i;
			Clusters.at<Vec3b>(index_i, index_j)[1] = j;
			Clusters.at<Vec3b>(index_i, index_j)[2] = image.at<uchar>(i, j);
			index_j++;
		}
		index_i++;
	}
	*/
	

	int Clusters[S + 1][S + 1][3];
	int index_i = 0;
	int index_j;
	for (int i = 0; i < rows; i = i + int(rows / S)) {
		index_j = 0;
		for (int j = 0; j < cols; j = j + int(cols / S)) {
			Clusters[index_i][index_j][0] = i;
			Clusters[index_i][index_j][1] = j;
			Clusters[index_i][index_j][2] = (unsigned char)image.at<uchar>(i, j);
			index_j++;
		}
		index_i++;
	}
	


	float dist[S][S];
	int argmin_i = 0, argmin_j = 0;
	//Superpixel image
	cv::Mat image_super_pixel = cv::Mat::zeros(image.size(), CV_8UC1);
	
	int pixel1[3] = { 0,0,0 }, pixel2[3] = { 0,0,0 };

	cout << " ------------------------------ " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			
			pixel1[0] = image_pixel3D[i][j][0];
			pixel1[1] = image_pixel3D[i][j][1];
			pixel1[2] = image_pixel3D[i][j][2];
			
			for (int m = 0; m < S; m++) {
				for (int n = 0; n < S; n++) {
					pixel2[0] = Clusters[m][n][0];
					pixel2[1] = Clusters[m][n][1];
					pixel2[2] = Clusters[m][n][2];
					
					dist[m][n] = distancePixels(pixel1, pixel2, 20);
					
					//cout << dist[m][n] << endl;
				}
			}
			argmin_i, argmin_j = argmin(dist);
			
			//cout << argmin_i << argmin_j << endl;
			image_super_pixel.at<uchar>(i, j) = Clusters[argmin_i][argmin_j][2];
			
		}
		
	}

	plot_image(image);
	plot_image(image_super_pixel);
	return 0;
}
