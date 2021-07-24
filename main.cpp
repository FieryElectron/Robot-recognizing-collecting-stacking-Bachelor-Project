#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <math.h>
#include "radar/CYY_radar.h"
//#include "viz/CYY_viz.h"
#include "Com_Ard/com_ard.h"
#include "CubeOrder/CubeOrder.h"
//#include "MPU6050/MPU.h"

#define PI 3.141592653589793

#define INITIAL 0

#define FORWARD 1
#define BACKWARD 2

#define MOVE_LEFT 3
#define MOVE_RIGHT 4
#define MOVE_STRAIGHT 5

#define TURNLEFT 6
#define TURNRIGHT 7
#define STOP_FOR_WHEEL 8

#define FRONT_CORRECTION 9
#define FRONT_CORRECTION_LEFT 10
#define FRONT_CORRECTION_RIGHT 11

#define BACK_CORRECTION 12
#define BACK_CORRECTION_LEFT 13
#define BACK_CORRECTION_RIGHT 14

#define FRONT_DIS_CORRECTION 15
#define FRONT_FAR 16
#define FRONT_CLOSE 17

#define BACK_DIS_CORRECTION 18
#define BACK_FAR 19
#define BACK_CLOSE 20

#define RECOGNIZE_CUBE_ORDER 21
#define STOP_FOR_PICK 22
#define PRESS_BUTTON 23
#define ARRANGE_CUBE 24
#define RELEASE_CUBE 25

#define END 26

#define leftside 0
#define rightside 1

bool Side_Flag = 0;

char TimesOut = 0;
char *Cube_Cmd_Sequence;

char STOP_Wheel_CMD_Index = 0;
char STOP_Wheel_State_Index = 0;

char STOP_PICK_CMD_Index = 0;
char STOP_PICK_State_Index = 0;

char *Stop_Wheel_Cmd[20] = {
    "S", "F", "e", "S", "S", "B", "e", "S", "S", "S", "F", "e", "B", "S", "S", "E", "F", "S", "E"};

char *Stop_Pick_Cmd[10] = {
    "B", "S", "S", "A", "S"};

char Stop_Wheel_State[20] = {
    BACK_CORRECTION, FORWARD, TURNLEFT, FRONT_DIS_CORRECTION, STOP_FOR_PICK, BACKWARD, TURNLEFT,
    FRONT_DIS_CORRECTION, FRONT_CORRECTION,
    STOP_FOR_PICK, FORWARD, TURNLEFT, BACKWARD, BACK_DIS_CORRECTION, BACK_CORRECTION, RELEASE_CUBE, FORWARD, END};

char Stop_Pick_State[6] = {
    PRESS_BUTTON, RECOGNIZE_CUBE_ORDER, STOP_FOR_WHEEL, ARRANGE_CUBE, STOP_FOR_WHEEL};

char Forward_Dis_Index = 0;
char Backward_Dis_Index = 0;

char Front_Correction_Dis_Index = 0;
//char Back_Correction_Dis_Index = 0;

char Turn_Left_Index = 0;
char Turn_Right_Index = 0;
//1020
int Forward_Dis[10] = {1065, 800, 600, 600};
int Backward_Dis[10] = {500, 400};
int Front_Correction_Dis[10] = {355, 400};
//int Back_Correction_Dis[10] = {};

char Robot_State = INITIAL;
char Sub_State = INITIAL;

bool turn_flag = 0;
bool match_flag = 0;
double dis_mark = 0;

double F_dif = 0;
double ang_fl = 2;
double ang_fr = 358;
double ang_bl = 177;
double ang_br = 183;

