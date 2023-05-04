#pragma once

#include <string>

namespace Utils
{
    std::wstring SelectFolder(const std::wstring &title, const std::wstring &init_path, CWnd *parent_ptr);
    /// \param filter L"File(*.docx; *.DOCX) | *.docx; *.DOCX|| "
    std::wstring OpenFile(const std::wstring &def_path, const std::wstring &filter);
    /// \param filter L"File(*.docx; *.DOCX) | *.docx; *.DOCX|| "
    std::wstring SaveFile(const std::wstring &def_path, const std::wstring &file_name, const std::wstring &filter);
}//namespace Utils