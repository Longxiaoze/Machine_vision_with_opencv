/*creat by 龙笑泽  date：2020.10.02
 * 文件说明：使用opencv库读取三通道彩色图
 *         将图像旋转逆时针30度
 *         显示原图片和旋转后的图片
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 *        3.不知道是不是太简单，opencv居然没有封装旋转的函数。。。也是醉了
 * 软件及环境：clion  opencv3  gcc-9  g++-9
 * */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <cmath>

using namespace cv;

Mat imgRotate(Mat matSrc, float angle, bool direction)
{
    float theta = angle * CV_PI / 180.0;
    int nRowsSrc = matSrc.rows;
    int nColsSrc = matSrc.cols;
    // 如果是顺时针旋转
    if (!direction)
        theta = 2 * CV_PI - theta;
    // 全部以逆时针旋转来计算
    // 逆时针旋转矩阵
    float matRotate[3][3]{
            {std::cos(theta), -std::sin(theta), 0},
            {std::sin(theta), std::cos(theta), 0 },
            {0, 0, 1}
    };
    float pt[3][2]{
            { 0, static_cast<float>(nRowsSrc) },
            {static_cast<float>(nColsSrc), static_cast<float>(nRowsSrc)},
            {static_cast<float>(nColsSrc), 0}
    };
    for (int i = 0; i < 3; i++)
    {
        float x = pt[i][0] * matRotate[0][0] + pt[i][1] * matRotate[1][0];
        float y = pt[i][0] * matRotate[0][1] + pt[i][1] * matRotate[1][1];
        pt[i][0] = x;
        pt[i][1] = y;
    }
    // 计算出旋转后图像的极值点和尺寸
    float fMin_x = min(min(min(pt[0][0], pt[1][0]), pt[2][0]), (float)0.0);
    float fMin_y = min(min(min(pt[0][1], pt[1][1]), pt[2][1]), (float)0.0);
    float fMax_x = max(max(max(pt[0][0], pt[1][0]), pt[2][0]), (float)0.0);
    float fMax_y = max(max(max(pt[0][1], pt[1][1]), pt[2][1]), (float)0.0);
    int nRows = cvRound(fMax_y - fMin_y + 0.5) + 1;
    int nCols = cvRound(fMax_x - fMin_x + 0.5) + 1;
    int nMin_x = cvRound(fMin_x + 0.5);
    int nMin_y = cvRound(fMin_y + 0.5);
    // 拷贝输出图像
    Mat matRet(nRows, nCols, matSrc.type(), Scalar(0));
    for (int j = 0; j < nRows; j++)
    {
        for (int i = 0; i < nCols; i++)
        {
            // 计算出输出图像在原图像中的对应点的坐标，然后复制该坐标的灰度值
            // 因为是逆时针转换，所以这里映射到原图像的时候可以看成是，输出图像
            // 到顺时针旋转到原图像的，而顺时针旋转矩阵刚好是逆时针旋转矩阵的转置
            // 同时还要考虑到要把旋转后的图像的左上角移动到坐标原点。
            int x = (i + nMin_x) * matRotate[0][0] + (j + nMin_y) * matRotate[0][1];
            int y = (i + nMin_x) * matRotate[1][0] + (j + nMin_y) * matRotate[1][1];
            if (x >= 0 && x < nColsSrc && y >= 0 && y < nRowsSrc)
            {
                matRet.at<Vec3b>(j, i) = matSrc.at<Vec3b>(y, x);
            }
        }
    }
    return matRet;
}

int main()
{
    Mat matSrc = imread("/Users/hiyoshikei/Desktop/code_all/opencv_4/test.jpg");//读取图片
    if (matSrc.empty())
        return 1;
    float angle = 30;
    Mat matRet = imgRotate(matSrc, angle, true);
    imshow("src", matSrc);
    imshow("rotate", matRet);
    // 保存图像
    imwrite("/Users/hiyoshikei/Desktop/code_all/opencv_4/imgRotate.jpg", matRet);

    waitKey();
    return 0;
}
