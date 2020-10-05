/*creat by 龙笑泽 in CHD
 * Open the test.jpg
 *
 *  date:2020.09.07
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main() {
    Mat srcImage = imread("test.jpg");
    imshow("[img]", srcImage);
    waitKey(0);
    return 0;
}
