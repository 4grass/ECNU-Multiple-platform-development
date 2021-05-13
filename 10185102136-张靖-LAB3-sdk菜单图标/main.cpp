#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include <cstdio>
LRESULT CALLBACK WndProc(HWND hWnd,	UINT iMessage,
					UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������
HWND hWndMain;										//����ȫ�ִ��ھ��
HINSTANCE hInst;									//����ʵ�����

OPENFILENAME ofn;
CHOOSECOLOR  chc;
CHOOSEFONT   chf;


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
	MSG Message;
	HACCEL hAccel;
	hInst = hInstance;

	if(!InitWindowsClass(hInstance))		//��ʼ��������
		return FALSE;
	if(!InitWindows(hInstance,nCmdShow))	//��ʼ������
		return FALSE;

	hAccel = LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));	//���ؼ��ټ���Դ
	while(GetMessage(&Message,0,0,0))
	{
		if(!TranslateAccelerator(hWndMain,hAccel,&Message))//�ػ���ټ���Ϣ
		{
			TranslateMessage(&Message);			//��Ϣѭ��
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
        AppendMenu(haddmenu,MF_ENABLED,ID_EEEE,TEXT("�˳�\tctrl+f"));
        InsertMenu(hMenu1,0,MF_POPUP|MF_BYPOSITION,(UINT)haddmenu,TEXT("�˳�"));
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
                   hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS1,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS1,MF_UNCHECKED);
               }
               //printf("hello\n");
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_XS2:
               flag2=1-flag2;
               if(flag2==1)
               {
                   hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS2,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS2,MF_UNCHECKED);
               }
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_XS3:
               flag3=1-flag3;
               if(flag3==1)
               {
                   hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS3,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS3,MF_UNCHECKED);
               }
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_XS4:
               flag4=1-flag4;
               if(flag4==1)
               {
                   hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS4,MF_CHECKED);
               }
               else
               {
                    hMenu1 = GetMenu(hWnd);		//�õ��˵����
                   CheckMenuItem(hMenu1,ID_XS4,MF_UNCHECKED);
               }
               InvalidateRect(hWnd,NULL,TRUE);
               break;
            case ID_EXIT:
                SendMessage(hWnd,WM_DESTROY,0,0);
                break;
            case ID_CX:
                MessageBox(hWnd,TEXT("�ž�"),TEXT("10185102136"),MB_ICONEXCLAMATION);
                break;
            case ID_TB1:
                if(MessageBox(hWnd,TEXT("ȷ��Ҫ�ı���"),TEXT("�ı�"),MB_YESNO|MB_ICONQUESTION)==IDYES)
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
                 if(MessageBox(hWnd,TEXT("ȷ��Ҫ�ı���"),TEXT("�ı�"),MB_YESNO|MB_ICONQUESTION)==IDYES)
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
                 if(MessageBox(hWnd,TEXT("ȷ��Ҫ�ı���"),TEXT("�ı�"),MB_YESNO|MB_ICONQUESTION)==IDYES)
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
            TextOut(hdc,50,50,TEXT("��ʾ1"),lstrlen(TEXT("��ʾ1")));
        }
        if(flag2==1)
        {
            TextOut(hdc,100,50,TEXT("��ʾ2"),lstrlen(TEXT("��ʾ2")));
        }
        if(flag3==1)
        {
            TextOut(hdc,50,100,TEXT("��ʾ3"),lstrlen(TEXT("��ʾ3")));
        }
        if(flag4==1)
        {
            TextOut(hdc,100,100,TEXT("��ʾ4"),lstrlen(TEXT("��ʾ4")));
        }
        if(flag6==1)
        {
            TextOut(hdc,200,200,TEXT("������ͼ��1"),lstrlen(TEXT("������ͼ��1")));
        }
        else if(flag6==2)
        {
            TextOut(hdc,200,200,TEXT("������ͼ��2"),lstrlen(TEXT("������ͼ��2")));
        }
        else if(flag6==3)
        {
            TextOut(hdc,200,200,TEXT("������ͼ��3"),lstrlen(TEXT("������ͼ��3")));
        }
        break;


	case WM_DESTROY:		//�����˳�������Ϣ.
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
	hWnd=CreateWindow("7_11",				//����������.
					TEXT("10185102136 �ž�"),//����������.
					WS_OVERLAPPEDWINDOW,	//������ʽ.�б������������С����ť.
					CW_USEDEFAULT,			//�������Ͻ�����.
					0,
					CW_USEDEFAULT,			//����ȱʡ�ĸ߶ȺͿ��.
					0,
					NULL,					//�޸�����.
					hMenu,					//�˵�.
					hInstance,				//��ǰӦ��ʵ�����.
					NULL);					//ָ�򴫵ݸ����ڵĲ�����ָ��.����.
	if(!hWnd)		//����ʧ��.
		return FALSE;
	hWndMain=hWnd;	//��ȫ�ִ��ھ����ֵ.
	ShowWindow(hWnd,nCmdShow);	//��ʾ����.
	UpdateWindow(hWnd);			//ˢ���û���.
	return TRUE;
}

BOOL InitWindowsClass(HINSTANCE hInstance)
{
	WNDCLASS WndClass;

	WndClass.cbClsExtra=0;			//�޴�������չ
	WndClass.cbWndExtra=0;			//�޴���ʵ����չ
	WndClass.hbrBackground=(HBRUSH)(GetStockObject(WHITE_BRUSH));//����Ϊ��ɫ
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);	//���ΪΪ��ͷ
	WndClass.hInstance=hInstance;			//��ǰʵ��
	WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_FIRST));	//����ȱʡͼ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="7_11";			//����������
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);				//�޲˵�
	WndClass.style=0;						//ȱʡ���ڷ��
	return RegisterClass(&WndClass);	//���ش���ע��ֵ
}

