/*creat by 龙笑泽  date：2020.09.14
 * 文件说明：使用opencv库读取三通道彩色图并转化为灰度图,
 *         获得灰度直方图，
 *         然后通过灰度直方图获得图片前景，
 *         并在计算机上显示所有图，
 *         将灰度图,灰度直方图，2值图像保存
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 * 软件及环境：clion  opencv3  gcc-9  g++-9
 * */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "histogram.h"
using namespace std;

int main()
{
    //实例化类
    cv::Mat grayImage;
    cv::Mat histImage;
    cv::Mat binaryImage;
    Histogram hist;

    //读取图片（可能是由于我建项目在桌面的原因，将图片和此文件放在同一文件夹下，需要使用全路径，仅输入图片名有问题
    //在保存时，也是这个问题，也需要输出全部路径
    cv::Mat image = cv::imread("/Users/hiyoshikei/Desktop/code_all/opencv3/test.jpg");

    if (image.empty())//判断图片是否出错
    {
        cout << "read image is failure" << endl;//输出错误信息
        exit(0);
    }

    cv::imshow("Origin Image", image);//显示原彩色图片

    cv::cvtColor(image, grayImage, COLOR_BGR2GRAY);//转化彩色图片为灰度图

    imwrite("/Users/hiyoshikei/Desktop/code_all/opencv3/Gray_test.jpg", grayImage);//保存灰度图片，命名为Gray_test.jpg

    histImage = hist.getHistogramImage(grayImage);//调用编写的头文件histogram.h中的getHistogramImage函数，获得灰度图片的灰度直方图
    cv::imshow("histImage", histImage);//显示灰度直方图
    imwrite("/Users/hiyoshikei/Desktop/code_all/opencv3/histImage.jpg", histImage);//保存灰度直方图，命名为histImage.jpg

    //调用opencv的threshold函数，参数THRESH_BINARY_INV的作用是将大于thresh的值置0，小于等于thresh的值置maxval
    //对比灰度直方图和显示的2值图像，此处输入的图片的阈值thresh设置为60即可，这里表示将大于60的像素点变为0，将小于60的像素点设置为255，得到2值图像（对应输入图片则是将背景变成纯白色，将前景变为纯黑色）
    //想得到相反的结果只需要将THRESH_BINARY_INV参数设置为THRESH_BINARY，即可得到相反的结果
    cv::threshold(grayImage, binaryImage, 60, 255, THRESH_BINARY_INV);

    cv::imshow("gray Image", grayImage);//显示灰度图
    cv::imshow("binary Image", binaryImage);//显示2值图像
    imwrite("/Users/hiyoshikei/Desktop/code_all/opencv3/Gray_test_binary.jpg", binaryImage);//保存2值图像，命名为Gray_test_binary.jpg

    waitKey(0);
}
