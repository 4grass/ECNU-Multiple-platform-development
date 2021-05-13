#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include <cstdio>
LRESULT CALLBACK WndProc(HWND hWnd,	UINT iMessage,
					UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//初始化窗口类声明
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//初始化窗口声明
HWND hWndMain;										//定义全局窗口句柄
HINSTANCE hInst;									//定义实例句柄

OPENFILENAME ofn;
CHOOSECOLOR  chc;
CHOOSEFONT   chf;


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	HACCEL hAccel;
	hInst = hInstance;

	if(!InitWindowsClass(hInstance))		//初始化窗口类
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//初始化窗口
		return FALSE;

	hAccel = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));	//加载加速键资源
	while(GetMessage(&Message,0,0,0))
	{
		if(!TranslateAccelerator(hWndMain,hAccel,&Message))//截获加速键消息
		{
			TranslateMessage(&Message);			//消息循环
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,UINT wParam,LONG lParam)
{
	static char lpstrFileName[] = "";
	static COLORREF clref[16]={0x00ff0000};
    HDC hdc;
    HMENU hMenu1;
    HMENU haddmenu;
    static int flag1=0;
    static int flag2=0;
    static int flag3=0;
    static int flag4=0;
    static int flag5=0;
    static int flag6=1;
    PAINTSTRUCT ps;
    if(flag5==0)
    {
        flag5=1;
        hMenu1 = GetMenu(hWnd);
        CheckMenuRadioItem(hMenu1,ID_TB1,ID_TB3,ID_TB1,MF_BYCOMMAND);
    }

	switch(iMessage)
	{

    case WM_CREATE:
        hMenu1 = GetMenu(hWnd);
        haddmenu=CreateMenu();
        AppendMenu(haddmenu,MF_ENABLED,ID_EEEE,TEXT("退出\tctrl+f"));
        InsertMenu(hMenu1,0,MF_POPUP|MF_BYPOSITION,(UINT)haddmenu,TEXT("退出"));
        DrawMenuBar(hWnd);
        break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
            case ID_EEEE:
                SendMessage(hWnd,WM_DESTROY,0,0);
                break;
            case ID_XS1:
               flag1=1-flag1;
               if(flag1==1)
               {
                   hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS1,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS1,MF_UNCHECKED);
               }
               //printf("hello\n");
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_XS2:
               flag2=1-flag2;
               if(flag2==1)
               {
                   hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS2,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS2,MF_UNCHECKED);
               }
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_XS3:
               flag3=1-flag3;
               if(flag3==1)
               {
                   hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS3,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS3,MF_UNCHECKED);
               }
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_XS4:
               flag4=1-flag4;
               if(flag4==1)
               {
                   hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS4,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//得到菜单句柄
                   CheckMenuItem(hMenu1,ID_XS4,MF_UNCHECKED);
               }
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_EXIT:
                SendMessage(hWnd,WM_DESTROY,0,0);
                break;
            case ID_CX:
                MessageBox(hWnd,TEXT("张靖"),TEXT("10185102136"),MB_ICONEXCLAMATION);
                break;
            case ID_TB1:
                if(MessageBox(hWnd,TEXT("确定要改变吗？"),TEXT("改变"),MB_YESNO|MB_ICONQUESTION)==IDYES)
                {
                    hMenu1 = GetMenu(hWnd);
                    CheckMenuRadioItem(hMenu1,ID_TB1,ID_TB3,ID_TB1,MF_BYCOMMAND);
                    EnableMenuItem(hMenu1,3,MF_BYPOSITION|MF_ENABLED);
                    flag6=1;
                    SetClassLong(hWnd,GCL_HICON,(long)LoadIcon(hInst,MAKEINTRESOURCE(IDI_FIRST)));
                    InvalidateRect(hWnd,NULL,TRUE);
                    DrawMenuBar(hWnd);
                }
                break;
            case ID_TB2:
                 if(MessageBox(hWnd,TEXT("确定要改变吗？"),TEXT("改变"),MB_YESNO|MB_ICONQUESTION)==IDYES)
                {
                    hMenu1 = GetMenu(hWnd);
                    CheckMenuRadioItem(hMenu1,ID_TB1,ID_TB3,ID_TB2,MF_BYCOMMAND);
                    EnableMenuItem(hMenu1,3,MF_BYPOSITION|MF_ENABLED);
                    flag6=2;
                    SetClassLong(hWnd,GCL_HICON,(long)LoadIcon(hInst,MAKEINTRESOURCE(IDI_SECOND)));
                    InvalidateRect(hWnd,NULL,TRUE);
                    //LoadIcon(hInst,IDI_APPLICATION);
                   // SetClassLong(hWnd,GCL_HICON,(long)IDI_SECOND);
                    //InitWindowsClass(hInstance,IDI_SECOND);
                    DrawMenuBar(hWnd);
                }
                break;
            case ID_TB3:
                 if(MessageBox(hWnd,TEXT("确定要改变吗？"),TEXT("改变"),MB_YESNO|MB_ICONQUESTION)==IDYES)
                {
                    hMenu1 = GetMenu(hWnd);
                    CheckMenuRadioItem(hMenu1,ID_TB1,ID_TB3,ID_TB3,MF_BYCOMMAND);
                    EnableMenuItem(hMenu1,3,MF_BYPOSITION|MF_GRAYED);
                    flag6=3;
                     SetClassLong(hWnd,GCL_HICON,(long)LoadIcon(hInst,MAKEINTRESOURCE(IDI_THIRD)));
                    InvalidateRect(hWnd,NULL,TRUE);
                    //SendMessage(hWnd, WM_SETICON, ICON_BIG, IDI_THIRD );
                    //InitWindowsClass(hInstance,IDI_THIRD);
                    DrawMenuBar(hWnd);
                }
                break;
		}
		break;
    case WM_PAINT:
        hdc=BeginPaint(hWnd,&ps);
        if(flag1==1)
        {
            TextOut(hdc,50,50,TEXT("显示1"),lstrlen(TEXT("显示1")));
        }
        if(flag2==1)
        {
            TextOut(hdc,100,50,TEXT("显示2"),lstrlen(TEXT("显示2")));
        }
        if(flag3==1)
        {
            TextOut(hdc,50,100,TEXT("显示3"),lstrlen(TEXT("显示3")));
        }
        if(flag4==1)
        {
            TextOut(hdc,100,100,TEXT("显示4"),lstrlen(TEXT("显示4")));
        }
        if(flag6==1)
        {
            TextOut(hdc,200,200,TEXT("正在用图标1"),lstrlen(TEXT("正在用图标1")));
        }
        else if(flag6==2)
        {
            TextOut(hdc,200,200,TEXT("正在用图标2"),lstrlen(TEXT("正在用图标2")));
        }
        else if(flag6==3)
        {
            TextOut(hdc,200,200,TEXT("正在用图标3"),lstrlen(TEXT("正在用图标3")));
        }
        break;


	case WM_DESTROY:		//处理退出窗口信息.
		PostQuitMessage(0);
		return 0;
	default:
		return(DefWindowProc(hWnd,iMessage,wParam,lParam));
	}
	return 0;
}

