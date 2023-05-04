#pragma once
#include <string>

namespace Utils
{
    std::string Time2String(time_t time, const std::string &fmt);
    std::wstring Time2String(time_t time, const std::wstring &fmt = L"%Y/%m/%d,%H:%M:%S");

    time_t GetLocalTime();
    void GetLocalTime(time_t &time);

    time_t SystemTimeToTime(const SYSTEMTIME &st);

    time_t OleDateTimeToTime(const COleDateTime &dt);

    time_t String2Time(std::wstring str, const std::wstring &fmt = L"%Y/%m/%d,%H:%M:%S");
    time_t String2Time(std::string str, const std::string &fmt = "%Y/%m/%d,%H:%M:%S");
}//namespace Utils