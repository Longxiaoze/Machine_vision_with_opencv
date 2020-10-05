/*creat by 龙笑泽  date：2020.09.21
 * 文件说明：使用opencv库读取三通道彩色图
 *         对读入的图片加入椒盐噪声
 *         自定义中值滤波器处理
 *         opencv自带的中值滤波处理
 *         显示四张图片（原图片，加入椒盐噪声后的图像，自定义中值滤波器处理后的图片，opencv自带的中值滤波处理后的图片）
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
 * 函数名：Median()
 * 作用：通过Median()函数来求filter的中值。
 * 函数返回值：当前filter的中值
 ***********************************************************************************/
uchar Median(uchar n1, uchar n2, uchar n3, uchar n4, uchar n5,
             uchar n6, uchar n7, uchar n8, uchar n9)
{
    uchar arr[9];
    arr[0] = n1;
    arr[1] = n2;
    arr[2] = n3;
    arr[3] = n4;
    arr[4] = n5;
    arr[5] = n6;
    arr[6] = n7;
    arr[7] = n8;
    arr[8] = n9;
    for (int gap = 9 / 2; gap > 0; gap /= 2)//希尔排序：时间复杂度o(n^(3/2))
        for (int i = gap; i < 9; ++i)
            for (int j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap)
                swap(arr[j], arr[j + gap]);
    return arr[4];//返回中值
}

/**********************************************************************************
 * 函数名：AverFiltering()
 * 作用：通过AverFiltering()函数来进行三通道彩色图片的中值滤波。
 * 函数返回值：AverFiltering()函数处理后得到的图片矩阵
 ***********************************************************************************/
void MedianFlitering(const Mat &src, Mat &dst) {
    if (!src.data)return;
    Mat _dst(src.size(), src.type());
    for(int i=0;i<src.rows;++i)
        for (int j=0; j < src.cols; ++j) {
            if ((i - 1) > 0 && (i + 1) < src.rows && (j - 1) > 0 && (j + 1) < src.cols) {
                _dst.at<Vec3b>(i, j)[0] = Median(src.at<Vec3b>(i, j)[0], src.at<Vec3b>(i + 1, j + 1)[0],
                                                 src.at<Vec3b>(i + 1, j)[0], src.at<Vec3b>(i, j + 1)[0], src.at<Vec3b>(i + 1, j - 1)[0],
                                                 src.at<Vec3b>(i - 1, j + 1)[0], src.at<Vec3b>(i - 1, j)[0], src.at<Vec3b>(i, j - 1)[0],
                                                 src.at<Vec3b>(i - 1, j - 1)[0]);
                _dst.at<Vec3b>(i, j)[1] = Median(src.at<Vec3b>(i, j)[1], src.at<Vec3b>(i + 1, j + 1)[1],
                                                 src.at<Vec3b>(i + 1, j)[1], src.at<Vec3b>(i, j + 1)[1], src.at<Vec3b>(i + 1, j - 1)[1],
                                                 src.at<Vec3b>(i - 1, j + 1)[1], src.at<Vec3b>(i - 1, j)[1], src.at<Vec3b>(i, j - 1)[1],
                                                 src.at<Vec3b>(i - 1, j - 1)[1]);
                _dst.at<Vec3b>(i, j)[2] = Median(src.at<Vec3b>(i, j)[2], src.at<Vec3b>(i + 1, j + 1)[2],
                                                 src.at<Vec3b>(i + 1, j)[2], src.at<Vec3b>(i, j + 1)[2], src.at<Vec3b>(i + 1, j - 1)[2],
                                                 src.at<Vec3b>(i - 1, j + 1)[2], src.at<Vec3b>(i - 1, j)[2], src.at<Vec3b>(i, j - 1)[2],
                                                 src.at<Vec3b>(i - 1, j - 1)[2]);
            }
            else
                _dst.at<Vec3b>(i, j) = src.at<Vec3b>(i, j);
        }
    _dst.copyTo(dst);//拷贝
}


/**********************************************************************************
 * 函数名：salt()
 * 作用：通过salt()函数来给三通道彩色图片加入椒盐噪声。
 * 函数返回值：salt()函数处理后得到的椒盐噪声图片矩阵
 ***********************************************************************************/
void salt(Mat &image, int num) {
    if (!image.data) return;//防止传入空图
    int i, j;
    srand(time(NULL));
    for (int x = 0; x < num; ++x) {
        i = rand() % image.rows;
        j = rand() % image.cols;
        image.at<Vec3b>(i, j)[0] = 255;
        image.at<Vec3b>(i, j)[1] = 255;
        image.at<Vec3b>(i, j)[2] = 255;
    }
}

int main() {
    Mat image = imread("/Users/hiyoshikei/Desktop/code_all/opencv_4/test.jpg");//读取图片
    imshow("test.jpg", image);//显示原图片

    //图片加入椒盐噪声并显示
    Mat Salt_Image;
    image.copyTo(Salt_Image);
    salt(Salt_Image, 3000);
    imshow("Salt_Image", Salt_Image);

    //进行中值滤波
    Mat image3, image4;
    MedianFlitering(Salt_Image, image3);//自定义的中值滤波器处理椒盐噪声图片
    medianBlur(Salt_Image, image4, 3);//openCV库自带的中值滤波函数处理椒盐噪声图片
    imshow("Custom median filter", image3);//显示自定义的中值滤波器处理椒盐噪声图片后得到的图片
    imshow("openCV_median filter", image4);//显示openCV库自带的均值滤波函数处理椒盐噪声图片后得到的图片
    waitKey();
}
