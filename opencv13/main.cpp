#include <iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<fstream>
#include <string>

using namespace std;
using namespace cv;

float **Points=nullptr;//全局指针，存放坐标数组
int Points_count=0;

//读取txt文件
void readfile(string filename)
{
    ifstream file(filename);
    if (!file) //判断文件打开是否有问题
    {
        cout << "Error: can 't open the file（出错，无法打开文件）： " <<filename <<endl;
        exit(1);
    }
    string Line;
    string buf;
    int i=0,j=0;

    //动态申请二维数组存放坐标
    Points=(float**)malloc(sizeof(float*)*30);
    for(int k=0;k<30;k++){
        *(Points+k)=(float*)malloc(sizeof(float)*5);
    }

    //打开文件，把坐标存入数组
    if(file)
    {
        cout<<"文件打开成功";
        while (getline(file, Line)) {//按行读取
            stringstream split(Line);//按空格分割
            while(split>>buf){
                Points[i][j]=stof(buf);
                j++;
            }
            i++;
            j=0;//清零列标
            Points_count++;
        }
    }
    file.close();
}

int main(){
    //从文件中读取坐标点
    readfile("/Users/hiyoshikei/Desktop/code_all/opencv13/point1.txt");
    //显示文件的坐标点
    cout<<"全部坐标点如下：(前三个为世界坐标系下的点的坐标，后两个为图像像素点的坐标）"<<endl;
    for(int l=0;l<Points_count;l++)
    {
        for (int m=0; m<5; m++) {
            cout<<Points[l][m]<<" ";
        }
        cout<<endl;
    }

    //选取6个标定点
    float Points_cali[6][5];
    int index[6]={0,1,2,3,4,5};
    int ii=0;
    cout<<"标定点如下："<<endl;
    for (int i=0; i<6; i++) {
        for (int j=0; j<5; j++) {
            Points_cali[i][j]=Points[index[ii]][j];
        }
        ii++;
    }

    //其余的点
    float Points_remain[6][5];
    int index_remain[6]={6,7,8,9,10,11};
    ii=0;
    cout<<"验证点如下："<<endl;
    for(int i=0;i<6;i++){
        for (int j=0; j<5; j++) {
            Points_remain[i][j]=Points[index_remain[ii]][j];
            cout<<Points_remain[i][j]<<" "<<endl;
        }
        ii++;
    }
    //构造A矩阵
    ii=0;
    float a[12][11]={0};
    for (int i=0; i<12; i++) {
        if(i%2==0)
        {
            a[i][0]=Points_cali[ii][0];
            a[i][1]=Points_cali[ii][1];
            a[i][2]=Points_cali[ii][2];
            a[i][3]=1;
            a[i][8]=-Points_cali[ii][0]*Points_cali[ii][3];
            a[i][9]=-Points_cali[ii][1]*Points_cali[ii][3];
            a[i][10]=-Points_cali[ii][2]*Points_cali[ii][3];
        }
        else{
            a[i][4]=Points_cali[ii][0];
            a[i][5]=Points_cali[ii][1];
            a[i][6]=Points_cali[ii][2];
            a[i][7]=1;
            a[i][8]=-Points_cali[ii][0]*Points_cali[ii][4];
            a[i][9]=-Points_cali[ii][1]*Points_cali[ii][4];
            a[i][10]=-Points_cali[ii][2]*Points_cali[ii][4];
            ii++;
        }
    }
    cout<<endl<<"A矩阵:"<<endl;
    Mat A(12, 11, CV_32F,a);//存放A矩阵
    cout<<A<<endl;

    //构造U矩阵
    float u[12]={0};
    ii=0;
    for(int i=0;i<12;i=i+2){
        u[i]=Points_cali[ii][3];
        u[i+1]=Points_cali[ii][4];
        ii++;
    }
    Mat U(12,1,CV_32F,u);
    cout<<endl<<"U矩阵："<<endl;
    cout<<U<<endl;

    //////////////////////////////计算得到L矩阵
    Mat L=Mat::zeros(11, 1, CV_32F);
    L=(((A.t())*A).inv())*(A.t())*U;
    cout<<endl<<"L矩阵如下："<<endl<<L<<endl;
    //把L矩阵转化成3*4形式，最后一个l12取1
    Mat L_34=(Mat_<float>(3, 4)<<L.at<float>(0,0),L.at<float>(1,0),L.at<float>(2,0),L.at<float>(3,0),L.at<float>(4,0),L.at<float>(5,0),L.at<float>(6,0),L.at<float>(7,0),L.at<float>(8,0),L.at<float>(9,0),L.at<float>(10,0),1);//L矩阵的3*4形式
    cout<<endl<<"P矩阵如下："<<endl<<L_34<<endl;

    //计算重投影误差
    //计算用于标定的坐标点重投影误差
    cout<<endl<<"标定点的误差计算：";
    float err_caliPoints[6]={0};
    float err_caliPoints_mean=0;
    float err_relative=0;
    float u_restruct,v_restruct;
    for (int i=0; i<6; i++) {
        u_restruct=(Points_cali[i][0]*L.at<float>(0,0)+Points_cali[i][1]*L.at<float>(1,0)+Points_cali[i][2]*L.at<float>(2,0)+L.at<float>(3,0))
                        /(Points_cali[i][0]*L.at<float>(8,0)+Points_cali[i][1]*L.at<float>(9,0)+Points_cali[i][2]*L.at<float>(10,0)+1);
        v_restruct=(Points_cali[i][0]*L.at<float>(4,0)+Points_cali[i][1]*L.at<float>(5,0)+Points_cali[i][2]*L.at<float>(6,0)+L.at<float>(7,0))
                        /(Points_cali[i][0]*L.at<float>(8,0)+Points_cali[i][1]*L.at<float>(9,0)+Points_cali[i][2]*L.at<float>(10,0)+1);
        err_caliPoints[i]=sqrt(pow(u_restruct-Points_cali[i][3], 2)+pow(v_restruct-Points_cali[i][4], 2));
        cout<<endl<<"标定点"<<i+1<<"的重投影误差："<<err_caliPoints[i]<<"   相对误差："<<abs(err_caliPoints[i])/sqrt(pow(Points_cali[i][3],2)+pow(Points_cali[i][4], 2))<<endl;
        err_caliPoints_mean=err_caliPoints_mean+err_caliPoints[i];
        err_relative=err_relative+abs(err_caliPoints[i])/sqrt(pow(Points_cali[i][3],2)+pow(Points_cali[i][4], 2));
    }
    cout<<"重投影误差均值："<<err_caliPoints_mean/6<<"   "<<"相对误差均值："<<err_relative/6<<endl;

//    //计算重投影误差
//    //计算用于标定的坐标点重投影误差
//    cout<<endl<<"验证点的误差计算：";
//    float err_Points_remain[6]={0};
//    float err_Points_remain_mean=0;
//    float err_Points_remain_relative=0;
//    float u_restruct2,v_restruct2;
//    for (int i=0; i<6; i++) {
//        u_restruct2=(Points_remain[i][0]*L.at<float>(0,0)+Points_remain[i][1]*L.at<float>(1,0)+Points_remain[i][2]*L.at<float>(2,0)+L.at<float>(3,0))
//                   /(Points_remain[i][0]*L.at<float>(8,0)+Points_remain[i][1]*L.at<float>(9,0)+Points_remain[i][2]*L.at<float>(10,0)+1);
//        v_restruct2=(Points_remain[i][0]*L.at<float>(4,0)+Points_remain[i][1]*L.at<float>(5,0)+Points_remain[i][2]*L.at<float>(6,0)+L.at<float>(7,0))
//                   /(Points_remain[i][0]*L.at<float>(8,0)+Points_remain[i][1]*L.at<float>(9,0)+Points_remain[i][2]*L.at<float>(10,0)+1);
//        err_Points_remain[i]=sqrt(pow(u_restruct2-Points_remain[i][3], 2)+pow(v_restruct2-Points_remain[i][4], 2));
//        cout<<endl<<"验证点"<<i+1<<"的重投影误差："<<err_Points_remain[i]<<"   相对误差："<<abs(err_Points_remain[i])/sqrt(pow(Points_remain[i][3],2)+pow(Points_cali[i][4], 2))<<endl;
//        err_Points_remain_mean=err_Points_remain_mean+err_Points_remain[i];
//        err_Points_remain_relative=err_Points_remain_relative+abs(err_Points_remain[i])/sqrt(pow(Points_remain[i][3],2)+pow(Points_remain[i][4], 2));
//    }
//    cout<<"重投影误差均值："<<err_Points_remain_mean/6<<"   "<<"相对误差均值："<<err_Points_remain_relative/6<<endl;
//
//    if(err_Points_remain_mean/6<5 && err_Points_remain_relative/6<1)
//    {
//        cout<<"误差在允许范围内"<<endl;
//    }

    //释放空间
    for(int i = 0; i < 30;i++){
        free(*(Points+i));
    }
}