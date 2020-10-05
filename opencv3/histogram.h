/*creat by 龙笑泽  date：2020.09.14
 * 文件说明：main.cpp的头文件，主要是用来绘制灰度直方图，使用请调用getHistogramImage()函数，输入灰度图像即可返回灰度直方图图像。
 * 软件及环境：clion（在cmakelists中add_executable中加入histogram.h即可编译）  opencv3  gcc-9  g++-9
 * */

#if !defined HISTOGRAM
#define HISTOGRAM

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;

class Histogram
{
private:
    int histSize[1];
    float hranges[2];
    const float*ranges[1];
    int channels[1];
public:
    Histogram()
    {
        //初始化数组
        histSize[0] = 256;
        hranges[0] = 0.0;
        hranges[1] = 256.0;
        ranges[0] = hranges;
        channels[0] = 0;
    }

    /**********************************************************************************
     * 函数名：getHistogram()
     * 作用：通过calcHist函数来计算一组数组的直方图。
     * 函数返回值：calcHist函数得到的hist
     * trick（calcHist的主要参数说明）：1.images    –  源图像数组
     *                              2.nimages   –  源图像的数目
     *                              3.channels  –  维度通道序列
     *                              4.mask      –  可选择的mask。如果该矩阵不空的话，它必须是一个8-bit的矩阵，与images[i]同尺寸。在图像中，只有被mask覆盖的区域的像素才参与直方图统计。如果这个参数想用默认值，输入Mat()
     *                              5.hist      –  输出直方图， 它是一个稠密或稀疏矩阵，具有dims个维度
     *                              6.dims      –  直方图的维度
     *                              7.histSize  –  数组
     *                              8.ranges    -  统计像素点的取值范围
     ***********************************************************************************/
    Mat getHistogram(const Mat &image)
    {
        Mat hist;
        calcHist(&image,
                 1,
                 channels,
                 Mat(),
                 hist,
                 1,
                 histSize,
                 ranges
        );
        return hist;
    }

    /**********************************************************************************
 * 函数名：getImageOfHistogram()
 * 作用：通过getImageOfHistogram()函数来绘制直方图图像
 * 函数返回值：返回根据输入函数的图像hist数据绘制好的直方图图像
 ***********************************************************************************/
    static Mat getImageOfHistogram(const Mat &hist, int zoom)
    {
        cv::String ss;
        char midTurn[256];
        double maxVal = 0;
        double minVal = 0;
        minMaxLoc(hist, &minVal, &maxVal, 0, 0);// minMaxLoc查找最小和最大元素值及其位置。minMaxLoc只能处理2维以下的
        int histSize = hist.rows;//将图像的形状赋值
        Mat histImg(histSize*zoom, histSize*zoom, CV_8U, Scalar(255));
        int hpt = static_cast<int>(0.9*histSize);//强制类型转换
        for (int h = 0; h < histSize; h++)//绘制直方图的柱状图
        {
            float binVal = hist.at<float>(h);
            if (binVal > 0)
            {
                int intensity = static_cast<int>(binVal*hpt / maxVal);
                line(histImg, Point(h*zoom, histSize*zoom), Point(h*zoom, (histSize - intensity)*zoom), Scalar(0), zoom);
            }
        }
        for (int i = 0; i < 256; i += 25)//在直方图上标注坐标
        {
            sprintf(midTurn, "%d", i);//将数值转换为文本
            ss = midTurn;
            putText(histImg,//目标图像
                    ss,//文本
                    cv::Point(i, 10),//文本位置
                    cv::FONT_HERSHEY_PLAIN,//字体类型
                    0.5,//字体大小
                    0,//字体颜色
                    1);//文本厚度
        }
        return histImg;
    }

    /**********************************************************************************
* 函数名：getHistogramImage()
* 作用：结合getHistogram函数计算直方图和getImageOfHistogram函数绘制直方图
* 函数返回值：返回根据图像绘制好的直方图图像
***********************************************************************************/
    Mat getHistogramImage(const Mat &image, int zoom = 1)
    {
        Mat hist = getHistogram(image);

        return getImageOfHistogram(hist, zoom);
    }
};
#endif
