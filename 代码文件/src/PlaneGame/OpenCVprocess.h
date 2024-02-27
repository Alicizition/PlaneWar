#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include"stdafx.h"
using namespace cv;
using namespace std;
class OpenCVprocess
{

public:
	void ImgProcessInit();

	Point getRoiPoint(Mat src);//得到纸片坐标
	
	Point finalPoint(Mat src);//得到
	
	CPoint getGamePoint(Point imgP);//转化Point为CPoint
	
	void myyimshow(Mat src);//测试图片输出
	
	Point myFindcontours(Mat src);//测试轮廓

private:

	Mat m_frame;//图像
	Scalar targetColor;//目标颜色
	vector<vector<int>> myColors; //绿色
	Size imgSize;//图像大小
};

