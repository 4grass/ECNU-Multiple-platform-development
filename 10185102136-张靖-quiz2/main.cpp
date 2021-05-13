#include <windows.h>
#include <stdio.h>
#define ID_EDIT    1
#include <stdlib.h>
#include <commdlg.h>
#include <string.h>
#include <iostream>
using namespace std;
CHOOSEFONT   cf;
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
WNDPROC OldList ;
static HWND hwndEdit, HWnd;
LRESULT CALLBACK ListProc (HWND, UINT, WPARAM, LPARAM) ;
TCHAR szAppName[] = TEXT ("EditDemo") ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     HWND     hwnd ;
     MSG      msg ;
     WNDCLASS wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("Failed to RegisterClass! "),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     hwnd = CreateWindow (szAppName, szAppName,
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;
    HWnd =  hwnd;
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

     switch (message)
     {
     case WM_CREATE :
          hwndEdit = CreateWindow (TEXT ("edit"), NULL,                            //创建一个Edit控件
                         WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL |
                                   WS_BORDER | ES_LEFT | ES_MULTILINE |
                                   ES_AUTOHSCROLL | ES_AUTOVSCROLL,
                         0, 0, 0, 0, hwnd, (HMENU) ID_EDIT,
                         ((LPCREATESTRUCT) lParam) -> hInstance, NULL) ;
        OldList = (WNDPROC) SetWindowLong (hwndEdit, GWL_WNDPROC,
                                               (LPARAM) ListProc) ;
          return 0 ;

     case WM_SETFOCUS :
          SetFocus (hwndEdit) ;
          return 0 ;

     case WM_SIZE :
          MoveWindow (hwndEdit, 0, 0, LOWORD (lParam), HIWORD (lParam), TRUE) ;
          return 0 ;

     case WM_COMMAND :
          if (LOWORD (wParam) == ID_EDIT)
               if (HIWORD (wParam) == EN_ERRSPACE ||
                         HIWORD (wParam) == EN_MAXTEXT)

                    MessageBox (hwnd, TEXT ("Edit control out of space."),
                                szAppName, MB_OK | MB_ICONSTOP) ;

          return 0 ;
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

LRESULT CALLBACK ListProc (HWND hwnd, UINT message,
                           WPARAM wParam, LPARAM lParam)
{
  //  static HDC hd;
  static int flag=0;
    static LOGFONT logfont ;
    static HFONT   hFont ;
    static BOOL shift=FALSE;
    static BOOL ctrl=FALSE;
    CHOOSEFONT cf;
     HFONT hFontNew ;
    RECT  rect ;
    static LOGFONT lf;        // logical font structure
    static DWORD rgbCurrent;  // current text color
    static HFONT hfont;
    int iSelection;
    static LPTSTR Month[12] = {TEXT("January"), TEXT("February"), TEXT("March"),
                                      TEXT("April"), TEXT("May"), TEXT("June"),
                                      TEXT("July"), TEXT("August"), TEXT("September"),
                                      TEXT("October"), TEXT("November"), TEXT("December") };
    static LPTSTR m;
    switch (message)
    {
        case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_SHIFT :				//当按上箭头键时，变量置为真。
                shift=TRUE;
                break;
            case VK_CONTROL:
                ctrl=TRUE;
                break;
            case VK_F1:
                if(shift==TRUE)
                {
                    MessageBox(HWnd,TEXT("张靖"),TEXT("10185102136"),MB_ICONEXCLAMATION);
                    if(!(GetAsyncKeyState(VK_SHIFT)& 0x8000))
                    {
                        shift=FALSE;
                    }
                }
               if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[0]);
               }
                break;
            case VK_F2:
                 if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[1]);
               }
                break;
            case VK_F3:
                if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[2]);
               }
                break;
            case VK_F4:
                 if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[3]);
               }
                break;
            case VK_F5:
                 if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[4]);
               }
                break;
            case VK_F6:
                 if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[5]);
               }
                break;
            case VK_F7:
                if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[6]);
               }
                break;
            case VK_F8:
                if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[7]);
               }
                break;
            case VK_F9:
                 if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[8]);
               }
                break;
            case VK_F11:
                if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[10]);
               }
                break;
            case VK_F12:
                if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[11]);
               }
                break;
            }
            break;
		}
        case WM_SYSKEYDOWN:
        {
             case VK_F10:
                 if(ctrl==TRUE)
               {
                 //  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)(_T("Hello, World!")));
                  SendMessage (hwndEdit, EM_REPLACESEL, 0, (LPARAM)Month[9]);
                  SetCapture(hwndEdit);
               }
                break;
        }
        case WM_KEYUP:
        {
            switch(wParam)
            {
            case VK_SHIFT:
                shift=FALSE;
            case VK_CONTROL:
                ctrl=FALSE;
            }
            break;
        }
        case WM_RBUTTONUP:
        {
            //hd=GetDC(hwndEdit);
        ZeroMemory(&cf, sizeof(cf));
        cf.lStructSize = sizeof (cf);
        cf.hwndOwner = hwnd;
        cf.lpLogFont = &logfont ;
        cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
        if (ChooseFont(&cf)==TRUE)
        {
            hFontNew = CreateFontIndirect (&logfont) ;
             SendMessage (hwndEdit, WM_SETFONT, (WPARAM) hFontNew, 0) ;
             DeleteObject (hFont) ;
             hFont = hFontNew ;
             GetClientRect (hwndEdit, &rect) ;
             InvalidateRect (hwndEdit, &rect, TRUE) ;
            return TRUE;
        }
        break;
        }
    }
    return CallWindowProc (OldList, hwnd, message, wParam, lParam) ;
}
