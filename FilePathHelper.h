#pragma once
#include <string>
#include <vector>

namespace Utils
{
    /// \brief 检查一个指定的路径folder， 如果路径不存在，则创建新的路径
    bool CheckAndCreatePath(const std::string &folder);
    bool CheckAndCreatePathW(const std::wstring &folder);

    void GetMatchedFileNames(const std::wstring &dir,
                             const std::vector<std::wstring> &patterns,
                             std::vector<std::wstring> &file_names,
                             bool is_recursive,
                             bool hidden_dir);

    std::string PathAppendA(std::string &dest_str, const std::string &append_str);

    std::wstring PathAppendW(std::wstring &dest_str, const std::wstring &append_str);

    // "[/|?%*\\\\\"<>\]"
    std::string ValidFilePathStringA(const std::string &text, const std::string &_new);
    std::wstring ValidFilePathStringW(const std::wstring &text, const std::wstring &_new);
} // nampesapce Utils
