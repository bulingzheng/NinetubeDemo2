#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
    FileStorage fs0("config.xml", FileStorage::WRITE);
    string normalpath = "rm_pics//normal//";
    string targetpath = "rm_pics//target//";
    string numberpath = "test_images//";
    /*    Mat normal=imread(normalpath+"1.png");
        imshow("1.png",normal);
        waitKey(0);
    */
    fs0<<"normalpath"<<normalpath;
    fs0<<"targetpath"<<targetpath;
    fs0<<"numberpath"<<numberpath;
    int maxNumber=892;
    fs0<<"maxNumber"<<maxNumber;
    int delayTime=3000;
    fs0<<"delayTime"<<delayTime;
    fs0.release();
    cout<<"creat config.xml finished....."<<endl;
    return 0;

}

