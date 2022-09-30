//
// Created by 提姆西 on 2022/9/30.
//
#include <iostream>
using namespace std;

class UartUtil {
public:
    int usbInit(const string& port, int bord);
    int writeData(char *send_buffer, int length) const;
    int readData(char *recv_buffer, int length) const;
    int uart_close() const;

private:
    int fd;
    int uart_open(const char *pathname);
    int uart_set(int nSpeed) const;
};


