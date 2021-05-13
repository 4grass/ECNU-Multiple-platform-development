#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <tchar.h>
#include <windows.h>
#include <tlhelp32.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) (GetStockObject(WHITE_BRUSH));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("10185102136 张靖"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
//

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static long nXChar,nCaps,nYChar;
    int i=0;
    HDC hDC;
    //TCHAR* c= new TCHAR [100];
    unsigned temp;
    TEXTMETRIC tm;
    PAINTSTRUCT PtStr;
    PROCESSENTRY32 pe32;
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pe32.dwSize = sizeof(pe32);
    BOOL bMore = Process32First(hProcessSnap, &pe32);
    char s[50];
    TCHAR* ss=new TCHAR [100];
    int x;
    int record=-1;
    int cmp;
    LPCTSTR l1;
    LPCTSTR l2;
    LPCTSTR l3;
    LPCTSTR l4;
    LPCTSTR text;
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            hDC=GetDC(hwnd);
            GetTextMetrics(hDC,&tm);
            nXChar=tm.tmAveCharWidth;
            nYChar=tm.tmHeight+tm.tmExternalLeading;
            ReleaseDC(hwnd,hDC);
            return 0;
        case WM_PAINT:
            hDC=BeginPaint(hwnd,&PtStr);
            l1=TEXT("Windows进程列表");
            TextOut(hDC,nXChar,nYChar*(1+i),l1,lstrlen(l1));
            i++;

                // printf("Windows进程列表\n\n"); //Title
           //PROCESSENTRY32 pe32;

           // 给所有进程拍快照
          // HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

           // 在使用这个结构之前，先设置它的大小
          // pe32.dwSize = sizeof(pe32);

          // 遍历进程快照，逐个显示进程信息
          //BOOL bMore = Process32First(hProcessSnap, &pe32);
          while (bMore)
          {
               // printf("hello\n");
                l2=TEXT(" 进程ID:  ");
                TextOut(hDC,nXChar,nYChar*(1+i),l2,lstrlen(l2));
                wsprintf(ss,TEXT("%05x"),(unsigned)pe32.th32ProcessID);
                //text=TEXT(ss);
               // CString str;
                //str.Format("%d", (unsigned)pe32.th32ProcessID);
                /*
                temp=(unsigned)pe32.th32ProcessID;
                while(temp!=0)
                {
                    cmp=temp%16;
                    temp=temp/16;
                    if(cmp<10)
                    {
                        s[++record]=cmp+'0';
                    }
                    else
                    {
                        s[++record]=cmp-10+'a';
                    }
                   // printf("%d    %c\n",cmp,s[record]);
                }
                if(record==-1)
                {
                    s[0]='0';
                    record=0;
                }
                for(x=4;x>record;x--)
                {
                    ss[4-x]='0';
                }
                for(x=record;x>=0;x--)
                {
                    ss[4-x]=s[x];
                }
                /*
                printf("world\n");
                for(x=0;x<5;x++)
                {
                    printf("%c",ss[x]);
                }
                printf("\n");
                */
                l3=TEXT("  模块名:  ");
                TextOut(hDC,nXChar*30,nYChar*(1+i),ss,lstrlen(ss));
                TextOut(hDC,nXChar*45,nYChar*(1+i),l3,lstrlen(l3));
                TextOut(hDC,nXChar*60,nYChar*(1+i),pe32.szExeFile,lstrlen(pe32.szExeFile));
                i++;
                record=-1;
              // printf("%s%05x  %s%s\n", l2,(unsigned)pe32.th32ProcessID,l3,pe32.szExeFile);
             // %S for UNICODE string
             bMore = Process32Next(hProcessSnap, &pe32);
          }
          CloseHandle(hProcessSnap); // 关闭snapshot对象
            EndPaint(hwnd,&PtStr);

            return 0;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
