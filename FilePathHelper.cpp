#include "stdafx.h"
#include "FilePathHelper.h"

#include <regex>

#include <io.h>
#include <direct.h>

namespace Utils
{
    namespace Internal
    {
        const char PATH_DELIMITER = '\\';
        const wchar_t PATH_DELIMITER_W = L'\\';

        bool MatchInList(const TCHAR *file_name, const std::vector<std::wstring> &patterns)
        {
            for(size_t i = 0, len = patterns.size(); i < len; ++i) {
                if(::PathMatchSpec(file_name, patterns[i].c_str()))
                    return true;
            }
            return false;
        }

        // Source: https://blogs.msdn.microsoft.com/greggm/2005/09/21/comparing-file-names-in-native-code/
        // Modified to use TCHAR's instead of assuming Unicode and reformatted to conform with Notepad++ code style
        static TCHAR ToUpperInvariant(TCHAR input)
        {
            TCHAR result;
            LONG lres = LCMapString(LOCALE_INVARIANT, LCMAP_UPPERCASE, &input, 1, &result, 1);
            if(lres == 0) {
                result = input;
            }
            return result;
        }

        // Source: https://blogs.msdn.microsoft.com/greggm/2005/09/21/comparing-file-names-in-native-code/
        // Modified to use TCHAR's instead of assuming Unicode and reformatted to conform with Notepad++ code style
        int OrdinalIgnoreCaseCompareStrings(LPCTSTR sz1, LPCTSTR sz2)
        {
            if(sz1 == sz2) {
                return 0;
            }

            if(sz1 == nullptr) sz1 = _T("");
            if(sz2 == nullptr) sz2 = _T("");

            for(;; sz1++, sz2++) {
                const TCHAR c1 = *sz1;
                const TCHAR c2 = *sz2;

                // check for binary equality first
                if(c1 == c2) {
                    if(c1 == 0) {
                        return 0; // We have reached the end of both strings. No difference found.
                    }
                } else {
                    if(c1 == 0 || c2 == 0) {
                        return (c1 - c2); // We have reached the end of one string
                    }

                    // IMPORTANT: this needs to be upper case to match the behavior of the operating system.
                    // See http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dndotnet/html/StringsinNET20.asp
                    const TCHAR u1 = ToUpperInvariant(c1);
                    const TCHAR u2 = ToUpperInvariant(c2);
                    if(u1 != u2) {
                        return (u1 - u2); // strings are different
                    }
                }
            }
        }
    }// namespace Internal

    using namespace Internal;

    bool CheckAndCreatePath(const std::string &folder)
    {
        std::string folder_builder;
        std::string sub;
        sub.reserve(folder.size());
        for(auto it = folder.begin(); it != folder.end(); ++it) {
            const char c = *it;
            sub.push_back(c);
            if(c == Internal::PATH_DELIMITER || it == folder.end() - 1) {
                folder_builder.append(sub);
                if(0 != ::_access(folder_builder.c_str(), 0)) {
                    // this folder not exist
                    if(0 != ::_mkdir(folder_builder.c_str())) {
                        // create failed
                        return false;
                    }
                }
                sub.clear();
            }
        }
        return true;
    }
    bool CheckAndCreatePathW(const std::wstring &folder)
    {
        std::wstring folder_builder;
        std::wstring sub;
        sub.reserve(folder.size());
        for(auto it = folder.begin(); it != folder.end(); ++it) {
            const wchar_t c = *it;
            sub.push_back(c);
            if(c == Internal::PATH_DELIMITER_W || it == folder.end() - 1) {
                folder_builder.append(sub);
                if(0 != ::_waccess(folder_builder.c_str(), 0)) {
                    // this folder not exist
                    if(0 != ::_wmkdir(folder_builder.c_str())) {
                        // create failed
                        return false;
                    }
                }
                sub.clear();
            }
        }
        return true;
    }