void Forwarding(double bdl, double bdr, double fdl, double fdr)
{
    switch (Forward_Dis_Index)
    {

    case 0:
        if ((bdl + bdr) / 2 >= Forward_Dis[Forward_Dis_Index])
        {
            ++Forward_Dis_Index;
            SendMovArd("S");
            cout << "STOP!" << endl;
            Robot_State = STOP_FOR_WHEEL;
            ang_bl = 177;
            ang_br = 183;
        }
        else if (bdl - bdr > F_dif && Sub_State != MOVE_LEFT)
        {
            SendMovArd("l");
            cout << "MOVE_LEFT!"
                 << "L: " << bdl << "R:" << bdr << endl;
            Sub_State = MOVE_LEFT;
        }
        else if (bdl - bdr < F_dif && Sub_State != MOVE_RIGHT)
        {
            SendMovArd("r");
            cout << "MOVE_RIGHT!"
                 << "L: " << bdl << "R:" << bdr << endl;
            Sub_State = MOVE_RIGHT;
        }
        else if (bdl - bdr == F_dif && Sub_State != MOVE_STRAIGHT)
        {
            SendMovArd("s");
            cout << "MOVE_STRAIGHT!"
                 << "L: " << bdl << "R:" << bdr << endl;
            Sub_State = MOVE_STRAIGHT;
        }
        break;
    case 1:
        if ((fdl + fdr) / 2 <= Forward_Dis[Forward_Dis_Index])
        {
            ++Forward_Dis_Index;
            SendMovArd("S");
            cout << "STOP!" << endl;
            Robot_State = STOP_FOR_WHEEL;
        }
        else if (fdl > fdr && Sub_State != MOVE_LEFT)
        {
            SendMovArd("r");
            cout << "MOVE_LEFT!"
                 << "L: " << fdl << "R:" << fdr << endl;
            Sub_State = MOVE_LEFT;
        }
        else if (fdl < fdr && Sub_State != MOVE_RIGHT)
        {
            SendMovArd("l");
            cout << "MOVE_RIGHT!"
                 << "L: " << fdl << "R:" << fdr << endl;
            Sub_State = MOVE_RIGHT;
        }
        else if (fdl == fdr && Sub_State != MOVE_STRAIGHT)
        {
            SendMovArd("s");
            cout << "MOVE_STRAIGHT!"
                 << "L: " << fdl << "R:" << fdr << endl;
            Sub_State = MOVE_STRAIGHT;
        }
        break;
    case 2:
        if ((bdl + bdr) / 2 >= Forward_Dis[Forward_Dis_Index])
        {
            ++Forward_Dis_Index;
            SendMovArd("S");
            cout << "STOP!---" << endl;
            Robot_State = STOP_FOR_WHEEL;
        } /*else if(bdl>bdr && Sub_State != MOVE_LEFT){
            SendMovArd("l");
            cout<<"MOVE_LEFT!"<<"L: "<<fdl<<"R:"<<fdr<<endl;
            Sub_State = MOVE_LEFT;
        }else if(bdl<bdr && Sub_State != MOVE_RIGHT){
            SendMovArd("r");
            cout<<"MOVE_RIGHT!"<<"L: "<<fdl<<"R:"<<fdr<<endl;
            Sub_State = MOVE_RIGHT;
        }else if(bdl == bdr && Sub_State != MOVE_STRAIGHT){
            SendMovArd("s");
            cout<<"MOVE_STRAIGHT!"<<"L: "<<fdl<<"R:"<<fdr<<endl;
            Sub_State = MOVE_STRAIGHT;
        }*/
        break;
    }
}

