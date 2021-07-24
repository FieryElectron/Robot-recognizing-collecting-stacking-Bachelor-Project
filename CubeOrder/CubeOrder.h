#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace cv;
using namespace std;

//           0     1    2   3    4    5    6   7    8
int Glo_arr[9] = { -1,  0,  -1,  1,   2,   3,  -1,  4,  -1};

int buffer[5] = {-1,-1,-1,-1,-1};

void DeepCpoy(int* from,int* to){
    for(int i=0; i<9; i++){
        *(to+i)=*(from+i);
    }
}

void Display(int* dis){
    for(char i =0;i<9;++i){
        if(i==3||i==6){printf("\n");}
        if(dis[i] == -1){
            printf(" ");
        }else{
            printf("%d",dis[i]);
        }
    }
    printf("\n-----\n");
}

void Turnleft(int* Tl){
    int tem = Tl[1];
    Tl[1] = Tl[5];
    Tl[5] = Tl[7];
    Tl[7] = Tl[3];
    Tl[3] = tem;
    //Display(Tl);
}

void Turnright(int* Tr){
    int tem = Tr[1];
    Tr[1] = Tr[3];
    Tr[3] = Tr[7];
    Tr[7] = Tr[5];
    Tr[5] = tem;
    //Display(Tr);
}



int TriArr[5][3][3] = {
    {{1,3,4},{1,3,5},{1,3,7}},
    {{1,4,3},{1,4,5},{1,4,7}},
    {{1,5,3},{1,5,4},{1,5,7}},
    {{1,7,3},{1,7,4},{1,7,5}},
    {{4,1,3},{4,1,5},{4,1,7}}
};

int SearchType(int* tar){
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 3; ++j){
            int match[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
            for(int k = 0; k < 3; ++k){
                match[TriArr[i][j][k]] = tar[k];
            }
            int cp_glo[9] = {0};
            DeepCpoy(Glo_arr,cp_glo);
            for(int l = 0; l < 4; ++l){
                if(cp_glo[TriArr[i][j][0]]==match[TriArr[i][j][0]]&&
                   cp_glo[TriArr[i][j][1]]==match[TriArr[i][j][1]]&&
                   cp_glo[TriArr[i][j][2]]==match[TriArr[i][j][2]]){
                    //printf("Found it! ");
                    char row[2] = {0};
                    char col[2] = {0};
                    char rc[3] = {};
                    snprintf(row, sizeof(row), "%d", i);
                    snprintf(col, sizeof(col), "%d", j);
//                    itoa(i, row, 10);
//                    itoa(j, col, 10);
                    strcat(rc,row);
                    strcat(rc,col);
                    return atoi(rc);
                }else{
                    Turnleft(cp_glo);
                    //printf("Turn left!\n");
                }
            }
        }
    }
    return -1;
}


char quadArr[5][3][4][30]={
    {{{"TP R TP R TA L MP"},{"R TP TP R TP R TA L MP"},{"L TP R TP R TA L MP"},{"TA L L TP R TP MP"}},{{"TP R TP R R TP"},{"L TP R TP R R TP"},{"L TP R TP R R TP"},{"R R TP R TP R R TP"}},{{"TP R TP R TP"},{"R TP R TP R TP"},{"L TP R TP R TP"},{"R R TP R TP R TP"}}},
    {{{"TP R R TA L MP TP"},{"R TP R R TA L MP TP"},{"L TP R R TA L MP TP"},{"TA R R TP R MP TP"}},{{"TP R R TA R MP TP"},{"R TP R R TA R MP TP"},{"L TP R R TA R MP TP"},{"TA R R TP L MP TP"}},{{"TP R TA R R TA L MP TP"},{"TA L TP L TA L MP TP"},{"TA R TP R TA R MP TP"},{"L TA L TP L TA L MP TP"}}},
    {{{"TP L TP R R TP"},{"R TP L TP R R TP"},{"L TP L TP R R TP"},{"R R TP L TP R R TP"}},{{"TP L TP L TA R MP"},{"R TP L TP L TA R MP"},{"L TP L TP L TA R MP"},{"TA R R TP L TP MP"}},{{"TP L TP L TP"},{"R TP L TP L TP"},{"L TP L TP L TP"},{"R R TP L TP L TP"}}},
    {{{"TP R R TP L TP"},{"R TP R R TP L TP"},{"L TP R R TP L TP"},{"R R TP R R TP L TP"}},{{"TP R R TP R MP"},{"L TP R R TP R MP"},{"R TP R R TP R MP"},{"R R TP R R TP R MP"}},{{"TP R R TP R TP"},{"R TP R R TP R TP"},{"L TP R R TP R TP"},{"R R TP R R TP R TP"}}},
    {{{"R TP L TP L TA R MP"},{"TA R R TP L TP MP"},{"TP L TP L TA R MP"},{"TA L TP L TP R MP"}},{{"L TP R TP R TA L MP"},{"TP R TP R TA L MP"},{"TA R R TP R TP MP"},{"TA R TP R TP L MP"}},{{"R R TP R R TP R MP"},{"R TP R R TP R MP"},{"L TP R R TP R MP"},{"TP R R TP R MP"}}}

};