    void GetMatchedFileNames(const std::wstring &dir, const std::vector<std::wstring> &patterns, std::vector<std::wstring> &file_names, bool is_recursive, bool hidden_dir)
    {
        std::wstring dir_filter(dir);
        Utils::PathAppendW(dir_filter, L"*.*");
        WIN32_FIND_DATA found_data;

        HANDLE file_handle = ::FindFirstFile(dir_filter.c_str(), &found_data);

        if(file_handle != INVALID_HANDLE_VALUE) {
            // 如果找到目录(文件夹)
            if(found_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if(!hidden_dir && (found_data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
                    // do nothing
                } else if(is_recursive) { // 递归
                    if((OrdinalIgnoreCaseCompareStrings(found_data.cFileName, TEXT(".")) != 0) && (OrdinalIgnoreCaseCompareStrings(found_data.cFileName, TEXT("..")) != 0)) {
                        std::wstring path(dir);
                        Utils::PathAppendW(path, found_data.cFileName);
                        GetMatchedFileNames(path.c_str(), patterns, file_names, is_recursive, hidden_dir);
                    }
                }
            } else {
                if(MatchInList(found_data.cFileName, patterns)) {
                    std::wstring path(dir);
                    Utils::PathAppendW(path, found_data.cFileName);
                    file_names.push_back(path.c_str());
                }
            }
        }
        while(::FindNextFile(file_handle, &found_data)) {
            if(found_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if(!hidden_dir && (found_data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
                    // do nothing
                } else if(is_recursive) {
                    if((OrdinalIgnoreCaseCompareStrings(found_data.cFileName, TEXT(".")) != 0) && (OrdinalIgnoreCaseCompareStrings(found_data.cFileName, TEXT("..")) != 0)) {
                        std::wstring path(dir);
                        Utils::PathAppendW(path, found_data.cFileName);
                        GetMatchedFileNames(path.c_str(), patterns, file_names, is_recursive, hidden_dir);
                    }
                }
            } else {
                if(MatchInList(found_data.cFileName, patterns)) {
                    std::wstring path(dir);
                    Utils::PathAppendW(path, found_data.cFileName);
                    file_names.push_back(path.c_str());
                }
            }
        }
        ::FindClose(file_handle);
    }

    std::string PathAppendA(std::string &dest_str, const std::string &append_str)
    {
        auto val = Utils::AsciiToWideByte(dest_str);
        auto ret = PathAppendW(val, Utils::AsciiToWideByte(append_str));
        return dest_str = Utils::WideByteToAcsi(ret);
    }

    std::wstring PathAppendW(std::wstring &dest_str, const std::wstring &append_str)
    {
        if(dest_str.empty() && append_str.empty()) { // "" + ""
            dest_str = L"\\";
            return dest_str;
        }

        if(dest_str.empty() && !append_str.empty()) { // "" + titi
            dest_str = append_str;
            return dest_str;
        }

        if(dest_str[dest_str.length() - 1] == '\\' && (!append_str.empty() && append_str[0] == '\\')) { // toto\ + \titi
            dest_str.erase(dest_str.length() - 1, 1);
            dest_str += append_str;
            return dest_str;
        }

        if((dest_str[dest_str.length() - 1] == '\\' && (!append_str.empty() && append_str[0] != '\\')) // toto\ + titi
           || (dest_str[dest_str.length() - 1] != '\\' && (!append_str.empty() && append_str[0] == '\\'))) { // toto + \titi
            dest_str += append_str;
            return dest_str;
        }

        // toto + titi
        dest_str += L"\\";
        dest_str += append_str;

        return dest_str;
    }

    std::string ValidFilePathStringA(const std::string &text, const std::string &_new)
    {
        const std::string old = "[/|?%*\\\\\"<>\]";
        std::regex pattern(old);
        std::string rep(_new);
        std::string text1(text);
        std::string tmp = std::regex_replace(text1, pattern, rep);
        return tmp;
    }

    std::wstring ValidFilePathStringW(const std::wstring &text, const std::wstring &_new)
    {
        const std::wstring old = L"[/|?%*\\\\\"<>\]";
        std::wregex pattern(old);
        std::wstring rep(_new);
        std::wstring text1(text);
        std::wstring tmp = std::regex_replace(text1, pattern, rep);
        return tmp;
    }
} // nampesapce Utils