void Backwarding(double bdl, double bdr, double fdl, double fdr)
{
    switch (Backward_Dis_Index)
    {
    case 0:
        if ((fdl + fdr) / 2 >= Backward_Dis[Backward_Dis_Index])
        {
            SendMovArd("S");
            ++Backward_Dis_Index;
            cout << "STOP!" << endl;
            Robot_State = STOP_FOR_WHEEL;
        }
        else if (fdl > fdr && Sub_State != MOVE_RIGHT)
        {
            SendMovArd("r");
            Sub_State = MOVE_RIGHT;
            cout << "MOVE_LEFT! "
                 << "l: " << fdl << " r: " << fdr << endl;
        }
        else if (fdl < fdr && Sub_State != MOVE_LEFT)
        {
            SendMovArd("l");
            Sub_State = MOVE_LEFT;
            cout << "MOVE_RIGHT! "
                 << "l: " << fdl << " r: " << fdr << endl;
        }
        else if (fdl == fdr && Sub_State != MOVE_STRAIGHT)
        {
            SendMovArd("s");
            Sub_State = MOVE_STRAIGHT;
            cout << "MOVE_STRAIGHT! "
                 << "l: " << fdl << " r: " << fdr << endl;
        }
        break;
    case 1:
        if ((bdl + bdr) / 2 <= Backward_Dis[Backward_Dis_Index])
        {
            SendMovArd("S");
            ++Backward_Dis_Index;
            cout << "STOP!" << endl;
            Robot_State = STOP_FOR_WHEEL;
        }
        else if (bdl > bdr && Sub_State != MOVE_LEFT)
        {
            SendMovArd("l");
            Sub_State = MOVE_LEFT;
            cout << "MOVE_LEFT! "
                 << "l: " << bdl << " r: " << bdr << endl;
        }
        else if (bdl < bdr && Sub_State != MOVE_RIGHT)
        {
            SendMovArd("r");
            Sub_State = MOVE_RIGHT;
            cout << "MOVE_RIGHT! "
                 << "l: " << bdl << " r: " << bdr << endl;
        }
        else if (bdl == bdr && Sub_State != MOVE_STRAIGHT)
        {
            SendMovArd("s");
            Sub_State = MOVE_STRAIGHT;
            cout << "MOVE_STRAIGHT! "
                 << "l: " << bdl << " r: " << bdr << endl;
        }
        break;
    }
}

void Lefting(double bdl, double bdr, double fdl, double fdr)
{
    switch (Turn_Left_Index)
    {
    case 0:
        if (turn_flag)
        {
            if (fdl >= fdr)
            {
                SendMovArd("S");
                ++Turn_Left_Index;
                Robot_State = STOP_FOR_WHEEL;
            }
        }
        else
        {
            if ((fdl + fdr) / 2 <= 450)
            {
                ++turn_flag;
            }
        }
        break;
    case 1:
    {
        if (fdl < 400 && fdr < 400)
        {
            SendMovArd("S");
            ++Turn_Left_Index;
            Robot_State = STOP_FOR_WHEEL;
        }
        break;
    }
    case 2:
    {
        if ((bdl + bdr) / 2 <= 500)
        {
            SendMovArd("S");
            ++Turn_Left_Index;
            Robot_State = STOP_FOR_WHEEL;
        }
        break;
    }
    }
}

void Righting(double bdl, double bdr, double fdl, double fdr)
{
    switch (Turn_Right_Index)
    {
    case 0:
        if (turn_flag)
        {
            if (fdl <= fdr)
            {
                SendMovArd("S");
                ++Turn_Right_Index;
                Robot_State = STOP_FOR_WHEEL;
            }
        }
        else
        {
            if ((fdl + fdr) / 2 <= 450)
            {
                ++turn_flag;
            }
        }
        break;
    case 1:
    {
        if (fdl < 400 && fdr < 400)
        {
            SendMovArd("S");
            ++Turn_Right_Index;
            Robot_State = STOP_FOR_WHEEL;
        }
        break;
    }
    case 2:
    {
        if ((bdl + bdr) / 2 <= 600)
        {
            SendMovArd("S");
            ++Turn_Right_Index;
            Robot_State = STOP_FOR_WHEEL;
        }
        break;
    }
    }
}

/*
double GetMid(double* arr){
    for(char j = 0;j<3;++j){
        for(char i = j+1;i<5;++i){
            if(arr[j] > arr[i]){
                double temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    return arr[2];
}
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 1024
char recvline[MAXLINE], sendline[MAXLINE];

/*
 * int main( ){
    char *servInetAddr = "172.20.10.11";
    int socketfd;
    struct sockaddr_in sockaddr;

    int n;

    socketfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(10004);

    inet_pton(AF_INET,servInetAddr,&sockaddr.sin_addr);

    if((connect(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))) < 0 ){
        printf("connect error %s errno: %d\n",strerror(errno),errno);
        exit(0);
    }

    n = recv(socketfd,recvline,MAXLINE,0);
    recvline[n] = '\0';
    cout<<recvline<<endl;
    close(socketfd);

    printf("Recving finished!\n");
    //exit(0);
    return 0;
}
*/

