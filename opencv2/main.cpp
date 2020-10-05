/*creat by 龙笑泽  date：2020.09.07
 * 文件说明：使用opencv库读取三通道彩色图并转化为灰度图，并将灰度图保存
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 * 软件及环境：clion  opencv4  gcc-9  g++-9
 * */
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    String imageName( "/Users/hiyoshikei/Desktop/code_all/opencv2/test.jpg" ); // 打开图片的位置
    Mat image = imread( imageName, IMREAD_COLOR ); // 读取文件

    // 检查输入（一般图片位置信息有问题会输出如下信息。解决方案：检查图片是否存在/输入完整路径）
    if( image.empty() )
    {
        cout <<  "Could not open or find the image" << endl ;
        return -1;
    }

    // 创建一个显示窗口
    namedWindow( "Colorful pics", WINDOW_NORMAL | WINDOW_FREERATIO | WINDOW_GUI_EXPANDED );
    imshow( "Colorful pics", image );                // 在该窗口显示彩色图片

    // 将彩色图片转化为灰度图，并保存为Gray_test.jpg文件
    Mat gray_img;
    cvtColor( image, gray_img, COLOR_BGR2GRAY);  //使用 COLOR_BGR2GRAY，将彩色图片转化为灰度图。 在include <opencv2/opencv.hpp>头文件中
    imwrite("/Users/hiyoshikei/Desktop/code_all/opencv2/Gray_test.jpg", gray_img);//保存图片为Gray_test.jpg
    // 创建一个显示窗口
    namedWindow("Gray pics", WINDOW_AUTOSIZE);    // 使用 WINDOW_AUTOSIZE 参数
    imshow("Gray pics", gray_img);//在窗口显示灰度图

    waitKey(0);
    return 0;
}
