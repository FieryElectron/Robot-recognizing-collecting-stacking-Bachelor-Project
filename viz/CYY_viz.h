#include <opencv2/viz.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>

#define OO 0
#define HH 1
#define VV 2

using namespace cv;
using namespace viz;
using namespace std;

int rect_counter = 0;

Viz3d Plane("Simulation");/// Create a window


void setRect_Gray(float height, float width, float cx, float cy, float cz, int sign){
    string id = "Rect";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    free(szBuffer);
    WPlane Rect(Size2d(width,height),Color::gray());
    Plane.showWidget(id, Rect);
    Mat rvec = Mat::zeros(1, 3, CV_32F);
    rvec.at<float>(0,0) = 0.0f;
    rvec.at<float>(0,1) = 0.0f;
    rvec.at<float>(0,2) = 0.0f;
    if(sign == HH){
        rvec.at<float>(0,1) = CV_PI*0.5f;
    }else if(sign == VV){
        rvec.at<float>(0,0) = CV_PI*0.5f;
    }else if(sign == OO){
        ;
    }
    Mat rmat;
    Rodrigues(rvec, rmat);
    Affine3f pose(rmat, Vec3f(cx,cy,cz));
    Plane.setWidgetPose(id, pose);
    ++rect_counter;
}

void setRect_White(float height, float width, float cx, float cy, float cz, int sign){
    string id = "Rect";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    free(szBuffer);
    WPlane Rect(Size2d(width,height),Color::white());
    Plane.showWidget(id, Rect);
    Mat rvec = Mat::zeros(1, 3, CV_32F);
    rvec.at<float>(0,0) = 0.0f;
    rvec.at<float>(0,1) = 0.0f;
    rvec.at<float>(0,2) = 0.0f;
    if(sign == HH){
        rvec.at<float>(0,1) = CV_PI*0.5f;
    }else if(sign == VV){
        rvec.at<float>(0,0) = CV_PI*0.5f;
    }else if(sign == OO){
        ;
    }
    Mat rmat;
    Rodrigues(rvec, rmat);
    Affine3f pose(rmat, Vec3f(cx,cy,cz));
    Plane.setWidgetPose(id, pose);
    ++rect_counter;
}

void setRect_Black(float height, float width, float cx, float cy, float cz, int sign){
    string id = "Rect";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    free(szBuffer);
    WPlane Rect(Size2d(width,height),Color::black());
    Plane.showWidget(id, Rect);
    Mat rvec = Mat::zeros(1, 3, CV_32F);
    rvec.at<float>(0,0) = 0.0f;
    rvec.at<float>(0,1) = 0.0f;
    rvec.at<float>(0,2) = 0.0f;
    if(sign == HH){
        rvec.at<float>(0,1) = CV_PI*0.5f;
    }else if(sign == VV){
        rvec.at<float>(0,0) = CV_PI*0.5f;
    }else if(sign == OO){
        ;
    }
    Mat rmat;
    Rodrigues(rvec, rmat);
    Affine3f pose(rmat, Vec3f(cx,cy,cz));
    Plane.setWidgetPose(id, pose);
    ++rect_counter;
}

void setRect_Green(float height, float width, float cx, float cy, float cz, int sign){
    string id = "Rect";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    free(szBuffer);
    WPlane Rect(Size2d(width,height),Color::green());
    Plane.showWidget(id, Rect);
    Mat rvec = Mat::zeros(1, 3, CV_32F);
    rvec.at<float>(0,0) = 0.0f;
    rvec.at<float>(0,1) = 0.0f;
    rvec.at<float>(0,2) = 0.0f;
    if(sign == HH){
        rvec.at<float>(0,1) = CV_PI*0.5f;
    }else if(sign == VV){
        rvec.at<float>(0,0) = CV_PI*0.5f;
    }else if(sign == OO){
        ;
    }
    Mat rmat;
    Rodrigues(rvec, rmat);
    Affine3f pose(rmat, Vec3f(cx,cy,cz));
    Plane.setWidgetPose(id, pose);
    ++rect_counter;
}

void setRect_Orange(float height, float width, float cx, float cy, float cz, int sign){
    string id = "Rect";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    free(szBuffer);
    WPlane Rect(Size2d(width,height),Color::orange());
    Plane.showWidget(id, Rect);
    Mat rvec = Mat::zeros(1, 3, CV_32F);
    rvec.at<float>(0,0) = 0.0f;
    rvec.at<float>(0,1) = 0.0f;
    rvec.at<float>(0,2) = 0.0f;
    if(sign == HH){
        rvec.at<float>(0,1) = CV_PI*0.5f;
    }else if(sign == VV){
        rvec.at<float>(0,0) = CV_PI*0.5f;
    }else if(sign == OO){
        ;
    }
    Mat rmat;
    Rodrigues(rvec, rmat);
    Affine3f pose(rmat, Vec3f(cx,cy,cz));
    Plane.setWidgetPose(id, pose);
    ++rect_counter;
}

void setCubeSet(float cx, float cy){
    string id = "Cube";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    WCube yellow(Point3d(cx-30,cy-30,0.1),Point3d(cx+30,cy+30,60.1),false,Color::yellow());
    Plane.showWidget(id, yellow);
    id.append(szBuffer);
    WCube orange(Point3d(cx-30,cy+30,0.1),Point3d(cx+30,cy+90,60.1),false,Color::red());
    Plane.showWidget(id, orange);
    id.append(szBuffer);
    WCube black(Point3d(cx-90,cy-30,0.1),Point3d(cx-30,cy+30,60.1),false,Color::black());
    Plane.showWidget(id, black);
    id.append(szBuffer);
    WCube green(Point3d(cx-30,cy-90,0.1),Point3d(cx+30,cy-30,60.1),false,Color::green());
    Plane.showWidget(id, green);
    id.append(szBuffer);
    WCube blue(Point3d(cx+30,cy-30,0.1),Point3d(cx+90,cy+30,60.1),false,Color::blue());
    Plane.showWidget(id, blue);
    free(szBuffer);
    ++rect_counter;
}

