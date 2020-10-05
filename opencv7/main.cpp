/*creat by 龙笑泽  date：2020.10.02
 * 文件说明：使用opencv库读取三通道彩色图
 *         输入平移量，对图像进行平移操作
 *         显示原图片和平移后的图片
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 * 软件及环境：clion  opencv3  gcc-9  g++-9
 * */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main() {
    Mat srcImage, dstImage;
    int xOffset, yOffset;        //x和y方向的平移量
    srcImage = imread("/Users/hiyoshikei/Desktop/code_all/opencv_4/test.jpg");//读取图片
    if (!srcImage.data) {
        cout << "读入图片错误！" << endl;
        return -1;
    }
    dstImage.create(srcImage.size(), srcImage.type());
    cout << "请输入x方向和y方向的平移量：";
    cin >> xOffset >> yOffset;
    int rowNumber = srcImage.rows;
    int colNumber = srcImage.cols;

    //进行遍历图像
    for (int i = 0; i < rowNumber; i++) {
        for (int j = 0; j < colNumber; j++) {
            //平移变换
            int x = j - xOffset;
            int y = i - yOffset;
            //判断边界情况
            if (x >= 0 && y >= 0 && x < colNumber && y < rowNumber)
                dstImage.at<Vec3b>(i, j) = srcImage.at<Vec3b>(y, x);
        }
    }
    imshow("test", srcImage);
    imshow("remove_img", dstImage);
    waitKey();
    return 0;
}
