#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <RS-232/rs232.h>
#include <iostream>

using namespace std;

#define PortMov  24
#define PortPick 25



char str_send[128] = {0};
unsigned char str_recv[128] = {0};

void SerialIniMov(){
    char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
    if(RS232_OpenComport(PortMov, 57600, mode)){
      printf("Can not open comport %d\n",PortMov);
    }
}

void SerialIniPick(){
    char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
    if(RS232_OpenComport(PortPick, 57600, mode)){
      printf("Can not open comport %d\n",PortPick);
    }
}

void SendMovArd(char* str){
    RS232_cputs(PortMov, str);
    //printf("Sent to Arduino: '%s'\n", str);
}

void SendPickArd(char* str){
    RS232_cputs(PortPick, str);
    //printf("Sent to Arduino: '%s'\n", str);
}

void RecvMovArd(unsigned char* str){
    int n = 0;
    while(n<1){
      usleep(50000);
      n = RS232_PollComport(PortMov, str, (int)128);
      //printf("n = %d\n",n);
    }
    str[n] = 0;
    cout<<str<<endl;
}

void RecvPickArd(unsigned char* str){
    int n = 0;
    while(n<1){
      usleep(50000);
      n = RS232_PollComport(PortPick, str, (int)128);
    }
    str[n] = 0;
    cout<<str<<endl;
}
