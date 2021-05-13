#include <windows.h>
#include <iostream>
#include "resource.h"
using namespace std;
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

HINSTANCE hInst ;
TCHAR     szAppName[] = TEXT ("PopMenu") ;

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
     wndclass.hIcon         = LoadIcon (NULL, szAppName) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = MAKEINTRESOURCE(POPMENU) ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("Failed to RegisterClass! "),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     hInst = hInstance ;

     hwnd = CreateWindow (szAppName, TEXT ("Popup Menu Demonstration"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

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
     static HMENU hMenu ;
     static HMENU hMenu1 ;
     static HMENU hMenu2 ;
     static HMENU hMenu3 ;
     RECT ClientRect;
     static HMENU hMenu4 ;
     POINT point2 ;
     RECT rc ;
     static int   idColor [5] = { WHITE_BRUSH,  LTGRAY_BRUSH, GRAY_BRUSH,
                                  DKGRAY_BRUSH, BLACK_BRUSH } ;
     static int   iSelection = IDM_BKGND_WHITE ;
     POINT        point ;

     switch (message)
     {
     case WM_CREATE:
          hMenu = LoadMenu (hInst, MAKEINTRESOURCE(POPMENU) ) ;
          hMenu = GetSubMenu (hMenu, 0) ;
          hMenu1 = GetSubMenu (hMenu, 0) ;
          hMenu2 = GetSubMenu (hMenu, 1) ;
          hMenu3 = GetSubMenu (hMenu, 2) ;
          hMenu4 = GetSubMenu (hMenu, 3) ;
          CheckMenuRadioItem(hMenu3, IDM_BKGND_WHITE, IDM_BKGND_BLACK,IDM_BKGND_WHITE, MF_BYCOMMAND);
          return 0 ;

     case WM_RBUTTONUP:
          point.x = LOWORD (lParam) ;
          point.y = HIWORD (lParam) ;
          ClientToScreen (hwnd, &point) ;
          GetWindowRect(hwnd,&rc),
          GetCursorPos (&point2) ;
          GetClientRect(hwnd,&ClientRect);	//得到窗口大小
          cout<<rc.left<<" "<<rc.top<<endl;
         if((point.y-rc.top)<=ClientRect.bottom/2 && (point.x-rc.left)<=ClientRect.right/2)
         {
             //cout<<rc.left<<endl;

            TrackPopupMenu (hMenu1, TPM_RIGHTBUTTON, point.x, point.y,
                          0, hwnd, NULL) ;
         }
         if((point.y-rc.top)>ClientRect.bottom/2 && (point.x-rc.left)<=ClientRect.right/2)
         {

            TrackPopupMenu (hMenu3, TPM_RIGHTBUTTON, point.x, point.y,
                          0, hwnd, NULL) ;
         }
         if((point.y-rc.top)<=ClientRect.bottom/2 && (point.x-rc.left)>ClientRect.right/2)
         {

            TrackPopupMenu (hMenu2, TPM_RIGHTBUTTON, point.x, point.y,
                          0, hwnd, NULL) ;
         }
         if((point.y-rc.top)>ClientRect.bottom/2 && (point.x-rc.left)>ClientRect.right/2)
         {

            TrackPopupMenu (hMenu4, TPM_RIGHTBUTTON, point.x, point.y,
                          0, hwnd, NULL) ;
         }

          return 0 ;

     case WM_COMMAND:
          switch (LOWORD (wParam))
          {
          case IDM_FILE_NEW:
          case IDM_FILE_OPEN:
          case IDM_FILE_SAVE:
          case IDM_FILE_SAVE_AS:
          case IDM_EDIT_UNDO:
          case IDM_EDIT_CUT:
          case IDM_EDIT_COPY:
          case IDM_EDIT_PASTE:
          case IDM_EDIT_CLEAR:
               MessageBeep (0) ;
               return 0 ;

          case IDM_BKGND_WHITE:         // Note: Logic below
          case IDM_BKGND_LTGRAY:        //   assumes that IDM_WHITE
          case IDM_BKGND_GRAY:          //   through IDM_BLACK are
          case IDM_BKGND_DKGRAY:        //   consecutive numbers in
          case IDM_BKGND_BLACK:         //   the order shown here.

               CheckMenuRadioItem (hMenu, IDM_BKGND_WHITE, IDM_BKGND_BLACK,iSelection, MF_BYCOMMAND) ;
               iSelection = LOWORD (wParam) ;
               CheckMenuRadioItem (hMenu, IDM_BKGND_WHITE, IDM_BKGND_BLACK,iSelection, MF_BYCOMMAND) ;

               SetClassLong (hwnd, GCL_HBRBACKGROUND, (LONG)
                    GetStockObject
                         (idColor [LOWORD (wParam) - IDM_BKGND_WHITE])) ;

               InvalidateRect (hwnd, NULL, TRUE) ;
               return 0 ;

          case IDM_APP_ABOUT:
               MessageBox (hwnd, TEXT ("Popup Menu Demonstration Program\n")
                                 TEXT (" "),
                           szAppName, MB_ICONINFORMATION | MB_OK) ;
               return 0 ;

          case IDM_APP_EXIT:
               SendMessage (hwnd, WM_CLOSE, 0, 0) ;
               return 0 ;

          case IDM_APP_HELP:
               MessageBox (hwnd, TEXT ("10185102136 张靖"),
                           szAppName, MB_ICONEXCLAMATION | MB_OK) ;
               return 0 ;
          }
          break ;

     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