/*
int main(){
        system("raspistill -o tar.jpg  -w 600 -h -rot 180 400 -t 500");//system("raspistill -o tar.jpg -rot 180 -w 600 -h 400 -t 500");
           int iLowH = 23;
           int iHighH = 100;
           int iLowS = 0;
           int iHighS = 255;
           int iLowV = 0;
           int iHighV = 255;

           namedWindow("Results", CV_WINDOW_AUTOSIZE);

           createTrackbar("LowH", "Results", &iLowH, 179);
           createTrackbar("HighH", "Results", &iHighH, 179);
           createTrackbar("LowS", "Results", &iLowS, 255);
           createTrackbar("HighS", "Results", &iHighS, 255);
           createTrackbar("LowV", "Results", &iLowV, 255);
           createTrackbar("HighV", "Results", &iHighV, 255);

           int iMinBlobSize = 8;
           createTrackbar("MinBlobSize*1000", "Results", &iMinBlobSize, 100);

           while (true){

               Mat imgOriginal = imread("tar.jpg", CV_LOAD_IMAGE_UNCHANGED);
               Mat imgHSV;
               cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

               Mat imgThresholded;
               inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
               //cv::imshow("Thresholded Image", imgThresholded);

               erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
               dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

               dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
               erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );


               /// Blob Analysis:
               ///
               /// 1. Get the blobs (i.e. their contour)
               /// 2. Get the moments
               /// 3. Get the mass centers
               /// 4. Draw blobs
               /// 5. Blob filtering
               /// 6. Draw filtered blobs

               // 1. Get the blobs (i.e. their contour)
               vector<vector<Point> >contours;
               vector<Vec4i> hierarchy;
               findContours( imgThresholded,
                             contours,
                             hierarchy,
                             CV_RETR_TREE,
                             CV_CHAIN_APPROX_SIMPLE,
                             Point(0, 0) );

               // 2. Get the moments
               vector<Moments> mu(contours.size() );
               for( int i = 0; i < contours.size(); i++ ){
                   mu[i] = moments( contours[i], false );
               }
               //  3. Get the mass centers (centroids)
               vector<Point2f> mc( contours.size() );
               for( int i = 0; i < contours.size(); i++ ){
                   mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
               }
               // 4. Draw blobs
               RNG rng(12345);
               Mat blobImg = Mat::zeros( imgThresholded.size(), CV_8UC3 );
               for( int i = 0; i< contours.size(); i++ ){
                   Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                   drawContours( blobImg, contours, i, color, 2, 8, hierarchy, 0, Point() );
                   circle( blobImg, mc[i], 4, color, -1, 8, 0 );
               }
               //cv::imshow( "blobImg", blobImg );
               // 5. Blob filtering
               vector<vector<Point> > contours_filt;
               vector<Vec4i> hierarchy_filt;
               vector<Moments> mu_filt;
               vector<Point2f> mc_filt;
               // Filter blobs w.r.t. to size
               int minBlobArea = iMinBlobSize*1000; // Minimum Pixels for valid blob
               for( int i = 0; i< contours.size(); i++ ){
                   if (mu[i].m00 > minBlobArea){
                       contours_filt.push_back(contours[i]);
                       hierarchy_filt.push_back(hierarchy[i]);
                       mu_filt.push_back(mu[i]);
                       mc_filt.push_back(mc[i]);
                   }
               }
               // 6. Draw filtered blobs
               Mat blobImg_filt = Mat::zeros( imgThresholded.size(), CV_8UC3 );;
               cout<< "------" <<endl;
               for( int i = 0; i< contours_filt.size(); i++ ){
                   cout<< mc_filt[i].x <<endl;
                   Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
                   drawContours( blobImg_filt, contours_filt, i, color, 2, 8, hierarchy_filt, 0, Point() );
                   circle( blobImg_filt, mc_filt[i], 4, color, -1, 8, 0 );

                   drawContours( imgOriginal, contours_filt, i, color, 2, 8, hierarchy_filt, 0, Point() );
                   circle( imgOriginal, mc_filt[i], 4, color, -1, 8, 0 );
               }
               cout<< "======" <<endl;
               cv::imshow( "blobImg_filt", blobImg_filt );
               cv::imshow("Results", imgOriginal);

               if (waitKey(30) == 27){
                   cout << "esc key is pressed by user" << endl;
                   break;
               }
           }
    return 0;
}
*/

