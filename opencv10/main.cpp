#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;

int main()
{
    //图像尺寸
    cv::Size imageSize;

    //标定板上每行每列的角点数
    cv::Size boardSize = cv::Size(8, 6);

    //缓存图像上检测到的角点
    std::vector<Point2f>  imagePointsBuf;
    std::vector<Point2f>  imagePointsSeq;

    //读入第一张图片并获取图宽高信息
    Mat imageInput = cv::imread("/Users/hiyoshikei/Desktop/code_all/opencv10/test.jpg");
    cv::imshow("imageInput", imageInput);

    imageSize.width = imageInput.cols;
    imageSize.height = imageInput.rows;
    std::cout << "imageSize.width = " << imageSize.width << std::endl;
    std::cout << "imageSize.height = " << imageSize.height << std::endl;


    //提取图片的角点
    if (cv::findChessboardCorners(imageInput, boardSize, imagePointsBuf) == 0)
    {
        //找不到角点
        std::cout << "Can not find chessboard corners!" << std::endl;
        exit(1000);
    }
    else
    {
        //输出48个角点
        //std::cout << "imagePointsBuf = " << imagePointsBuf << std::endl;
        int c = imagePointsBuf.size();
        std::cout <<"共有 "<< c <<" 个角点"<< std::endl;

        //转换为灰度图片
        Mat viewGray;
        cv::cvtColor(imageInput, viewGray, cv::COLOR_BGR2GRAY);
        //亚像素精确化   对粗提取的角点进行精确化
        cv::find4QuadCornerSubpix(viewGray, imagePointsBuf, cv::Size(5, 5));
        //保存亚像素点
        //imagePointsSeq.push_back(imagePointsBuf);
        std::cout << "二维像素图像点 ：" << imagePointsBuf << std::endl;
        std::cout << "=====================分割线======================" << std::endl;
        //在图像上显示角点位置
        cv::drawChessboardCorners(viewGray, boardSize, imagePointsBuf, true);
        //显示图片
        cv::imshow("Camera Calibration", viewGray);
        cv::imwrite("test.jpg", viewGray);
        //等待0.5s
        //waitKey(500);
    }

    std::vector<cv::Point2f> scene_PointSet;

    for (int i = 0; i < 8; i++)//行数
    {
        for (int j = 0; j < 6; j++)//列数
        {
            cv::Point2f realPoint;
            //假设标定板放在世界坐标系中z=0的平面上。
            realPoint.x = i*1.55;
            realPoint.y = j*1.55;

            scene_PointSet.push_back(realPoint);
        }
    }

    std::cout << "二维平面坐标点 ：" << scene_PointSet << std::endl;
    std::cout << "=====================分割线======================" << std::endl;
    Mat h = findHomography(scene_PointSet, imagePointsBuf);
    std::cout << "H ：" << h << std::endl;
    std::cout << "=====================分割线======================" << std::endl;
    cv::waitKey(0);
}



