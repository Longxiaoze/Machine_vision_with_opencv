/*creat by 龙笑泽  date：2020.09.21
 * 文件说明：0.使用opencv库读取三通道彩色图并显示
 *         1.将三通道彩色图片转化为灰度图
 *         2.Canny算子：均值滤波--》canny处理--》显示
 *         3.Sobel算子：分别计算x，y方向的结果并显示，并将两结果结合显示
 *         4.Laplacian算子：将原图片--》高斯滤波消除噪声--》转化为灰度图--》
 *         显示四张图片（原图片，加入椒盐噪声后的图像，自定义中值滤波器处理后的图片，opencv自带的中值滤波处理后的图片）
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 *        3.Canny()函数介绍：
 *              void Canny(InputArray image,OutputArray edges, double threshold1, double threshold2, int apertureSize=3,bool L2gradient=false )
 *              第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
 *              第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型。
 *              第三个参数，double类型的threshold1，第一个滞后性阈值。
 *              第四个参数，double类型的threshold2，第二个滞后性阈值。
 *              第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3。
 *              第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false。
 *         4.Sobel()函数介绍：
 *              void Sobel (InputArray src,OutputArray dst,int ddepth,int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT );
 *              第一个参数，InputArray 类型的src，为输入图像，填Mat类型即可。
 *              第二个参数，OutputArray类型的dst，即目标图像，函数的输出参数，需要和源图片有一样的尺寸和类型。
 *              第三个参数，int类型的ddepth，输出图像的深度，支持如下src.depth()和ddepth的组合：
 *                  若src.depth() = CV_8U, 取ddepth =-1/CV_16S/CV_32F/CV_64F
 *                  若src.depth() = CV_16U/CV_16S, 取ddepth =-1/CV_32F/CV_64F
 *                  若src.depth() = CV_32F, 取ddepth =-1/CV_32F/CV_64F
 *                  若src.depth() = CV_64F, 取ddepth = -1/CV_64F
 *              第四个参数，int类型dx，x 方向上的差分阶数。
 *              第五个参数，int类型dy，y方向上的差分阶数。
 *              第六个参数，int类型ksize，有默认值3，表示Sobel核的大小;必须取1，3，5或7。
 *              第七个参数，double类型的scale，计算导数值时可选的缩放因子，默认值是1，表示默认情况下是没有应用缩放的。我们可以在文档中查阅getDerivKernels的相关介绍，来得到这个参数的更多信息。
 *              第八个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
 *              第九个参数， int类型的borderType，我们的老朋友了（万年是最后一个参数），边界模式，默认值为BORDER_DEFAULT。
 *          5.Laplacian()函数介绍：
 *              void Laplacian(InputArray src,OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, intborderType=BORDER_DEFAULT );
 *              第一个参数，InputArray类型的image，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位图像。
 *              第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和通道数。
 *              第三个参数，int类型的ddept，目标图像的深度。
 *              第四个参数，int类型的ksize，用于计算二阶导数的滤波器的孔径尺寸，大小必须为正奇数，且有默认值1。
 *              第五个参数，double类型的scale，计算拉普拉斯值的时候可选的比例因子，有默认值1。
 *              第六个参数，double类型的delta，表示在结果存入目标图（第二个参数dst）之前可选的delta值，有默认值0。
 *              第七个参数， int类型的borderType，边界模式，默认值为BORDER_DEFAULT。
 * 软件及环境：clion  opencv3  gcc-9  g++-9
 * */
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){
    //载入原始图
    Mat srcImage = imread("/Users/hiyoshikei/Desktop/code_all/opencv_4/test.jpg");//读取图片
    //显示原始图
    imshow("test", srcImage);
    Mat grayImage;
    //将原图转换为灰度图像
    cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

    /********************************Canny*************************/
    Mat edge;
    blur(grayImage, edge, Size(3, 3));    //先使用3*3来进行降噪
    Canny(edge, edge, 3, 9, 3);    //运行Canny算子
    imshow("Canny", edge);//显示canny算子结果
    /********************************Canny*************************/

    /********************************Sobel*************************/
    //创建 grad_x 和 grad_y 矩阵
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y,dst;
    //求X方向梯度
    Sobel( srcImage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );//计算绝对值，并将结果转换成8位
    imshow("X--Sobel", abs_grad_x);
    //求Y方向梯度
    Sobel( srcImage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );//计算绝对值，并将结果转换成8位
    imshow("Y--Sobel", abs_grad_y);
    //合并梯度(近似)
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
    imshow("Final--Sobel", dst);
    /********************************Sobel*************************/

    /********************************Laplacian*************************/
    Mat src_gray,dst1, abs_dst;
    //使用高斯滤波消除噪声
    GaussianBlur( srcImage, srcImage, Size(3,3), 0, 0, BORDER_DEFAULT );
    //转换为灰度图
    cvtColor( srcImage, src_gray, COLOR_RGB2GRAY );
    //使用Laplace函数
    Laplacian( src_gray, dst1, CV_16S, 3, 1, 0, BORDER_DEFAULT );
    //计算绝对值，并将结果转换成8位
    convertScaleAbs( dst1, abs_dst );
    //显示效果图
    imshow( "Laplace", abs_dst );
    /********************************Laplacian*************************/

    waitKey(0);
}