int main()
{
    SerialIniMov();
    SerialIniPick();
    iniRadar();
    double ang;
    int qua;

    while (true)
    {
        rplidar_response_measurement_node_t nodes[8192];
        size_t count = _countof(nodes);
        op_result = drv->grabScanData(nodes, count);
        if (IS_OK(op_result))
        {
            drv->ascendScanData(nodes, count);
            double bdl, bdr, fdl, fdr;
            bool bl = 1;
            bool br = 1;
            bool fl = 1;
            bool fr = 1;
            double sds;
            bool sdf = 1;
            for (int pos = 0; pos < (int)count; ++pos)
            {
                ang = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f;
                qua = nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;
                if (qua == 0)
                {
                    continue;
                }
                else if (ang >= ang_fl && fl)
                {
                    fdl = nodes[pos].distance_q2 / 4.0f;
                    fl = 0;
                }
                else if (ang >= 15 && sdf)
                {
                    sds = nodes[pos].distance_q2 / 4.0f;
                    sdf = 0;
                }
                else if (ang >= ang_fr && fr)
                {
                    fdr = nodes[pos].distance_q2 / 4.0f;
                    fr = 0;
                }
                else if (ang >= ang_bl && bl)
                {
                    bdl = nodes[pos].distance_q2 / 4.0f;
                    bl = 0;
                }
                else if (ang >= ang_br && br)
                {
                    bdr = nodes[pos].distance_q2 / 4.0f;
                    br = 0;
                }
                else
                {
                    continue;
                }
            }

            switch (Robot_State)
            {
            case INITIAL:
            {
                cout << "INITIAL Robot State!" << endl;
                cout << sds << endl;
                if (sds < 800)
                {
                    cout << "Green Left" << endl;
                }
                else
                {
                    cout << "Orange Right" << endl;
                    F_dif = 0;
                    Forward_Dis[0] = 1050;
                    ang_bl = 165;
                    ang_br = 180;
                    int i = 0;
                    while (Stop_Wheel_State[i])
                    {
                        if (Stop_Wheel_State[i] == TURNLEFT)
                        {
                            Stop_Wheel_State[i] = TURNRIGHT;
                        }
                        ++i;
                    }
                    int j = 0;
                    while (Stop_Wheel_Cmd[j])
                    {
                        if (Stop_Wheel_Cmd[j] == "e")
                        {
                            Stop_Wheel_Cmd[j] = "i";
                        }
                        ++j;
                    }
                }
                Robot_State = STOP_FOR_WHEEL;
                break;
            }
            case FRONT_CORRECTION:
            {
                if (TimesOut > 4)
                {
                    Robot_State = STOP_FOR_WHEEL;
                }
                else if (fdl > fdr)
                {
                    SendMovArd("i");
                    Robot_State = FRONT_CORRECTION_LEFT;
                }
                else if (fdl < fdr)
                {
                    SendMovArd("e");
                    Robot_State = FRONT_CORRECTION_RIGHT;
                }
                else
                {
                    Robot_State = STOP_FOR_WHEEL;
                }
                break;
            }
            case FRONT_CORRECTION_LEFT:
            {
                if (fdl <= fdr)
                {
                    SendMovArd("S");
                    Robot_State = FRONT_CORRECTION;
                    ++TimesOut;
                }
                break;
            }
            case FRONT_CORRECTION_RIGHT:
            {
                if (fdl >= fdr)
                {
                    SendMovArd("S");
                    Robot_State = FRONT_CORRECTION;
                    ++TimesOut;
                }
                break;
            }
            case BACK_CORRECTION:
            {
                if (TimesOut > 6)
                {
                    Robot_State = STOP_FOR_WHEEL;
                }
                else if (bdl > bdr)
                {
                    SendMovArd("e");
                    Robot_State = BACK_CORRECTION_RIGHT;
                }
                else if (bdl < bdr)
                {
                    SendMovArd("i");
                    Robot_State = BACK_CORRECTION_LEFT;
                }
                else
                {
                    Robot_State = STOP_FOR_WHEEL;
                }
                break;
            }
            case BACK_CORRECTION_LEFT:
            {
                if (bdl >= bdr)
                {
                    SendMovArd("S");
                    Robot_State = BACK_CORRECTION;
                    ++TimesOut;
                }
                break;
            }
            case BACK_CORRECTION_RIGHT:
            {
                if (bdl <= bdr)
                {
                    SendMovArd("S");
                    Robot_State = BACK_CORRECTION;
                    ++TimesOut;
                }
                break;
            }
            case FRONT_DIS_CORRECTION:
            {
                if ((fdl + fdr) / 2 < Front_Correction_Dis[Front_Correction_Dis_Index])
                {
                    SendMovArd("b");
                    Robot_State = FRONT_CLOSE;
                }
                else if ((fdl + fdr) / 2 > Front_Correction_Dis[Front_Correction_Dis_Index])
                {
                    SendMovArd("f");
                    Robot_State = FRONT_FAR;
                }
                else
                {
                    Robot_State = STOP_FOR_WHEEL;
                    ++Front_Correction_Dis_Index;
                }
                break;
            }
            case FRONT_FAR:
            {
                if ((fdl + fdr) / 2 <= Front_Correction_Dis[Front_Correction_Dis_Index])
                {
                    SendMovArd("S");
                    ++Front_Correction_Dis_Index;
                    cout << "STOP!" << endl;
                    Robot_State = STOP_FOR_WHEEL;
                }
                else if (fdl < fdr && Sub_State != MOVE_LEFT)
                {
                    SendMovArd("l");
                    cout << "MOVE_LEFT!"
                         << "L: " << fdl << "R:" << fdr << endl;
                    Sub_State = MOVE_LEFT;
                }
                else if (fdl > fdr && Sub_State != MOVE_RIGHT)
                {
                    SendMovArd("r");
                    cout << "MOVE_RIGHT!"
                         << "L: " << fdl << "R:" << fdr << endl;
                    Sub_State = MOVE_RIGHT;
                }
                else if (fdl == fdr && Sub_State != MOVE_STRAIGHT)
                {
                    SendMovArd("s");
                    cout << "MOVE_STRAIGHT!"
                         << "L: " << fdl << "R:" << fdr << endl;
                    Sub_State = MOVE_STRAIGHT;
                }
                break;
            }
            case FRONT_CLOSE:
            {
                if ((fdl + fdr) / 2 >= Front_Correction_Dis[Front_Correction_Dis_Index])
                {
                    SendMovArd("S");
                    cout << "STOP!" << endl;
                    Robot_State = FRONT_DIS_CORRECTION;
                }
                else if (fdl < fdr && Sub_State != MOVE_LEFT)
                {
                    SendMovArd("l");
                    cout << "MOVE_LEFT!"
                         << "L: " << bdl << "R:" << bdr << endl;
                    Sub_State = MOVE_LEFT;
                }
                else if (fdl > fdr && Sub_State != MOVE_RIGHT)
                {
                    SendMovArd("r");
                    cout << "MOVE_RIGHT!"
                         << "L: " << bdl << "R:" << bdr << endl;
                    Sub_State = MOVE_RIGHT;
                }
                else if (fdl == fdr && Sub_State != MOVE_STRAIGHT)
                {
                    SendMovArd("s");
                    cout << "MOVE_STRAIGHT!"
                         << "L: " << bdl << "R:" << bdr << endl;
                    Sub_State = MOVE_STRAIGHT;
                }
                break;
            }
            case BACK_DIS_CORRECTION:
            {
                if ((bdl + bdr) / 2 > 300)
                {
                    SendMovArd("b");
                    Robot_State = BACK_FAR;
                }
                else if ((bdl + bdr) / 2 < 300)
                {
                    SendMovArd("f");
                    Robot_State = BACK_CLOSE;
                }
                else
                {
                    Robot_State = STOP_FOR_WHEEL;
                }
                break;
            }
            case BACK_FAR:
            {
                if ((bdl + bdr) / 2 <= 300)
                {
                    SendMovArd("S");
                    Robot_State = STOP_FOR_WHEEL;
                }
                break;
            }
            case BACK_CLOSE:
            {
                if ((bdl + bdr) / 2 >= 300)
                {
                    SendMovArd("S");
                    Robot_State = BACK_DIS_CORRECTION;
                }
                break;
            }
            case FORWARD:
            {
                cout << "FORWARD!" << endl;
                Forwarding(bdl, bdr, fdl, fdr);
                break;
            }
            case BACKWARD:
            {
                cout << "BACKWARD!" << endl;
                Backwarding(bdl, bdr, fdl, fdr);

                break;
            }
            case TURNLEFT:
            {
                cout << "TURNLEFT!" << endl;
                Lefting(bdl, bdr, fdl, fdr);
                break;
            }
            case TURNRIGHT:
                cout << "TURNRIGHT!" << endl;
                Righting(bdl, bdr, fdl, fdr);
                break;
            case RECOGNIZE_CUBE_ORDER:
            {
                char *servInetAddr = "172.20.10.11";
                int socketfd;
                struct sockaddr_in sockaddr;

                int n;

                socketfd = socket(AF_INET, SOCK_STREAM, 0);
                memset(&sockaddr, 0, sizeof(sockaddr));
                sockaddr.sin_family = AF_INET;
                sockaddr.sin_port = htons(10004);

                inet_pton(AF_INET, servInetAddr, &sockaddr.sin_addr);

                if ((connect(socketfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr))) < 0)
                {
                    printf("connect error %s errno: %d\n", strerror(errno), errno);
                    exit(0);
                }

                n = recv(socketfd, c_cmd, MAXLINE, 0);
                c_cmd[n] = '\0';
                cout << c_cmd << endl;
                close(socketfd);

                //                system("raspistill -o tar.jpg -rot 180 -w 600 -h 400 -t 500");
                //                int tar[4] = {0};
                //                int order;
                //                if(Side_Flag == leftside){
                //                    order = GetCubeOrder();
                //                }
                //                order = 24;
                //                tar[2] = order%10;
                //                tar[1] = (order/10)%10;
                //                tar[0] = (order/100)%10;
                //                GetCubeCmd(tar);
                Robot_State = STOP_FOR_PICK;
                break;
            }
            case PRESS_BUTTON:
            {
                RecvPickArd(str_recv);
                Robot_State = STOP_FOR_PICK;
                break;
            }
            case ARRANGE_CUBE:
            {
                usleep(1000000);
                cout << "CMD====" << c_cmd << endl;
                SendPickArd(c_cmd);
                RecvPickArd(str_recv);
                Robot_State = STOP_FOR_PICK;
                break;
            }
            case RELEASE_CUBE:
            {
                RecvMovArd(str_recv);
                Robot_State = STOP_FOR_WHEEL;
                break;
            }
            case STOP_FOR_WHEEL:
            {
                Sub_State = INITIAL;
                turn_flag = 0;
                match_flag = 0;
                dis_mark = 0;
                TimesOut = 0;
                SendMovArd(Stop_Wheel_Cmd[STOP_Wheel_CMD_Index++]);
                Robot_State = Stop_Wheel_State[STOP_Wheel_State_Index++];
                break;
            }
            case STOP_FOR_PICK:
            {
                SendPickArd(Stop_Pick_Cmd[STOP_PICK_CMD_Index++]);
                Robot_State = Stop_Pick_State[STOP_PICK_State_Index++];
                break;
            }
            case END:
            {
                goto end;
                break;
            }
            }
        }
    }
