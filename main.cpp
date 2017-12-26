#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdlib.h>
using namespace std;
using namespace cv;


int main()
{
    FileStorage fs("config.xml", FileStorage::READ);
    string normalpath, targetpath, numberpath;
    fs["normalpath"] >> normalpath;
    fs["targetpath"] >> targetpath;
    fs["numberpath"] >> numberpath;
    int maxNumber;
    fs["maxNumber"] >> maxNumber;
    int delayTime;
    fs["delayTime"] >> delayTime;
    fs.release();
    cout << normalpath << endl << targetpath << endl << numberpath << endl;
    cout << maxNumber << endl << delayTime << endl;
    Rect rects[9];
    rects[0] = Rect(70, 50, 210, 110);
    rects[1] = Rect(70 + 280, 50, 210, 110);
    rects[2] = Rect(70 + 560, 50, 210, 110);
    /*********/
    rects[3] = Rect(70, 50 + 160, 210, 110);
    rects[4] = Rect(70 + 280, 50 + 160, 210, 110);
    rects[5] = Rect(70 + 560, 50 + 160, 210, 110);
    /********/
    rects[6] = Rect(70, 50 + 320, 210, 110);
    rects[7] = Rect(70 + 280, 50 + 320, 210, 110);
    rects[8] = Rect(70 + 560, 50 + 320, 210, 110);

    Mat Back = imread("bg.png");
    if(Back.empty())
    {
        cout << "没有读取到bg.png" << endl;
        return -1;
    }

    RNG rng;
    //保存1-9这九个数字
    int aa[9];
    for(int i = 0; i < 9; i++)
    {
        aa[i] = i + 1;
    }
    int bb[9];
    string cc[9];
    bool dafu = true;
    while(true)
    {
        if(dafu == 1)
        {
            Mat bg_ = Back.clone();
            //imshow("九宫格demo", Back);
            //waitKey(100);

            for(int i = 0; i < 30; i++) //让aa[i]对应的值是随机的
            {
                swap(aa[rng.uniform(0, 9)], aa[rng.uniform(0, 9)]);
            }
            for(int i = 0; i < 9; i++)
            {
                bb[i] = rng.uniform(1, maxNumber); //在0-892之间产生随机数
            }
            for(int i = 0; i < 9; i++)
            {
                if(bb[i] < 10)
                {
                    cc[i] = "0000" + to_string(bb[i]) + ".png";
                }
                else if(bb[i] >= 10 && bb[i] < 100)
                {
                    cc[i] = "000" + to_string(bb[i]) + ".png";
                }
                else
                {
                    cc[i] = "00" + to_string(bb[i]) + ".png";
                }
            }

            vector<Mat>number_mat(9);
            for(int i = 0; i < 9; i++)
            {
                string filename = numberpath + to_string(aa[i]) + "_" + cc[i];
                Mat m = imread(filename);
                if(m.empty())
                {
                    cout << "没找到number图片" << endl;
                    return -1;
                }
                resize(m, m, Size(210, 110));
                threshold(m, m, 100, 255, THRESH_BINARY_INV);
                blur(m, m, Size(3, 3));
                number_mat[i] = m;
                //imshow("m", m);
                //waitKey(0);
            }
            for(int i = 0; i < 9; i++)
            {
                number_mat[i].copyTo(bg_(rects[i]));
                imshow("九宫格", bg_);
                waitKey(100);
            }

            int key = waitKey(delayTime);
            if(key == 27)
                break;
            if(key == 'c')
                dafu = false;
        }
        /*********************/
        if(dafu == false)
        {
            Mat bg_ = Back.clone();
            //imshow("九宫格demo", Back);
            //waitKey(100);

            for(int i = 0; i < 30; i++) //让aa[i]对应的值是随机的
            {
                swap(aa[rng.uniform(0, 9)], aa[rng.uniform(0, 9)]);
            }

            vector<Mat>number_mat(9);
            for(int i = 0; i < 9; i++)
            {
                string filename;
                filename = normalpath + to_string(aa[i]) + ".png";
                Mat m = imread(filename);
                if(m.empty())
                {
                    cout << "没找到图片" << endl;
                    return -1;
                }
                resize(m, m, Size(210, 110));
                blur(m, m, Size(3, 3));
                number_mat[i] = m;

            }
            for(int i = 0; i < 9; i++)      //生成战车底图
            {
                number_mat[i].copyTo(bg_(rects[i]));

            }
            Mat zhancheditu=bg_.clone();

            int dddd =rng.uniform(0, 9);
            for(int i = 1; i < 10; i++)
            {
                string targetname = targetpath + to_string(i) + ".png";
                Mat m = imread(targetname);
                if(m.empty())
                {
                    cout << "没找到图片" << endl;
                    return -1;
                }
                resize(m, m, Size(210, 110));
                blur(m, m, Size(3, 3));
                m.copyTo(zhancheditu(rects[dddd]));
                imshow("九宫格", zhancheditu);
                int key = waitKey(300);
                if(key ==27)
                    break;
                if(key == 'c')
                    dafu = true;
            }
        }

    }
    return 0;
}

string to_string(int &x)
{
    stringstream ss;
    string y;
    ss << x;
    ss >> y;
    return y;
}






