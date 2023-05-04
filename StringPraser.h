#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace Utils
{
    template<typename T>
    std::wstring NumericToStringW(T val)
    {
        std::wstringstream ss;
        ss << val;
        return ss.str();
    }

    template<typename T>
    std::string NumericToString(T val)
    {
        std::stringstream ss;
        ss << val;
        return ss.str();
    }

    template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = 0>
    std::wstring NumericToStringW(T val, int precision)
    {
        std::wstringstream ss;
        ss.precision(precision);
        ss << std::fixed << val;
        return ss.str();
    }

    template<typename T, std::enable_if_t<std::is_floating_point<T>::value, bool> = 0>
    std::string NumericToString(T val, int precision)
    {
        std::stringstream ss;
        ss.precision(precision);
        ss << std::fixed << val;
        return ss.str();
    }

    template<bool>
    std::wstring NumericToStringW(bool val)
    {
        return val ? L"1" : L"0";
    }

    template<bool>
    std::string NumericToString(bool val)
    {
        return val ? "1" : "0";
    }

    template<typename T>
    T StringToNumeric(const std::wstring &value)
    {
        T val;
        std::wstringstream ss;
        ss << value.c_str();
        ss >> val;
        return val;
    }

    template<typename T>
    T StringToNumeric(const std::string &value)
    {
        T val;
        std::stringstream ss;
        ss << value.c_str();
        ss >> val;
        return val;
    }

    template<bool>
    bool StringToNumeric(const std::wstring &value)
    {
        int val{};
        std::wstringstream ss;
        ss << value.c_str();
        ss >> val;
        return val != 0;
    }

    template<bool>
    bool StringToNumeric(const std::string &value)
    {
        int val{};
        std::stringstream ss;
        ss << value.c_str();
        ss >> val;
        return val != 0;
    }

    inline void SplitString(const std::wstring &str,
                            std::vector<std::wstring> &vec,
                            const std::wstring cut)
    {
        std::string::size_type begin_index = 0;
        std::string::size_type end_index = str.find(cut);
        while(std::wstring::npos != end_index) {
            vec.push_back(str.substr(begin_index, end_index - begin_index));
            begin_index = end_index + cut.size();
            end_index = str.find(cut, begin_index);
        }
        if(begin_index != str.length())
            vec.push_back(str.substr(begin_index));
    }

    inline void SplitString(const std::string &str,
                            std::vector<std::string> &vec,
                            const std::string cut)
    {
        std::string::size_type begin_index = 0;
        std::string::size_type end_index = str.find(cut);
        while(std::string::npos != end_index) {
            auto temp_str = str.substr(begin_index, end_index - begin_index);
            if(temp_str.length()) {
                vec.push_back(temp_str);
            }
            begin_index = end_index + cut.size();
            end_index = str.find(cut, begin_index);
        }
        if(begin_index != str.length())
            vec.push_back(str.substr(begin_index));
    }
} //namespace Utils
