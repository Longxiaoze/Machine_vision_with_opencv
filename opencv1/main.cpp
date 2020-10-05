/*creat by liuzenong in CHD
 * Open the test.jpg
 *
 *  date:2020.09.07
 * */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int main() {
    Mat srcImage = imread("/Users/hiyoshikei/Desktop/code_all/opencv1/test.jpg");
    imshow("[img]", srcImage);
    waitKey(0);
    return 0;
}
