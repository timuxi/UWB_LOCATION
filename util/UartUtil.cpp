#include <sys/fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "UartUtil.h"
using namespace std;

int UartUtil::uart_open(const char *pathname)
{
    fd = open(pathname, O_RDWR | O_NOCTTY);
    if (-1 == fd)
    {
        perror("Can't Open Serial Port");
        return (-1);
    }
    else
    {
        printf("open %s success!\n", pathname);
    }
    /*测试是否为终端设备*/
    if (isatty(STDIN_FILENO) == 0)
        printf("standard input is not a terminal device\n");
    return fd;
}

//串口名、波特率、数据位、奇偶校验位、停止位
int UartUtil::uart_set(int nSpeed) const
{
    int nStop=1;
    struct termios newtio ={};
    struct termios oldtio ={};
    /*保存测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息*/
    if (tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        printf("tcgetattr(fd,&oldtio) -> %d\n", tcgetattr(fd, &oldtio));
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    /*步骤一，设置字符大小*/
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;
    /*设置数据位*/
    switch (8)
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }
    /*设置奇偶校验位*/
    switch ('N')
    {
        case 'o':
        case 'O': //奇数
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'e':
        case 'E': //偶数
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'n':
        case 'N': //无奇偶校验位
            newtio.c_cflag &= ~PARENB;
            break;
        default:
            break;
    }
    /*设置波特率*/
    switch (nSpeed)
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }
    /*设置停止位*/
    if (nStop == 1)
        newtio.c_cflag &= ~CSTOPB;
    else if (nStop == 2)
        newtio.c_cflag |= CSTOPB;
    /*设置等待时间和最小接收字符*/
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    /*处理未接收字符*/
    tcflush(fd, TCIFLUSH);
    /*激活新配置*/
    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0)
    {
        perror("com set error");
        return -1;
    }
    return 0;
}

int UartUtil::uart_close() const
{
    close(fd);
    /*可以在这里做些清理工作*/
    return 0;
}

int UartUtil::writeData(char *send_buffer, int length) const
{
    length = write(fd, send_buffer, length * sizeof(unsigned char));
    return length;
}

long UartUtil::readData(char *recv_buffer, int length) const
{
    long ret = read(fd, recv_buffer, length);
    if (ret == -1)
    {
        printf("uart read failed!\n");
    }
    return ret;
}

int UartUtil::usbInit(const string& port, int bord)
{
    fd = uart_open(port.data());
    if (fd == -1)
    {
        cout << port << " open error\n";
        exit(EXIT_FAILURE);
    }

    if (uart_set(bord) == -1)
    {
        cout << port << " set error\n";
        exit(EXIT_FAILURE);
    }
    return fd;
}
