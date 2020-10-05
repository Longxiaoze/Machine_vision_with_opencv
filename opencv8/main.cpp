/*creat by 龙笑泽  date：2020.10.02
 * 文件说明：使用opencv库读取三通道彩色图
 *         键盘输入缩小放大方式，对图像进行缩小放大
 *         显示原图片和缩小放大后的图片
 * trick: 1.图片输入和输出应为完整路径（可能是我建项目在桌面的原因），仅输入输出文件名无法打开和保存
 *        2.命名显示窗口不能有汉字，否则无法显示标题
 * 软件及环境：clion  opencv3  gcc-9  g++-9
 * */
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

//图片的缩小与放大
int main()
{
    Mat img = imread("/Users/hiyoshikei/Desktop/code_all/opencv_4/test.jpg");//读取图片
    imshow("test", img);
    if (!img.data) {
        cout << "读入图片错误！" << endl;
        return -1;
    }
    int x,y;
    cout << "请输入图像缩小/放大的方式：（0：图像变换后的形状；1：图像缩小/放大的比率）";
    cin >> x;

    if (x==0)
    {
        cout<<"请输入变换后的图像的行列值："<<endl;
        int a,b;
        cin>>a>>b;
        Mat dst = Mat::zeros(a, b, CV_8UC3);
        resize(img, dst, dst.size());
        imshow("test", img);
        imshow("resize_img", dst);
    }
    else if(x==1)
    {
        cout<<"请输入变换的长宽比例："<<endl;
        int m,p;
        cin>>m>>p;
        Mat dst1;
        resize(img, dst1, Size(),m,p);
        imshow("test", img);
        imshow("resize_img", dst1);
    }
    else cout<<"请正确输入，输入数字即可";
    waitKey(0);
}



 