end:
    drv->stop();
    drv->stopMotor();
    RPlidarDriver::DisposeDriver(drv);
    drv = NULL;
    return 0;
}

/*
#define SCALE 0.001
int main() {
    //Plane.registerKeyboardCallback(KeybdCallback);
    Plane.setBackgroundColor();
    //Plane.showWidget("Coordinate Widget", WCoordinateSystem());
//    initialPlane();
//    initialObj();


    iniRadar();
    // fetech result and print it out...
    double ang,dis;
    int qua;

    WLine Axis_y(Point3f(0.0f, SCALE*150.0f, 0.0f), Point3f(0.0f, SCALE*-150.0f, 0.0f),Color::blue());
    WLine Axis_x(Point3f(SCALE*230.0f, 0.0f, 0.0f), Point3f(SCALE*-120.0f, 0.0f, 0.0f),Color::red());

    WLine Tra_F(Point3f(0.0f, 0.0f, 0.0f), Point3f(0.0f, SCALE*300.0f, 0.0f),Color::yellow());
    WLine Tra_S(Point3f(SCALE*-173.2050807568878f, SCALE*300.0f, 0.0f), Point3f(0.0f, SCALE*300.0f, 0.0f),Color::yellow());
    WLine Tra_L(Point3f(SCALE*-173.2050807568878f, SCALE*300.0f, 0.0f), Point3f(0.0f, 0.0f, 0.0f),Color::yellow());

    Axis_y.setRenderingProperty(viz::LINE_WIDTH, 1.0);
    Axis_x.setRenderingProperty(viz::LINE_WIDTH, 1.0);
    Tra_F.setRenderingProperty(viz::LINE_WIDTH, 1.0);
    Tra_S.setRenderingProperty(viz::LINE_WIDTH, 1.0);
    Tra_L.setRenderingProperty(viz::LINE_WIDTH, 1.0);


    Plane.showWidget("Axis_y", Axis_y);
    Plane.showWidget("Axis_x", Axis_x);
    Plane.showWidget("Tra_F", Tra_F);
    Plane.showWidget("Tra_S", Tra_S);
    Plane.showWidget("Tra_L", Tra_L);


    while (true) {
        rplidar_response_measurement_node_t nodes[8192];
        size_t   count = _countof(nodes);
        op_result = drv->grabScanData(nodes, count);
        if (IS_OK(op_result)) {
            drv->ascendScanData(nodes, count);
            vector<Vec3f> points;
            vector<Vec3f> front_left_point;
            vector<Vec3f> front_right_point;

            bool f_l_flag = 1;
            bool f_r_flag = 1;

            addPoint(&points,0,0,0);

            for (int pos = 0; pos < (int)count ; ++pos) {
                ang = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;
                qua = nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;
                dis = nodes[pos].distance_q2/4.0f;
                if(qua == 0){
                    continue;
                }else if(ang>=177 && f_r_flag){
                    addPoint(&front_right_point,SCALE*dis*cos(ang*PI/180)+x,SCALE*dis*sin(ang*PI/180)+y,0);
                    f_r_flag = 0;
                }else if(ang>=183 && f_l_flag){
                    addPoint(&front_left_point,SCALE*dis*cos(ang*PI/180)+x,SCALE*dis*sin(ang*PI/180)+y,0);
                    f_l_flag = 0;
                }else{
                    addPoint(&points,SCALE*dis*cos(ang*PI/180)+x,SCALE*dis*sin(ang*PI/180)+y,0);
                }
            }
            if(!points.empty()){
                WCloud point_cloud(points,Color::green());
                Plane.showWidget("point_cloud", point_cloud);
            }
            if(!front_left_point.empty()){
                WCloud front_l_cloud(front_left_point,Color::red());
                Plane.showWidget("front_l_cloud", front_l_cloud);
            }
            if(!front_right_point.empty()){
                WCloud front_r_cloud(front_right_point,Color::blue());
                Plane.showWidget("front_r_cloud", front_r_cloud);
            }
        }
//        Mat rvec = Mat::zeros(1, 3, CV_32F);
//        rvec.at<float>(0,0) = 0.0f;
//        rvec.at<float>(0,1) = 0.0f;
//        rvec.at<float>(0,2) = 0.0f;
//        Mat rmat;
//        Rodrigues(rvec, rmat);
//        Affine3f pose(rmat, Vec3f(x,y,0.0));
//        Plane.setWidgetPose("Robot", pose);
//        Affine3f pose11(rmat, Vec3f(x,0.0,0.0));
//        Plane.setWidgetPose("l1", pose11);
//        Affine3f pose22(rmat, Vec3f(0.0,y,0.0));
//        Plane.setWidgetPose("l2", pose22);

        Plane.spinOnce(1, true);
    }
    drv->stop();
    drv->stopMotor();
    // done!
    RPlidarDriver::DisposeDriver(drv);
    drv = NULL;
    return 0;
}

*/