BOOL InitWindows(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HMENU hMenu;

	hMenu = LoadMenu(hInstance,"Menu");
	hWnd=CreateWindow("7_11",				//窗口类名称.
					TEXT("10185102136 张靖"),//标题栏名称.
					WS_OVERLAPPEDWINDOW,	//窗口样式.有标题栏和最大最小化按钮.
					CW_USEDEFAULT,			//窗口左上角坐标.
					0,
					CW_USEDEFAULT,			//采用缺省的高度和宽度.
					0,
					NULL,					//无父窗口.
					hMenu,					//菜单.
					hInstance,				//当前应用实例句柄.
					NULL);					//指向传递给窗口的参数的指针.不用.
	if(!hWnd)		//创建失败.
		return FALSE;
	hWndMain=hWnd;	//给全局窗口句柄付值.
	ShowWindow(hWnd,nCmdShow);	//显示窗口.
	UpdateWindow(hWnd);			//刷新用户区.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;			//无窗口类扩展
	WndClass.cbWndExtra=0;			//无窗口实例扩展
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//背景为白色
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//光标为为箭头
	WndClass.hInstance=hInstance;			//当前实例
	WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_FIRST));	//采用缺省图标
	WndClass.lpfnWndProc=WndProc;			//消息处理函数
	WndClass.lpszClassName="7_11";			//窗口类名称
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);				//无菜单
	WndClass.style=0;						//缺省窗口风格
	return RegisterClass(&WndClass);	//返回窗口注册值
}

