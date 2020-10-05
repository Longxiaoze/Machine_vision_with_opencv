/*creat by 龙笑泽  date：2020.09.21
 * 文件说明：使用opencv库读取三通道彩色图
 *         对读入的图片加入椒盐噪声
 *         自定义均值滤波器处理
 *         opencv自带的均值滤波处理
 *         显示四张图片（原图片，加入椒盐噪声后的图像，自定义均值滤波器处理后的图片，opencv自带的均值滤波处理后的图片）
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 * 软件及环境：clion  opencv3  gcc-9  g++-9
 * */
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<ctime>
using namespace cv;
using namespace std;

/**********************************************************************************
 * 函数名：AverFiltering()
 * 作用：通过AverFiltering()函数来进行三通道彩色图片的均值滤波。
 * 函数返回值：AverFiltering()函数处理后得到的图片矩阵
 ***********************************************************************************/
void AverFiltering(const Mat &src,Mat &dst)
{
    if (!src.data) return;
    //at访问像素点
    for (int i = 1; i<src.rows; ++i)//读取行数，遍历
        for (int j = 1; j < src.cols; ++j) //读取列数，遍历
        {
            if ((i - 1 >= 0) && (j - 1) >= 0 && (i + 1)<src.rows && (j + 1)<src.cols) //边缘不进行处理，也就是处理除了周围一圈的矩阵像素点
            {
                dst.at<Vec3b>(i, j)[0] = (src.at<Vec3b>(i, j)[0] + src.at<Vec3b>(i - 1, j - 1)[0] +
                                          src.at<Vec3b>(i - 1, j)[0] + src.at<Vec3b>(i, j - 1)[0] +
                                          src.at<Vec3b>(i - 1, j + 1)[0] + src.at<Vec3b>(i + 1, j - 1)[0] +
                                          src.at<Vec3b>(i + 1, j + 1)[0] + src.at<Vec3b>(i, j + 1)[0] +
                                          src.at<Vec3b>(i + 1, j)[0]) / 9;
                dst.at<Vec3b>(i, j)[1] = (src.at<Vec3b>(i, j)[1] + src.at<Vec3b>(i - 1, j - 1)[1] +
                                          src.at<Vec3b>(i - 1, j)[1] + src.at<Vec3b>(i, j - 1)[1] +
                                          src.at<Vec3b>(i - 1, j + 1)[1] + src.at<Vec3b>(i + 1, j - 1)[1] +
                                          src.at<Vec3b>(i + 1, j + 1)[1] + src.at<Vec3b>(i, j + 1)[1] +
                                          src.at<Vec3b>(i + 1, j)[1]) / 9;
                dst.at<Vec3b>(i, j)[2] = (src.at<Vec3b>(i, j)[2] + src.at<Vec3b>(i - 1, j - 1)[2] +
                                          src.at<Vec3b>(i - 1, j)[2] + src.at<Vec3b>(i, j - 1)[2] +
                                          src.at<Vec3b>(i - 1, j + 1)[2] + src.at<Vec3b>(i + 1, j - 1)[2] +
                                          src.at<Vec3b>(i + 1, j + 1)[2] + src.at<Vec3b>(i, j + 1)[2] +
                                          src.at<Vec3b>(i + 1, j)[2]) / 9;
            }
            else//边缘赋值，边缘一圈为原来图片矩阵的值
            {
                dst.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];
                dst.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
                dst.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];
            }
        }
}

/**********************************************************************************
 * 函数名：salt()
 * 作用：通过salt()函数来给三通道彩色图片加入椒盐噪声。
 * 函数返回值：salt()函数处理后得到的椒盐噪声图片矩阵
 ***********************************************************************************/
void salt(Mat &image, int num)
{
    if (!image.data) return;//防止传入空图
    int i, j;
    srand(time(NULL));
    for (int x = 0; x < num; ++x)
    {
        i = rand() % image.rows;
        j = rand() % image.cols;
        image.at<Vec3b>(i, j)[0] = 255;
        image.at<Vec3b>(i, j)[1] = 255;
        image.at<Vec3b>(i, j)[2] = 255;
    }
}

int main()
{
    Mat image = imread("/Users/hiyoshikei/Desktop/code_all/opencv_4/test.jpg");//读取图片
    imshow("test img", image);//显示原图片

    //图片加入椒盐噪声并显示
    Mat Salt_Image;
    image.copyTo(Salt_Image);
    salt(Salt_Image, 3000);
    imshow("salt img", Salt_Image);

    //进行均值滤波
    Mat image1(image.size(), image.type());
    Mat image2;
    AverFiltering(Salt_Image, image1);//自定义的均值滤波器处理椒盐噪声图片
    blur(Salt_Image, image2, Size(3, 3));//openCV库自带的均值滤波函数处理椒盐噪声图片
    imshow("Custom mean filter", image1);//显示自定义的均值滤波器处理椒盐噪声图片后得到的图片
    imshow("openCV_filter", image2);//显示openCV库自带的均值滤波函数处理椒盐噪声图片后得到的图片
    waitKey();
}
