#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()    //生成bg.png
{
    Mat bg(530,910,CV_8UC1,Scalar(0));
    Mat white(110,210,CV_8UC1,Scalar(255));

    Rect rects[9];
    rects[0]=Rect(70,50,210,110);
    rects[1]=Rect(70+280,50,210,110);
    rects[2]=Rect(70+560,50,210,110);
    /*******/
    rects[3]=Rect(70,50+160,210,110);
    rects[4]=Rect(70+280,50+160,210,110);
    rects[5]=Rect(70+560,50+160,210,110);
    /*******/
    rects[6]=Rect(70,50+320,210,110);
    rects[7]=Rect(70+280,50+320,210,110);
    rects[8]=Rect(70+560,50+320,210,110);

    for(int i=0;i<9;i++)
    {
        white.copyTo(bg(rects[i]));
    }
    imshow("bg",bg);
    imwrite("bg.png",bg);
    waitKey(0);
    return 0;
}
