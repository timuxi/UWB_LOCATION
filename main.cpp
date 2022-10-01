#include <iostream>
#include <thread>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "util/UartUtil.h"
#include "util/GpsUtil.h"
#include "util/TimeUtil.h"
using namespace std;


const int ms = 900000;

const int uwb_data_size = 1024;
const int uwbBord = 115200;
const string uwbPort = "/dev/ttyUSBuwb";

const int gps_data_size = 1024;
const int gpsBord = 115200;
const string gpsPort = "/dev/ttyUSBgps";

static char uwb_r_buf[uwb_data_size];
static char gps_r_buf[gps_data_size];


int uwbProcess(char* buf,long len){
    for(int i=0;i<len;i++){
        if(buf[i] == '\n'){
            buf[i] = '\0';
            return i+1;
        }
    }
    return 0;
}


[[noreturn]] void readData(
        const string& port,int bord, char* read_buf, int dataSize,const string& tag
        ){
    UartUtil uart = UartUtil();
    // usb初始化
    uart.usbInit(port, bord);
    ofstream OutFile(TimeUtil::getFilenameWithTime(tag));
    int cnt = 0;
    char* temp;
    while (true)
    {
        bzero(read_buf, dataSize);
        long ret = uart.readData(read_buf, dataSize);
        temp = read_buf;
        if(ret != 0){
            string  time = TimeUtil::getTimeWithStr();
            while(int index = uwbProcess(temp,ret)){
                OutFile<<time << " " << temp<<endl;
                if(cnt%5 == 0){
                    cout <<time << " " << temp<<endl;
                }
                temp+=index;
                ret -= index;
            }
        }
        usleep(ms);
        cnt++;
    }
}



int main()
{
    thread uwb(readData,uwbPort,uwbBord,uwb_r_buf,uwb_data_size,"uwb");
    thread gps(readData,gpsPort,gpsBord,gps_r_buf,gps_data_size,"gps");
    uwb.join();
    gps.join();
    return 0;
}