char * strim(char * str){
    char * tail = str;
    char * next = str;
    while(*next){
        if(*next != ' '){
            if(tail < next)
                *tail = *next;
            tail++;
        }
        next++;
    }
    *tail = '\0';
    return str;
}

char* verify(int row, int col, int start){
    //char cmd[30] = {0};
    int realStart = 0;
    if(start == 0){
        realStart = 0;
    }else if(start == 1){
        realStart = 1;
    }else if(start == 3){
        realStart = 2;
    }else if(start == 4){
        realStart = 3;
    }
    //cout<<"ROW: "<<row<<"COL: "<<col<<"START: "<<realStart<<endl;
//    memset(Global_CubeCMD,0,sizeof(char)*4);
//    strcpy(Global_CubeCMD,quadArr[row][col][realStart]);

//    strcpy(cmd,quadArr[row][col][realStart]);
//    printf("CMD -> %s\t\t",cmd);
//    int vearr[9] = {0};
//    DeepCpoy(Glo_arr,vearr);
//    int index = -1;
//    int buf_index = 0;
//    for(int i = 0; i < strlen(cmd); ++i){
//        if(cmd[i] == 'T'){
//            index = 1;
//        }else if(cmd[i] == 'M'){
//            index = 4;
//        }else if(cmd[i] == 'P'){
//            buffer[buf_index++] = vearr[index];
//            vearr[index] = -1;index = -1;
//        }else if(cmd[i] == 'L'){
//            Turnleft(vearr);
//        }else if(cmd[i] == 'R'){
//            Turnright(vearr);
//        }else if(cmd[i] == 'A'){
//            buffer[buf_index++] = vearr[index];
//            vearr[index] = -1;index = -1;
//        }
//        //Display(vearr);
//    }
    //Display(vearr);
    return strim(quadArr[row][col][realStart]);
}

char* GetCubeOrderCMD_old(int* tar){
    int RowCol = SearchType(tar);
    //printf("%02d\n",RowCol);
    int col = RowCol%10;
    int row = (RowCol - col)/10;
    if(tar[0] == 2){
        return verify(row, col, tar[1]);
    }else{
        return verify(row, col, tar[0]);
    }
}
char str[20] = {0};

