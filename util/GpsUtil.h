#include <iostream>
using namespace std;

class GpsUtil {
public:
    static void getX(char *chr);
    static void getY(char *chr);
    static void getZ(char *chr);
    static string getTime();
    static void printGpsDataAll(char *chr);
private:
};

