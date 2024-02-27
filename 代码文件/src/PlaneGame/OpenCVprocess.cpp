#include "stdafx.h"
#include "OpenCVprocess.h"

void OpenCVprocess::ImgProcessInit()
{
	myColors = {/*noon {44,69,64,97,255,255}*/ /*{45,99,40,89,248,130} at doom*/{44,75,57,96,246,217} };
	//要识别的颜色
}
Point OpenCVprocess:: getRoiPoint(Mat src)//得到坐标
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//threshold(src, src, 125, 255, THRESH_BINARY);
	if (src.empty()) return Point(5, 5);
	findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	Point myPoint(0, 0);//坐标
	int max = -1;//储存面积最大的区域的下标

	//寻找最大轮廓

	int good_contours = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		if (contourArea(contours[i]) > 40)
		{
			good_contours++;
			if (max != -1)
			{
				if (contourArea(contours[i]) > contourArea(contours[max]))
					max = i;
			}
			else max = i;
		}
	}
	if (good_contours == 0)
		return Point(src.cols / 2 - 50, src.rows - 100);

	if (max != -1)
	{
		//绘制边缘
		float peri = arcLength(contours[max], true);
		approxPolyDP(contours[max], conPoly[max], 0.01 * peri, true);
		//drawContours(img, conPoly, max, Scalar(255, 0, 255), 3);
		//cout << conPoly[i].size() << endl;
		//绘制矩形框
		boundRect[max] = boundingRect(conPoly[max]);
		//rectangle(img, boundRect[max].tl(), boundRect[max].br(), Scalar(0, 255, 0));
		//获取面积最大的区域,坐标
		myPoint.x = boundRect[max].x + boundRect[max].width / 2;
		myPoint.y = boundRect[max].y;
	}
	return myPoint;
}
Point OpenCVprocess::finalPoint(Mat src)
{

	imgSize = Size(src.cols, src.rows);
	Mat imgHSV;
	flip(src, src, 1);
	//imshow("0", imgHSV);
	cvtColor(src, imgHSV, COLOR_BGR2HSV);
	int max = 0;
	Point myPoint;
	for (int i = 0; i < myColors.size(); i++)
	{

		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);

		//Scalar lower(33, 95, 23);
		//Scalar upper(66, 246, 106);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);//筛选出特定颜色的区域
		//imshow(to_string(i), mask);
		//cout << mask.size() << endl;
		myPoint = getRoiPoint(mask);
	}
	return myPoint;
}
CPoint OpenCVprocess::getGamePoint(Point imgP)
{
	CPoint gameP;
	gameP.x = imgP.x * GAME_WIDTH / imgSize.width;
	gameP.y = imgP.y * GAME_HEIGHT / imgSize.height;
	return gameP;
}
void OpenCVprocess::myyimshow(Mat src)
{
	imshow("ddd", src);
}
Point OpenCVprocess::myFindcontours(Mat src)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//threshold(src, src, 125, 255, THRESH_BINARY);
	if (src.empty()) return Point(5, 5);
	imshow("qqqq", src);
	//findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	return Point(6, 6);
}