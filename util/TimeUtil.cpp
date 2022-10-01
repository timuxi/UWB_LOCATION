
#include <ctime>
#include <chrono>
#include <sstream>
#include "TimeUtil.h"

using namespace std;

std::time_t TimeUtil::getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp=std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    return timestamp;
}

tm* TimeUtil::getTime(std::time_t timestamp)
{
    std::time_t milli = timestamp/*+ (std::time_t)8*60*60*1000*/;//此处转化为东八区北京时间，如果是其它时区需要按需求修改
    auto mTime = std::chrono::milliseconds(milli);
    auto tp=std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* now = std::gmtime(&tt);
    std::string outTime = to_string(now->tm_year+1900) + "-"
            + to_string(now->tm_mon+1) + "-" + to_string(now->tm_mday) + " "
            + to_string(now->tm_hour+8) + ":" + to_string(now->tm_min) + ":"
            + to_string(now->tm_sec) + "." +to_string(milli%10)  ;
    return now;
}

string TimeUtil::getTimeWithStr(){
    time_t timestamp = getTimeStamp();
    std::tm* now = getTime(timestamp);
    std::string outTime = to_string(now->tm_hour+8) + ":"
                          + to_string(now->tm_min) + ":"
                          + to_string(now->tm_sec) + "."
                          + to_string(timestamp%10);
    return outTime;
}

string TimeUtil::getFilenameWithTime(const string& tag)
{
    std::tm* now = getTime(getTimeStamp());
    std::string outTime = tag +  "_" + to_string(now->tm_year+1900) + "-"
                          + to_string(now->tm_mon+1) + "-"
                          + to_string(now->tm_mday) + " "
                          + to_string(now->tm_hour+8) + ":"
                          + to_string(now->tm_min) + ":"
                          + to_string(now->tm_sec) + ".txt";
    return outTime;
}
