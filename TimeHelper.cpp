#include "stdafx.h"
#include "TimeHelper.h"

#include <sstream>
#include <iomanip>
#include <time.h>

namespace Utils
{
    extern"C" char *strptime(const char *s,
                             const char *f,
                             struct tm *tm)
    {
        // Isn't the C++ standard lib nice? std::get_time is defined such that its
        // format parameters are the exact same as strptime. Of course, we have to
        // create a string stream first, and imbue it with the current C locale, and
        // we also have to make sure we return the right things if it fails, or
        // if it succeeds, but this is still far simpler an implementation than any
        // of the versions in any of the C standard libraries.
        std::istringstream input(s);
        input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
        input >> std::get_time(tm, f);
        if(input.fail()) {
            return nullptr;
        }
        return (char *)(s + input.tellg());
    }

    extern"C" wchar_t *wcsptime(const wchar_t *s,
                                const wchar_t *f,
                                struct tm *tm)
    {
        std::wstringstream input(s);
        input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
        input >> std::get_time(tm, f);
        if(input.fail()) {
            return nullptr;
        }
        return (wchar_t *)(s + input.tellg());
    }

    std::string Time2String(time_t time, const std::string &fmt)
    {
        if(time == 0) {
            return std::string();
        }
        std::string str;
        char mbstr[256];
        struct tm newtime;
        __time64_t target_time = time;
        errno_t err = ::_localtime64_s(&newtime, &target_time);
        if(err) {
            str = "";
        } else {
            if(strftime(mbstr, sizeof(mbstr), fmt.length() ? fmt.c_str() : "%c", &newtime))
                str = mbstr;
            else
                str = "";
        }
        return str;
    }

    std::wstring Time2String(time_t time, const std::wstring &fmt)
    {
        if(time == 0) {
            return std::wstring();
        }
        std::wstring str;
        wchar_t wstr[256];
        struct tm newtime;
        __time64_t target_time = time;
        errno_t err = ::_localtime64_s(&newtime, &target_time);
        if(err) {
            str = L"";
        } else {
            if(wcsftime(wstr, sizeof(wstr), fmt.length() ? fmt.c_str() : L"%c", &newtime))
                str = wstr;
            else
                str = L"";
        }
        return str;
    }

    time_t GetLocalTime()
    {
        time_t time;
        tm newtime;
        ::_time64(&time);                         // ��ȡ64λ������ʱ��.
        ::_localtime64_s(&newtime, &time);        // ת���ɱ���ʱ��.
        return time;
    }

    void GetLocalTime(time_t &time)
    {
        time = GetLocalTime();
    }

    time_t SystemTimeToTime(const SYSTEMTIME &st)
    {
        tm temptm = { st.wSecond
                      ,st.wMinute
                      ,st.wHour
                      ,st.wDay
                      ,st.wMonth - 1
                      ,st.wYear - 1900
                      ,st.wDayOfWeek
                      ,0
                      ,0
        };

        return ::mktime(&temptm);
    }

    time_t OleDateTimeToTime(const COleDateTime &dt)
    {
        SYSTEMTIME st;
        dt.GetAsSystemTime(st);
        return SystemTimeToTime(st);
    }

    time_t String2Time(std::wstring str, const std::wstring &fmt)
    {
        tm tm_;                                    // ����tm�ṹ�塣
        wcsptime(str.c_str(), fmt.c_str(), &tm_);
        time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
        return t_;
    }

    time_t String2Time(std::string str, const std::string &fmt)
    {
        tm tm_;                                    // ����tm�ṹ�塣
        strptime(str.c_str(), fmt.c_str(), &tm_);
        time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
        return t_;                                 // ����ֵ��
    }
}//namespace Utils