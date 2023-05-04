#include "stdafx.h"
#include "WndHelper.h"

namespace Utils
{
    void EnableWindowWhen(HWND whandle, bool enable)
    {
        if(::IsWindow(whandle)) {
            auto val = (enable ? TRUE : FALSE);
            if(::IsWindowEnabled(whandle) != val) {
                ::EnableWindow(whandle, val);
            }
        }
    }

    void EnableWindowWhen(CWnd &wnd_ref, bool enable)
    {
        EnableWindowWhen(wnd_ref.GetSafeHwnd(), enable);
    }

    void EnableWindowWhen(CWnd *wnd_ptr, bool enable)
    {
        if(wnd_ptr) {
            EnableWindowWhen(wnd_ptr->GetSafeHwnd(), enable);
        }
    }

    void EnableWindowWhen(CWnd *wnd_ptr, UINT id, bool enable)
    {
        if(wnd_ptr) {
            EnableWindowWhen(wnd_ptr->GetDlgItem(id), enable);
        }
    }

    void VisibleWindowWhen(HWND whandle, bool visible)
    {
        if(::IsWindow(whandle)) {
            auto val = (visible ? SW_SHOW : SW_HIDE);
            ::ShowWindow(whandle, val);
        }
    }

    void VisibleWindowWhen(CWnd &wnd_ref, bool visible)
    {
        VisibleWindowWhen(wnd_ref.GetSafeHwnd(), visible);
    }

    void VisibleWindowWhen(CWnd *wnd_ptr, bool visible)
    {
        if(wnd_ptr) {
            VisibleWindowWhen(wnd_ptr->GetSafeHwnd(), visible);
        }
    }

    void VisibleWindowWhen(CWnd *wnd_ptr, UINT id, bool visible)
    {
        if(wnd_ptr) {
            VisibleWindowWhen(wnd_ptr->GetDlgItem(id), visible);
        }
    }

    std::wstring WindowText(HWND whandle)
    {
        if(::IsWindow(whandle)) {
            static wchar_t str[1024];
            ::GetWindowTextW(whandle, str, 1023);
            return std::wstring(str);
        }
        return std::wstring();
    }

    std::wstring WindowText(CWnd &wnd_ref)
    {
        return WindowText(wnd_ref.GetSafeHwnd());
    }

    std::wstring WindowText(CWnd *wnd_ptr)
    {
        return WindowText(wnd_ptr->GetSafeHwnd());
    }

    std::wstring WindowText(CWnd *wnd_ptr, UINT id)
    {
        return WindowText(wnd_ptr->GetDlgItem(id));
    }

    bool UpdateWindowText(HWND whandle, const std::wstring &val)
    {
        if(::IsWindow(whandle)) {
            auto &text = WindowText(whandle);
            if(0 != val.compare(text)) {
                ::SetWindowTextW(whandle, val.c_str());
                return true;
            }
        }
        return false;
    }

    bool UpdateWindowText(CWnd &wnd_ref, const std::wstring &val)
    {
        return UpdateWindowText(wnd_ref.GetSafeHwnd(), val);
    }

    bool UpdateWindowText(CWnd *wnd_ptr, const std::wstring &val)
    {
        return UpdateWindowText(wnd_ptr->GetSafeHwnd(), val);
    }

    bool UpdateWindowText(CWnd *wnd_ptr, UINT id, const std::wstring &val)
    {
        return UpdateWindowText(wnd_ptr->GetDlgItem(id), val);
    }

    bool UpdateWindowText(CWnd &wnd_ref, LPCTSTR format_str, ...)
    {
        if(!wnd_ref.GetSafeHwnd()) {
            return false;
        }
        // Initialize variable arguments list
        va_list args_list;
        va_start(args_list, format_str);

        // Format the message
        CString str_temp, str_text;
        str_temp.FormatV(format_str, args_list);
        wnd_ref.GetWindowText(str_text);

        if(str_temp == str_text) {
            va_end(args_list);
            return false;
        } else {
            wnd_ref.SetWindowText(str_temp);
        }

        // Null the argument list pointer
        va_end(args_list);
        return true;
    }

    bool UpdateWindowText(CWnd *wnd_ptr, LPCTSTR format_str, ...)
    {
        if(!wnd_ptr) {
            return false;
        }

        return UpdateWindowText(*wnd_ptr, format_str);
    }

    void ReadonlyWindowWhen(HWND whandle, bool readonly)
    {
        if(::IsWindow(whandle)) {
            auto val = (readonly ? TRUE : FALSE);
            ::SendMessageW( //returnsLRESULTinlResult
                           whandle,    // handle to destination control
                           (UINT)EM_SETREADONLY,   // message ID
                           val,
                           0   //=0;notused,mustbezero
            );
        }
    }

    void ReadonlyWindowWhen(CEdit &wnd_ref, bool readonly)
    {
        ReadonlyWindowWhen(wnd_ref.GetSafeHwnd(), readonly);
    }

    void ReadonlyWindowWhen(CWnd *wnd_ptr, bool readonly)
    {
        if(wnd_ptr) {
            ReadonlyWindowWhen(wnd_ptr->GetSafeHwnd(), readonly);
        }
    }

    void ReadonlyWindowWhen(CWnd *wnd_ptr, UINT id, bool readonly)
    {
        if(wnd_ptr) {
            ReadonlyWindowWhen(wnd_ptr->GetDlgItem(id), readonly);
        }
    }
} // nampesapce Utils