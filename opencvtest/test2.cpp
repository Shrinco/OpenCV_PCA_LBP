#include "stdafx.h"
#include "test.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
int main2()
{
	const char* imagename = "111.bmp";
 
	//���ļ��ж���ͼ��
	Mat img = imread(imagename);
	//�������ͼ��ʧ��
	if(img.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}
	Mat img1(img.rows,img.cols,CV_32FC1);
	//img.copyTo(img1);
	
	
	Mat img2(140,6400,CV_8UC1);
	for(int i=0;i<140;i++)
	{
		for(int j = 0;j<6400;j++)
		{
			img1.at<float>(i,j) = img.at<uchar>(i,j);
		}
	}
	PCA pca(img1,Mat(),CV_PCA_DATA_AS_ROW,12);
	Mat dst1;
	dst1 = pca.project(img1);
	Mat dst2,dst3;
	Mat img3(1,6400,CV_32FC1);
	for(int i = 0;i<6400;i++)
	{
		img3.at<float>(0,i) = img1.at<float>(0,i);
	}
	Mat img11 = imread("1.bmp");
	Mat img4(1,6400,CV_32FC1);
	for(int i = 0;i<80;i++)
	{
		for(int j = 0;j<80;j++)
		{
			img4.at<float>(0,80*i+j) = img11.at<uchar>(i,j);
		}
	}
	dst2 = pca.project(img3);
	dst3 = pca.project(img4);
	for(int i = 0;i<80;i++)
	{
		float a = img3.at<float>(0,80);
		float b = img3.at<float>(0,81);
		float c = img3.at<float>(0,82);
		if((a == int(img11.at<uchar>(i,0)))&&(b == int(img11.at<uchar>(i,1)))&&(c == int(img11.at<uchar>(i,3)))){
			std::cout<<a<<"  "<<b<<"  "<<int(img11.at<uchar>(i,0))<<std::endl;
		}
	}
	Mat label(140,1,CV_32FC1);
	for(int i = 0;i<140;i++)
	{
		label.at<float>(i,0) = i;
	}
	Mat trainingData = dst1;
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC; 
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);
	CvSVM SVM;
	SVM.train(trainingData, label, Mat(), Mat(), params);
	float response = SVM.predict(dst2);
	int number = SVM.get_support_vector_count();
	//��ʾͼ��
	imshow("image", img1);
 
	//�˺����ȴ�������������������ͷ���
	waitKey();
 
	return 0;
}
PCA PCATrain(Mat img)
{
	PCA pca(img,Mat(),CV_PCA_DATA_AS_ROW,12);
	return pca;
}
Mat TrainCode(Mat img,PCA pca)
{
	Mat dst = pca.project(img);
	return dst;
}
int CvSVMTrain(Mat trainingData,Mat label,CvSVM &SVM)
{
	CvSVMParams params;
	params.svm_type = CvSVM::C_SVC; 
	params.kernel_type = CvSVM::LINEAR;
	params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);	
	SVM.train(trainingData, label, Mat(), Mat(), params);
	return 0;
}
Mat CheckImage(Mat dst,CvSVM &SVM,Mat imgmain)
{
	Mat last(80,80,CV_32FC1);
	float response = SVM.predict(dst);
	int b = response;
	imgmain.row(b).reshape(1,80).convertTo(last,CV_32FC1);
	//for(int i = 0;i<80;i++)
	//{
	//	for(int j = 0;j<80;j++)
	//	{
	//		last.at<float>(i,j) = imgmain.at<float>(b,80*i+j);
	//	}
	//}
	return last;
}
Mat ReturnImage(Mat img1,Mat img2)
{
	img2.reshape(1,1).row(0).convertTo(img1,CV_32FC1);
	return img1;
}
int ImageMain(char*imagename,char*imagename1,char*imagename2)
{
	Mat label(210,1,CV_32FC1);
	for(int i = 0;i<70;i++)
	{
		for(int j = 0;j<3;j++)
		{
			int n = 3*i+j;
			label.at<float>(n,0) = 3*i;
		}
	}
	//���ļ��ж���ͼ��
	Mat img = imread(imagename,0);
	Mat img2 = imread(imagename1,0);
	Mat img3 = imread(imagename2,0);
	Mat WillCheckImage1(1,6400,CV_32FC1);
	Mat WillCheckImage2(1,6400,CV_32FC1);
	WillCheckImage1 = ReturnImage(WillCheckImage1,img2);
	WillCheckImage2 = ReturnImage(WillCheckImage2,img3);
	//�������ͼ��ʧ��
	if(img.empty()||WillCheckImage1.empty()||WillCheckImage2.empty())
	{
		fprintf(stderr, "Can not load image %s\n", imagename);
		return -1;
	}
	else
	{
		Mat img1(img.rows,img.cols,CV_32FC1);
		//for(int i=0;i<140;i++)
		//{
		//	for(int j = 0;j<6400;j++)
		//	{
		//	img1.at<float>(i,j) = img.at<uchar>(i,j);
		//	}
		//}
		img1 = img;
		PCA pca;
		pca = PCATrain(img1);
		Mat dst,dst1,dst2;
		dst = TrainCode(img1,pca);
		dst1 = TrainCode(WillCheckImage1,pca);
		dst2 = TrainCode(WillCheckImage2,pca);
		CvSVM SVM;
		CvSVMTrain(dst,label,SVM);
		SVM.predict(dst1);
		Mat LastImage1 = CheckImage(dst1,SVM,img1);
		Mat LastImage2 = CheckImage(dst2,SVM,img1);
		return 0;
	}
}