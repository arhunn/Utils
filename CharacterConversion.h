#pragma once
#include <string>

namespace Utils
{
    //UTF-8תUnicode
    std::wstring Utf8ToUnicode(const std::string &utf8string);
    //unicode תΪ ascii
    std::string WideByteToAcsi(const std::wstring &wstrcode);
    //utf-8 ת ascii
    std::string Utf8ToAscii(const std::string &strUtf8Code);
    //ascii ת Unicode
    std::wstring AsciiToWideByte(const std::string &strascii);
    //Unicode ת Utf8
    std::string UnicodeToUtf8(const std::wstring &widestring);
    //ascii ת Utf8
    std::string AsciiToUtf8(const std::string &strAsciiCode);
} // namespace Utils
