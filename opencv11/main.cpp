#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
    cv::Mat image1 = cv::imread("/Users/hiyoshikei/Desktop/code_all/opencv2/test.jpg");

    Mat image, gray, hsv, hsvChannels[3];
    pyrDown(image1, image);
    cvtColor(image,gray,COLOR_BGR2GRAY);

    namedWindow("source image", 2);
    imshow("source image",image);
    namedWindow("gray", 2);
    imshow("gray",gray);
//    imwrite("E:/gray.jpg", gray);

    cvtColor(image, hsv, COLOR_BGR2HSV);
    split(hsv,hsvChannels);

    namedWindow("Hue", 2);
    imshow("Hue",hsvChannels[0]);
//    imwrite("E:/Hue.jpg", hsvChannels[0]);

    namedWindow("Saturation", 2);
    imshow("Saturation", hsvChannels[1]);
//    imwrite("E:/Saturation.jpg", hsvChannels[1]);

    namedWindow("Value", 2);
    imshow("Value", hsvChannels[2]);
//    imwrite("E:/Value.jpg", hsvChannels[2]);
    waitKey();
    return 0;
}
//
//运行结果：
//
//图二：灰度图；
//
//图三：色度；
//
//图四：饱和度；
//
//图五：亮度；
//
//以上，HSI和HSV差不多。
//
//由上图也可以看出，灰度图像具有原始图像的大部分信息，因而在图像处理中，多是以灰度图像进行操作处理，以提高处理速度。
