#include <stdio.h>
#include <stdlib.h>

#include "radar/include/rplidar.h"

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifdef _WIN32
#include <Windows.h>
#define delay(x)   ::Sleep(x)
#else
#include <unistd.h>
static inline void delay(_word_size_t ms){
    while (ms>=1000){
        usleep(1000*1000);
        ms-=1000;
    };
    if (ms!=0)
        usleep(ms*1000);
}
#endif

using namespace rp::standalone::rplidar;

bool checkRPLIDARHealth(RPlidarDriver * drv)
{
    u_result     op_result;
    rplidar_response_device_health_t healthinfo;


    op_result = drv->getHealth(healthinfo);
    if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
        printf("RPLidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
            fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want rplidar to be reboot by software
            // drv->reset();
            return false;
        } else {
            return true;
        }

    } else {
        fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

    const char * opt_com_path = NULL;
    _u32         baudrateArray[2] = {115200, 256000};
    _u32         opt_com_baudrate = 0;
    u_result     op_result;

    bool useArgcBaudrate = false;


RPlidarDriver * drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
void iniRadar(){
    opt_com_path = "/dev/ttyUSB0";
    // create the driver instance

    if (!drv) {fprintf(stderr, "insufficent memory, exit\n");exit(-2);}
    rplidar_response_device_info_t devinfo;
    bool connectSuccess = false;
    // make connection...
    if(useArgcBaudrate){
        if(!drv)
            drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
        if (IS_OK(drv->connect(opt_com_path, opt_com_baudrate))){
            op_result = drv->getDeviceInfo(devinfo);
            if (IS_OK(op_result)){
                connectSuccess = true;
            }
            else{
                delete drv;
                drv = NULL;
            }
        }
    }else{
        size_t baudRateArraySize = (sizeof(baudrateArray))/ (sizeof(baudrateArray[0]));
        for(size_t i = 0; i < baudRateArraySize; ++i){
            if(!drv)
                drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
            if(IS_OK(drv->connect(opt_com_path, baudrateArray[i]))){
                op_result = drv->getDeviceInfo(devinfo);
                if (IS_OK(op_result)){
                    connectSuccess = true;
                    break;
                }else{
                    delete drv;
                    drv = NULL;
                }
            }
        }
    }
    if (!connectSuccess) {
        fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n", opt_com_path);
        RPlidarDriver::DisposeDriver(drv);
        drv = NULL;
        exit(-2);
    }
    // print out the device serial number, firmware and hardware version number..
    printf("RPLIDAR S/N: ");
    for (int pos = 0; pos < 16 ;++pos) {
        printf("%02X", devinfo.serialnum[pos]);
    }
    printf("\n""Firmware Ver: %d.%02d\n""Hardware Rev: %d\n", devinfo.firmware_version>>8, devinfo.firmware_version & 0xFF, (int)devinfo.hardware_version);
    // check health...
    if (!checkRPLIDARHealth(drv)) {
        RPlidarDriver::DisposeDriver(drv);
        drv = NULL;
        exit(-2);
    }
    signal(SIGINT, ctrlc);
    drv->startMotor();
    // start scan...
    drv->startScan(0,1);
}