#include <iostream>

#ifndef UWB_TIMEUTIL_H
#define UWB_TIMEUTIL_H


class TimeUtil {
public:
    static std::string getTimeWithStr();
    static std::string getFilenameWithTime(const std::string& tag);
private:
    static std::time_t getTimeStamp();
    static tm* getTime(std::time_t timestamp);

};


#endif //UWB_TIMEUTIL_H
