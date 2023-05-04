#pragma once
#include <string>

namespace Utils
{
    void EnableWindowWhen(HWND whandle, bool enable);
    void EnableWindowWhen(CWnd &wnd_ref, bool enable);
    void EnableWindowWhen(CWnd *wnd_ptr, bool enable);
    void EnableWindowWhen(CWnd *wnd_ptr, UINT id, bool enable);

    void VisibleWindowWhen(HWND whandle, bool visible);
    void VisibleWindowWhen(CWnd &wnd_ref, bool visible);
    void VisibleWindowWhen(CWnd *wnd_ptr, bool visible);
    void VisibleWindowWhen(CWnd *wnd_ptr, UINT id, bool visible);

    std::wstring WindowText(HWND whandle);
    std::wstring WindowText(CWnd &wnd_ref);
    std::wstring WindowText(CWnd *wnd_ptr);
    std::wstring WindowText(CWnd *wnd_ptr, UINT id);

    bool UpdateWindowText(HWND whandle, const std::wstring &val);
    bool UpdateWindowText(CWnd &wnd_ref, const std::wstring &val);
    bool UpdateWindowText(CWnd *wnd_ptr, const std::wstring &val);
    bool UpdateWindowText(CWnd *wnd_ptr, UINT id, const std::wstring &val);
    bool UpdateWindowText(CWnd &wnd_ref, LPCTSTR format_str, ...);
    bool UpdateWindowText(CWnd *wnd_ptr, LPCTSTR format_str, ...);

    void ReadonlyWindowWhen(HWND whandle, bool readonly);
    void ReadonlyWindowWhen(CEdit &wnd_ref, bool readonly);
    void ReadonlyWindowWhen(CWnd *wnd_ptr, bool readonly);
    void ReadonlyWindowWhen(CWnd *wnd_ptr, UINT id, bool readonly);
} // nampesapce Utils