void initialPlane(){
    setRect_White(3000,2000,1000,0,0,OO);
    setRect_Gray(3000,100,0,0,50,HH);
    setRect_Gray(3000,100,2000,0,50,HH);
    setRect_Gray(100,2000,1000,1500,50,VV);
    setRect_Gray(100,2000,1000,-1500,50,VV);
    setRect_Black(3000,30,300,0,0.1,OO);
    setRect_White(3000,10,300,0,0.2,OO);
    setRect_Black(30,300,150,-250,0.1,OO);
    setRect_White(10,300,150,-250,0.2,OO);
    setRect_Black(30,300,150,250,0.1,OO);
    setRect_White(10,300,150,250,0.2,OO);
    setRect_Black(30,70,300,0,0.1,OO);
    setRect_White(10,50,300,0,0.2,OO);
    setRect_Black(30,1400,1000,-1000,0.1,OO);
    setRect_White(10,1390,992,-1000,0.2,OO);
    setRect_Black(30,1400,1000,1000,0.1,OO);
    setRect_White(10,1390,992,1000,0.2,OO);
    setRect_Black(500,30,800,-1050,0.1,OO);
    setRect_White(480,10,800,-1050,0.2,OO);
    setRect_Black(500,30,800,1050,0.1,OO);
    setRect_White(480,10,800,1050,0.2,OO);
    setRect_Green(360,285,142.5,-1320,0.2,OO);

    setRect_Green(360,220,425,-1320,0.2,OO);
    setRect_Orange(360,285,142.5,1320,0.2,OO);
    setRect_Orange(360,220,425,1320,0.2,OO);
    setRect_Green(700,140,70,-800,0.2,OO);
    setRect_White(680,130,65,-800,0.3,OO);
    setRect_Orange(700,140,70,800,0.2,OO);
    setRect_White(680,130,65,800,0.3,OO);
    setRect_Black(1200,300,1850,0,0.2,OO);
    setRect_Orange(580,280,1850,300,0.3,OO);
    setRect_Green(580,280,1850,-300,0.3,OO);

    setCubeSet(540,-650);
    setCubeSet(1190,-1200);
    setCubeSet(1500,-400);
    setCubeSet(540,650);
    setCubeSet(1190,1200);
    setCubeSet(1500,400);

    WLine l0(Point3f(0.0f,0.0f,0.0f),Point3f(0.0f,0.0f,50.0f),Color::green());
    l0.setRenderingProperty(LINE_WIDTH, 1.0);
    Plane.showWidget("l0",l0);
}

void initialObj(){
    WCube Robot(Point3d(10,-1490,0.1),Point3d(290,-1100,300),false,Color::silver());
    Plane.showWidget("Robot", Robot);


    WLine l1(Point3f(150,-1500,310.0f),Point3f(150,1500.0f,310.0f),Color::red());
    l1.setRenderingProperty(LINE_WIDTH, 2.0);
    Plane.showWidget("l1",l1);

    WLine l2(Point3f(0,-1300,311.0f),Point3f(2000,-1300.0f,311.0f),Color::blue());
    l1.setRenderingProperty(LINE_WIDTH, 2.0);
    Plane.showWidget("l2",l2);
}

int x=0;
int y=0;

void KeybdCallback(const viz::KeyboardEvent &keyEvent, void *){
    //(keyEvent.action == viz::KeyboardEvent::KEY_DOWN)&& (keyEvent.code == 'a')
    if(keyEvent.code == '8'){
        y += 10;
    }else if(keyEvent.code == '5'){
        y -= 10;
    }else if(keyEvent.code == '4'){
        x -= 10;
    }else if(keyEvent.code == '6'){
        x += 10;
    }
}

void addPoint(vector<Vec3f>* cloud,float x,float y,float z){
    cloud->push_back({x,y,z});
}

void addPathPoint(vector<Affine3d>* path, float x, float y, float z){
    path->push_back(Affine3d(Mat{0.0,0.0,0.0},Mat{x, y, z}));
}

void setCloud(){
    vector<Vec3f> Cloud_Arr;
//    srand((unsigned)time(NULL));
//    rand();
    float j = 0;
    for(int k = 0;k<30;k+=2){
        for(int j = 0 ;j<30;j+=2){
            for(int i =0;i<30;i+=2){
                addPoint(&Cloud_Arr,i,j,k);
            }
        }
    }

    WCloud cloud(Cloud_Arr,Color::green());
    Plane.showWidget("cloud", cloud);
}

void setPath(){
    vector<Affine3d> path;
    srand((unsigned)time(NULL));

    for(int i =0;i<100;++i){
        addPathPoint(&path,rand()/10,rand()/10,rand()/10);
    }
    Plane.showWidget("camPath", viz::WTrajectory(path, WTrajectory::PATH, 1.0, Color::yellow()));

}

void setCamera(float x, float y, float z, float s){
    string id = "cam";
    char* szBuffer = (char *)malloc(sizeof(int) + 1);
    memset(szBuffer, 0, sizeof(int) + 1);
    sprintf(szBuffer, "%d", rect_counter);
    id.append(szBuffer);
    free(szBuffer);

    WCameraPosition cam(Matx33d{x,0.0,0.0,0.0,y,z,0.0,0.0,0.0},s,Color::white());
    Plane.showWidget(id, cam);
    ++rect_counter;
}