void GetCubeOrderCMD(int* tar){

    if(tar[0] == 2){
        int temp = tar[0];
        tar[0] = tar[2];
        tar[2] = temp;
    }
        int pnum = 0;
        int cp[9] = {0};
        DeepCpoy(Glo_arr,cp);
        int CutNum = 0;
    if(tar[0] !=2&&tar[1] !=2&&tar[2] !=2){
        while(true){
            if(cp[1] == tar[pnum]){
                strcat (str,"TP");
               // printf(" TP ");
                cp[1] = -1;
                ++pnum;
                ++CutNum;
            }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                //printf(" TA ");
                strcat (str,"TA");
                cp[1] = -1;
                ++CutNum;
            }
            if(cp[3] == -1 && cp[5] == -1&&cp[4] !=-1){
                    //printf(" MA ");
                strcat (str,"MA");
                    cp[4] = -1;
                    ++CutNum;
            }
            if(cp[1] == tar[pnum]){
                //printf(" TP ");
                strcat (str,"TP");
                cp[1] = -1;
                ++pnum;
                ++CutNum;
            }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                //printf(" TA ");
                strcat (str,"TA");
                cp[1] = -1;
                ++CutNum;
            }
            if(CutNum <5){
                Turnright(cp);
                strcat (str,"R");
                //printf(" R ");
            }else{
                break;
            }
        }
    }else{
           while(true){
               if(cp[1] == tar[pnum]){
                   strcat (str,"TP");
                   //printf(" TP");
                   cp[1] = -1;
                   ++pnum;
                   ++CutNum;
               }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                   //printf(" TA");
                   strcat (str,"TA");
                   cp[1] = -1;
                   ++CutNum;
               }
               if(cp[3] == -1 && cp[5] == -1&&cp[4] == tar[pnum]&&cp[4] !=-1){
                       //printf(" MP");
                   strcat (str,"MP");
                       cp[4] = -1;
                       ++pnum;
                       ++CutNum;
               }
               if(cp[1] == tar[pnum]){
                   strcat (str,"TP");
                   //printf(" TP ");
                   cp[1] = -1;
                   ++pnum;
                   ++CutNum;
               }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                   strcat (str,"TA");
                   //printf(" TA ");
                   cp[1] = -1;
                   ++CutNum;
               }
               if(CutNum <5){
                   Turnright(cp);
                   strcat (str,"R");
                   //printf(" R ");
               }else{
                   break;
               }
           }
    }
}


int GetEachColor_X(int iLowH, int iHighH, int iLowS,int iHighS, int iLowV, int iHighV, int iMinBlobSize){
    Mat imgOriginal = imread("b1.jpg", IMREAD_GRAYSCALE);
    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
    Mat imgThresholded;
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    vector<vector<Point> >contours;
    vector<Vec4i> hierarchy;
    findContours( imgThresholded,
                  contours,
                  hierarchy,
                  RETR_TREE,
                  CHAIN_APPROX_SIMPLE,
                  Point(0, 0) );
    vector<Moments> mu(contours.size() );
    for( int i = 0; i < contours.size(); i++ ){
        mu[i] = moments( contours[i], false );
    }
    vector<Point2f> mc( contours.size() );
    for( int i = 0; i < contours.size(); i++ ){
        mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
    }
    RNG rng(12345);
    Mat blobImg = Mat::zeros( imgThresholded.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ ){
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( blobImg, contours, i, color, 2, 8, hierarchy, 0, Point() );
        circle( blobImg, mc[i], 4, color, -1, 8, 0 );
    }
    vector<vector<Point> > contours_filt;
    vector<Vec4i> hierarchy_filt;
    vector<Moments> mu_filt;
    vector<Point2f> mc_filt;
    int minBlobArea = iMinBlobSize*1000;
    for( int i = 0; i< contours.size(); i++ ){
        if (mu[i].m00 > minBlobArea){
            contours_filt.push_back(contours[i]);
            hierarchy_filt.push_back(hierarchy[i]);
            mu_filt.push_back(mu[i]);
            mc_filt.push_back(mc[i]);
        }
    }
    Mat blobImg_filt = Mat::zeros( imgThresholded.size(), CV_8UC3 );;
    //cout<< "------" <<endl;
    for( int i = 0; i< contours_filt.size(); i++ ){
        return mc_filt[i].x;
        cout<< mc_filt[i].x <<endl;
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( blobImg_filt, contours_filt, i, color, 2, 8, hierarchy_filt, 0, Point() );
        circle( blobImg_filt, mc_filt[i], 4, color, -1, 8, 0 );

        drawContours( imgOriginal, contours_filt, i, color, 2, 8, hierarchy_filt, 0, Point() );
        circle( imgOriginal, mc_filt[i], 4, color, -1, 8, 0 );
    }
    return 6666;
    //cout<< "======" <<endl;
    //cv::imshow( "blobImg_filt", blobImg_filt );
    //cv::imshow("Results", imgOriginal);
}

