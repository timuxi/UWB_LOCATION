#include <iostream>
#include <thread>
#include <fstream>
#include <unistd.h>
#include "util/UartUtil.h"
#include "util/GpsUtil.h"

using namespace std;


const int second = 1000000;
const int uwb_data_size = 200;
const int uwbBord = 115200;
const string uwbPort = "/dev/ttyUSBuwb";

const int gps_data_size = 88;
const int gpsBord = 115200;
const string gpsPort = "/dev/ttyUSBgps";

static int ret;
static char uwb_r_buf[uwb_data_size];
static char gps_r_buf[gps_data_size];

[[noreturn]] void readData(const string& port, int bord, char* read_buf, int dataSize){
    UartUtil uart = UartUtil();
    // usb初始化
    uart.usbInit(port, bord);
    ofstream OutFile(GpsUtil::getTime());

    while (true)
    {
        bzero(read_buf, dataSize);
        ret = uart.readData(read_buf, dataSize);
        cout << gps_r_buf;
        OutFile << gps_r_buf;
        usleep(second);
    }
}


int main()
{
    thread uwb(readData,uwbPort,uwbBord,uwb_r_buf,uwb_data_size);
    thread gps(readData,gpsPort,gpsBord,gps_r_buf,gps_data_size);
    uwb.join();
    gps.join();
    return 0;
}


