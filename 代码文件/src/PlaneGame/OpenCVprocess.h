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

	Point getRoiPoint(Mat src);//�õ�ֽƬ����
	
	Point finalPoint(Mat src);//�õ�
	
	CPoint getGamePoint(Point imgP);//ת��PointΪCPoint
	
	void myyimshow(Mat src);//����ͼƬ���
	
	Point myFindcontours(Mat src);//��������

private:

	Mat m_frame;//ͼ��
	Scalar targetColor;//Ŀ����ɫ
	vector<vector<int>> myColors; //��ɫ
	Size imgSize;//ͼ���С
};

