#include "stdafx.h"

namespace Utils
{
    void replace(std::string &str, const std::string &before, const std::string &after)
    {
        for(std::string::size_type pos(0); pos != std::string::npos; pos += after.length()) {
            pos = str.find(before, pos);
            if(pos != std::string::npos)
                str.replace(pos, before.length(), after);
            else
                break;
        }
    }

    void replace(std::wstring &str, const std::wstring &before, const std::wstring &after)
    {
        for(std::wstring::size_type pos(0); pos != std::wstring::npos; pos += after.length()) {
            pos = str.find(before, pos);
            if(pos != std::wstring::npos)
                str.replace(pos, before.length(), after);
            else
                break;
        }
    }

    void PumpMessage()
    {
        MSG msg;
        if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { //取消息，检索应用程序的消息队列，PM_REMOVE取过之后从消息队列中移除
            //发消息
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }

    std::wstring FormatSquareBracket(const std::wstring &sValue, bool bSpace)
    {
        if(sValue.length() == 0) {
            return std::wstring();
        }
        auto sRet = std::wstring(bSpace ? L" [" : L"[");
        sRet.append(sValue);
        sRet.append(L"]");
        return sRet;
    }

    void WndPostionCenter(CWnd *pWnd)
    {
        CRect rc;
        pWnd->GetWindowRect(rc);
        auto cx = GetSystemMetrics(SM_CXSCREEN);
        auto cy = GetSystemMetrics(SM_CYSCREEN);
        pWnd->SetWindowPos(&pWnd->wndTopMost, (cx - rc.Width()) / 2, (cy - rc.Height()) / 2, rc.Width(), rc.Height(), SWP_NOSIZE);
    }
} // namespace Utils