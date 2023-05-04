#include "stdafx.h"

#include "FileDialogHelper.h"

namespace Utils
{
    std::wstring SelectFolder(const std::wstring &title, const std::wstring &init_path, CWnd *parent_ptr)
    {
        auto fun = [](CString pszPath, LPITEMIDLIST &pidl) {
            LPSHELLFOLDER pDesktopFolder = NULL;
            HRESULT       hr;

            if(SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder))) {
                hr = pDesktopFolder->ParseDisplayName(NULL, NULL, pszPath.GetBuffer(), NULL, &pidl, NULL);
                pDesktopFolder->Release();
            }
        };

        wchar_t          folder_path[255] = { 0 };
        std::wstring     folder_path_str;
        BROWSEINFO       browse_info;
        ::ZeroMemory(&browse_info, sizeof(BROWSEINFO));
        LPITEMIDLIST pidlRoot = NULL;
        fun(init_path.c_str(), pidlRoot);
        browse_info.pidlRoot = pidlRoot;
        browse_info.lpszTitle = title.c_str();
        browse_info.ulFlags = BIF_USENEWUI;
        browse_info.ulFlags |= BIF_RETURNONLYFSDIRS;
        browse_info.ulFlags |= BIF_EDITBOX;
        browse_info.ulFlags |= BIF_STATUSTEXT;
        browse_info.ulFlags |= BIF_DONTGOBELOWDOMAIN;
        browse_info.lpfn = NULL;
        browse_info.hwndOwner = parent_ptr->GetSafeHwnd();

        if(browse_info.ulFlags & BIF_USENEWUI) {
            ::OleInitialize(NULL);
        }

        LPITEMIDLIST    lpidl_browse = ::SHBrowseForFolder(&browse_info);
        if(lpidl_browse != NULL) {
            if(::SHGetPathFromIDListW(lpidl_browse, folder_path)) {
                folder_path_str = folder_path;
            }
        }
        if(lpidl_browse != NULL) {
            ::CoTaskMemFree(lpidl_browse);
        }
        return folder_path_str;
    }

    std::wstring OpenFile(const std::wstring &def_path, const std::wstring &filter)
    {
        CFileDialog dlg_file(TRUE, def_path.c_str(), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, filter.c_str(), nullptr);
        INT_PTR result = dlg_file.DoModal();
        if(result == IDOK)
            return std::wstring(dlg_file.GetPathName().GetString());
        else
            return def_path;
    }

    std::wstring SaveFile(const std::wstring &def_path, const std::wstring &file_name, const std::wstring &filter)
    {
        CFileDialog dlg_file(FALSE, def_path.c_str(), file_name.c_str(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter.c_str(), nullptr);
        INT_PTR result = dlg_file.DoModal();
        if(result == IDOK)
            return std::wstring(dlg_file.GetPathName().GetString());
        else
            return std::wstring();
    }
}//namespace Utils