int GetCubeOrder(){
    //0:green
    //1:blue
    //2:yellow
    //3:black
    //4:orange
    int eu_color_index = 0;
    int eu_color[5] = {0};
    eu_color[eu_color_index++] = GetEachColor_X(23, 100, 0, 255, 0, 255, 8);
    eu_color[eu_color_index++] = GetEachColor_X(49, 179, 0, 255, 0, 255, 8);
    eu_color[eu_color_index++] = GetEachColor_X(12, 47, 0, 255, 0, 255, 8);
    eu_color[eu_color_index++] = GetEachColor_X(0, 179, 0, 255, 0, 30, 8);
    eu_color[eu_color_index++] = GetEachColor_X(1, 21, 0, 255, 0, 255, 8);
    int left = 5555;int left_index = -1;
    int mid = 5555;int mid_index = -1;
    int right =  5555;int right_index = -1;

    for(int i =0;i<5;++i){
        if(eu_color[i]<left){
            left = eu_color[i];
            left_index = i;
        }
    }
    eu_color[left_index] = 6666;

    for(int i =0;i<5;++i){
        if(eu_color[i]<mid){
            mid = eu_color[i];
            mid_index = i;
        }
    }
    eu_color[mid_index] = 6666;

    for(int i =0;i<5;++i){
        if(eu_color[i]<right){
            right = eu_color[i];
            right_index = i;
        }
    }
    eu_color[right_index] = 6666;
    return left_index*100+mid_index*10+right_index;
}

char c_cmd[30] = {0};

void GetCubeCmd(int* tar ){
    if(tar[0] == 2){
        int temp = tar[0];
        tar[0] = tar[2];
        tar[2] = temp;
    }
        int pnum = 0;
        int cp[9] = {0};
        DeepCpoy(Glo_arr,cp);
        int CutNum = 0;
    if(tar[0] !=2&&tar[1] !=2&&tar[2] !=2){
        while(true){
            if(cp[1] == tar[pnum]){
                strcat(c_cmd,"TP");
                //printf(" TP ");
                cp[1] = -1;
                ++pnum;
                ++CutNum;
            }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                //printf(" TA ");
                strcat(c_cmd,"TA");
                cp[1] = -1;
                ++CutNum;
            }
            if(cp[3] == -1 && cp[5] == -1&&cp[4] !=-1){
                    //printf(" MA ");
                strcat(c_cmd,"MA");
                    cp[4] = -1;
                    ++CutNum;
            }
            if(cp[1] == tar[pnum]){
               // printf(" TP ");
                strcat(c_cmd,"TP");
                cp[1] = -1;
                ++pnum;
                ++CutNum;
            }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                //printf(" TA ");
                strcat(c_cmd,"TA");
                cp[1] = -1;
                ++CutNum;
            }
            if(CutNum <5){
                Turnright(cp);
                //printf(" R ");
                strcat(c_cmd,"R");
            }else{
                break;
            }
        }
    }else{
           while(true){
               if(cp[1] == tar[pnum]){
                   //printf(" TP ");
                   strcat(c_cmd,"TP");
                   cp[1] = -1;
                   ++pnum;
                   ++CutNum;
               }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                   //printf(" TA ");
                   strcat(c_cmd,"TA");
                   cp[1] = -1;
                   ++CutNum;
               }
               if(cp[3] == -1 && cp[5] == -1&&cp[4] == tar[pnum]&&cp[4] !=-1){
                      // printf(" MP ");
                   strcat(c_cmd,"MP");
                       cp[4] = -1;
                       ++pnum;
                       ++CutNum;
               }
               if(cp[1] == tar[pnum]){
                   //printf(" TP ");
                   strcat(c_cmd,"TP");
                   cp[1] = -1;
                   ++pnum;
                   ++CutNum;
               }else if(tar[0] !=cp[1]&&tar[1] !=cp[1]&&tar[2] !=cp[1]&&cp[1]!=-1){
                   //printf(" TA ");
                   strcat(c_cmd,"TA");
                   cp[1] = -1;
                   ++CutNum;
               }
               if(CutNum <5){
                   Turnright(cp);
                   //printf(" R ");
                   strcat(c_cmd,"R");
               }else{
                   break;
               }
           }
    }
}
