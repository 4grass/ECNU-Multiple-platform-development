#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "resource.h"
#include <cstdio>
#include <iostream>
using namespace std;
LRESULT CALLBACK WndProc(HWND hWnd,	UINT iMessage,
					UINT wParam,LONG lParam);
BOOL InitWindowsClass(HINSTANCE hInstance);			//��ʼ������������
BOOL InitWindows(HINSTANCE hInstance, int nCmdShow);//��ʼ����������
HWND hWndMain;										//����ȫ�ִ��ھ��
HINSTANCE hInst;									//����ʵ�����
BOOL CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);		//�Ի�������
HWND hDlg=0;				//����Ի�����
OPENFILENAME ofn;
CHOOSECOLOR  chc;
CHOOSEFONT   chf;
int judge=0;
int cjudge=1;
int gjudge=1;
int radioflag1=1;
int radioflag2=0;
int radioflag3=0;
int radiotemp1=0;
int radiotemp2=0;
int radiotemp3=0;
int checkflag1=0;
int checkflag2=0;
int checkflag3=0;
int checktemp1=0;
int checktemp2=0;
int checktemp3=0;
TCHAR temp[260]="";
TCHAR szFile[260]=" ";
HDC hdcmem;
HDC hdc;
HBITMAP hBm;
BITMAP bm;
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
		    if((!IsWindow(hDlg) || !IsDialogMessage(hDlg,&Message)) && (!TranslateAccelerator(hWndMain,hAccel,&Message)))
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
    HMENU hMenu1;
    HMENU haddmenu;
    PAINTSTRUCT ps;
	switch(iMessage)
	{

        case WM_CREATE:
		//ע��:�˴�ֻ��ע��һЩ���õ�OPENFILENAME�ṹ�ĳ�Ա
		ZeroMemory(&ofn,sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);				//���ݽṹ����
		ofn.hwndOwner=hWnd;
        ofn.lpstrFile=szFile;
        ofn.nMaxFile=sizeof(szFile);
        	ofn.lpstrFilter ="All Files (*.*)\0*.*\0";
			//�ļ�������
        ofn.nFilterIndex=1;
        ofn.lpstrFileTitle=NULL;
        ofn.nMaxFileTitle=0;
        ofn.lpstrInitialDir=NULL;
        ofn.Flags=OFN_HIDEREADONLY|OFN_CREATEPROMPT;
        hdc=GetDC(hWnd);
        hdcmem=CreateCompatibleDC(hdc);
        ReleaseDC(hWnd,hdc);
        break;
    case WM_COMMAND:
		switch(LOWORD(wParam))
		{
            case ID_40012:
                MessageBox(hWnd,TEXT("�ž�"),TEXT("10185102136"),MB_ICONEXCLAMATION);
                break;
            case ID_40001:
                SendMessage(hWnd,WM_DESTROY,0,0);
                break;
            case ID_Menu:
                hMenu1 = GetMenu(hWnd);
                CheckMenuRadioItem(hMenu1,ID_Menu,ID_40010 ,ID_Menu,MF_BYCOMMAND);
                SetClassLong(hWnd,GCL_HCURSOR,(long)LoadCursor (NULL, IDC_ARROW));
                gjudge=1;
                //SetCursor (LoadCursor (NULL, IDC_ARROW)) ;
                InvalidateRect(hWnd,NULL,TRUE);
                DrawMenuBar(hWnd);
                break;
            case ID_40009:
                hMenu1 = GetMenu(hWnd);
                CheckMenuRadioItem(hMenu1,ID_Menu,ID_40010,ID_40009,MF_BYCOMMAND);
               // SetCursor (LoadCursor (NULL, IDC_CROSS)) ;
                SetClassLong(hWnd,GCL_HCURSOR,(long)LoadCursor (NULL, IDC_CROSS));
                gjudge=2;
                InvalidateRect(hWnd,NULL,TRUE);
                DrawMenuBar(hWnd);
                break;
            case ID_40010:
                hMenu1 = GetMenu(hWnd);
                CheckMenuRadioItem(hMenu1,ID_Menu,ID_40010 ,ID_40010,MF_BYCOMMAND);
               // SetCursor (LoadCursor (hInst, MAKEINTRESOURCE(IDC_CURSOR1))) ;
                SetClassLong(hWnd,GCL_HCURSOR,(long)LoadCursor(hInst,MAKEINTRESOURCE(IDC_CURSOR1)));
                gjudge=3;
                InvalidateRect(hWnd,NULL,TRUE);
                DrawMenuBar(hWnd);
                break;
            case ID_40005:
                judge=1;
                DialogBox(hInst,MAKEINTRESOURCE(IDD_DIALOG1),hWnd,(DLGPROC)DlgProc);
                break;
            case ID_40006:
                judge=2;
                hDlg=CreateDialog(hInst,MAKEINTRESOURCE(IDD_DIALOG2),hWnd,(DLGPROC)DlgProc);
                break;
            case ID_40007:
                //����ͨ�öԻ�����ʽ
                //ofn.Flags = OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
                ofn.lpstrTitle = "��";				//ͨ�öԻ������
                if(GetOpenFileName(&ofn)==TRUE)
                {
                    MessageBox(hWnd,szFile,"�ļ���",MB_OK);
                }//��ʾ�Ի���
                break;
            case ID_Menu40013:
                cjudge=1;
                hMenu1 = GetMenu(hWnd);
                LoadString(hInst,IDS_STRING126,temp,260);
                ModifyMenu(hMenu1,0,MF_BYPOSITION,0,temp);

                LoadString(hInst,IDS_STRING127,temp,260);
                ModifyMenu(hMenu1,ID_40001,MF_BYCOMMAND,ID_40001,temp);

                LoadString(hInst,IDS_STRING128,temp,260);
                ModifyMenu(hMenu1,1,MF_BYPOSITION,1,temp);

                LoadString(hInst,IDS_STRING129,temp,260);
                ModifyMenu(hMenu1,ID_40005,MF_BYCOMMAND,ID_40005,temp);

                LoadString(hInst,IDS_STRING130,temp,260);
                ModifyMenu(hMenu1,ID_40006,MF_BYCOMMAND,ID_40006,temp);

                LoadString(hInst,IDS_STRING131,temp,260);
                ModifyMenu(hMenu1,ID_40007,MF_BYCOMMAND,ID_40007,temp);

                LoadString(hInst,IDS_STRING132,temp,260);
                ModifyMenu(hMenu1,2,MF_BYPOSITION,2,temp);

                LoadString(hInst,IDS_STRING133,temp,260);
                ModifyMenu(hMenu1,ID_Menu,MF_BYCOMMAND,ID_Menu,temp);

                LoadString(hInst,IDS_STRING134,temp,260);
                ModifyMenu(hMenu1,ID_40009,MF_BYCOMMAND,ID_40009,temp);

                LoadString(hInst,IDS_STRING135,temp,260);
                ModifyMenu(hMenu1,ID_40010,MF_BYCOMMAND,ID_40010,temp);

                LoadString(hInst,IDS_STRING136,temp,260);
                ModifyMenu(hMenu1,3,MF_BYPOSITION,3,temp);

                LoadString(hInst,IDS_STRING137,temp,260);
                ModifyMenu(hMenu1, ID_Menu40013,MF_BYCOMMAND, ID_Menu40013,temp);

                LoadString(hInst,IDS_STRING138,temp,260);
                ModifyMenu(hMenu1, ID_40014,MF_BYCOMMAND, ID_40014,temp);

                LoadString(hInst,IDS_STRING139,temp,260);
                ModifyMenu(hMenu1,4,MF_BYPOSITION,4,temp);

                LoadString(hInst,IDS_STRING140,temp,260);
                ModifyMenu(hMenu1, ID_40012,MF_BYCOMMAND, ID_40012,temp);

                LoadString(hInst,IDS_STRING141,temp,260);
                SetWindowText(hWnd, temp);
                InvalidateRect(hWndMain,NULL,TRUE);
                DrawMenuBar(hWnd);
                break;
            case ID_40014:
                //cout<<1<<endl;
                cjudge=2;
                hMenu1 = GetMenu(hWnd);
                LoadString(hInst,IDS_STRING111,temp,260);
                ModifyMenu(hMenu1,0,MF_BYPOSITION,0,temp);

                LoadString(hInst,IDS_STRING112,temp,260);
                ModifyMenu(hMenu1,ID_40001,MF_BYCOMMAND,ID_40001,temp);

                LoadString(hInst,IDS_STRING113,temp,260);
                ModifyMenu(hMenu1,1,MF_BYPOSITION,1,temp);

                LoadString(hInst,IDS_STRING114,temp,260);
                ModifyMenu(hMenu1,ID_40005,MF_BYCOMMAND,ID_40005,temp);

                LoadString(hInst,IDS_STRING115,temp,260);
                ModifyMenu(hMenu1,ID_40006,MF_BYCOMMAND,ID_40006,temp);

                LoadString(hInst,IDS_STRING116,temp,260);
                ModifyMenu(hMenu1,ID_40007,MF_BYCOMMAND,ID_40007,temp);

                LoadString(hInst,IDS_STRING117,temp,260);
                ModifyMenu(hMenu1,2,MF_BYPOSITION,2,temp);

                LoadString(hInst,IDS_STRING118,temp,260);
                ModifyMenu(hMenu1,ID_Menu,MF_BYCOMMAND,ID_Menu,temp);

                LoadString(hInst,IDS_STRING119,temp,260);
                ModifyMenu(hMenu1,ID_40009,MF_BYCOMMAND,ID_40009,temp);

                LoadString(hInst,IDS_STRING120,temp,260);
                ModifyMenu(hMenu1,ID_40010,MF_BYCOMMAND,ID_40010,temp);

                LoadString(hInst,IDS_STRING121,temp,260);
                ModifyMenu(hMenu1,3,MF_BYPOSITION,3,temp);

                LoadString(hInst,IDS_STRING122,temp,260);
                ModifyMenu(hMenu1, ID_Menu40013,MF_BYCOMMAND, ID_Menu40013,temp);

                LoadString(hInst,IDS_STRING123,temp,260);
                ModifyMenu(hMenu1, ID_40014,MF_BYCOMMAND, ID_40014,temp);

                LoadString(hInst,IDS_STRING124,temp,260);
                ModifyMenu(hMenu1,4,MF_BYPOSITION,4,temp);

                LoadString(hInst,IDS_STRING125,temp,260);
                ModifyMenu(hMenu1, ID_40012,MF_BYCOMMAND, ID_40012,temp);
                LoadString(hInst,IDS_STRING142,temp,260);
                //SetClassLong(hWnd,GCL_MENUNAME,(long)TEXT("10185102136 Zaneking"));
                SetWindowText(hWnd, temp);
                InvalidateRect(hWndMain,NULL,TRUE);
                DrawMenuBar(hWnd);
                break;
		}
    case WM_PAINT:
        hdc=BeginPaint(hWnd,&ps);
        if(gjudge==1)
        {
            if(cjudge==1)
            {
                TextOut(hdc,50,20,TEXT("��Ĺ����:��ͷ"),lstrlen(TEXT("��Ĺ����:��ͷ")));
            }
            else
            {
                TextOut(hdc,50,20,TEXT("your cursor:arrow"),lstrlen(TEXT("your cursor:arrow")));
            }
        }
         if(gjudge==2)
        {
            if(cjudge==1)
            {
                TextOut(hdc,50,20,TEXT("��Ĺ����:ʮ��"),lstrlen(TEXT("��Ĺ����:ʮ��")));
            }
            else
            {
                TextOut(hdc,50,20,TEXT("your cursor:cross"),lstrlen(TEXT("your cursor:cross")));
            }
        }
         if(gjudge==3)
        {
            if(cjudge==1)
            {
                TextOut(hdc,50,20,TEXT("��Ĺ����:�Լ�����"),lstrlen(TEXT("��Ĺ����:�Լ�����")));
            }
            else
            {
                TextOut(hdc,50,20,TEXT("your cursor:yourself"),lstrlen(TEXT("your cursor:yourself")));
            }
        }
        if(radioflag1==1)
        {
             hBm=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));
             GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);
             SelectObject(hdcmem,hBm);
             BitBlt(hdc,200,50,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
        }
        if(radioflag2==1)
        {
             hBm=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP2));
             GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);
             SelectObject(hdcmem,hBm);
             BitBlt(hdc,200,50,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
        }
        if(radioflag3==1)
        {
             hBm=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
             GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);
             SelectObject(hdcmem,hBm);
             BitBlt(hdc,200,50,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
        }
        if(checkflag1==1)
        {
             hBm=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP1));
             GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);
             SelectObject(hdcmem,hBm);
             BitBlt(hdc,100,50,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
        }
        if(checkflag2==1)
        {
             hBm=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP2));
             GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);
             SelectObject(hdcmem,hBm);
             BitBlt(hdc,100,100,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
        }
        if(checkflag3==1)
        {
             hBm=LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BITMAP3));
             GetObject(hBm,sizeof(BITMAP),(LPVOID)&bm);
             SelectObject(hdcmem,hBm);
             BitBlt(hdc,100,150,bm.bmWidth,bm.bmHeight,hdcmem,0,0,SRCCOPY);
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
    //cout<<"hello"<<" "<<radioflag1<<" "<<radioflag2<<" "<<radioflag3<<endl;
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
	WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));	//����ȱʡͼ��
	WndClass.lpfnWndProc=WndProc;			//��Ϣ������
	WndClass.lpszClassName="7_11";			//����������
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);				//�޲˵�
	WndClass.style=0;						//ȱʡ���ڷ��
	return RegisterClass(&WndClass);	//���ش���ע��ֵ
}
BOOL CALLBACK DlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
    if(judge==2)
    {
        switch(message)
        {
        case WM_INITDIALOG:			//��ʼ���Ի���
            if(radioflag1==1)
            {
                CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO3,IDC_RADIO1);
            }
            if(radioflag2==1)
            {
                CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);
            }
            if(radioflag3==1)
            {
                CheckRadioButton(hDlg,IDC_RADIO1,IDC_RADIO3,IDC_RADIO3);
            }
            return 1;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
            case IDOK:
                radioflag1=radiotemp1;
                radioflag2=radiotemp2;
                radioflag3=radiotemp3;
                //cout<<radioflag1<<" "<<radioflag2<<" "<<radioflag3<<endl;
                InvalidateRect(hWndMain,NULL,TRUE);
                return 1;
            case IDC_RADIO1:
                radiotemp1=1;
                radiotemp2=0;
                radiotemp3=0;
                return 1;
            case IDC_RADIO2:
                radiotemp1=0;
                radiotemp2=1;
                radiotemp3=0;
                return 1;
            case IDC_RADIO3:
                radiotemp1=0;
                radiotemp2=0;
                radiotemp3=1;
                return 1;
            case IDCANCEL:
                EndDialog(hDlg,0);
                return 1;
            }
            return 1;
        case WM_CLOSE:
            EndDialog(hDlg,0);
            return 1;
        }
        return 0;
    }
    if(judge==1)
    {
        switch(message)
        {
            case WM_INITDIALOG:		//��ʼ���Ի���
                if(checkflag1==1)
                {
                    CheckDlgButton(hDlg,IDC_CHECK1,BST_CHECKED);
                }
                if(checkflag2==1)
                {
                    CheckDlgButton(hDlg,IDC_CHECK2,BST_CHECKED);
                }
                if(checkflag3==1)
                {
                    CheckDlgButton(hDlg,IDC_CHECK3,BST_CHECKED);
                }
                return 1;
            case WM_COMMAND:
                switch(LOWORD(wParam))
                {
                case IDOK:
                    checkflag1=checktemp1;
                    checkflag2=checktemp2;
                    checkflag3=checktemp3;
                    //cout<<radioflag1<<" "<<radioflag2<<" "<<radioflag3<<endl;
                    InvalidateRect(hWndMain,NULL,TRUE);
                    EndDialog(hDlg,0);
                    return 1;
                case IDC_CHECK1:
                    checktemp1=1-checktemp1;
                    return 1;
                case IDC_CHECK2:
                    checktemp2=1-checktemp2;
                    return 1;
                case IDC_CHECK3:
                    checktemp3=1-checktemp3;
                    return 1;
                case IDCANCEL:
                    checktemp1=checkflag1;
                    checktemp2=checkflag2;
                    checktemp3=checkflag3;
                    EndDialog(hDlg,0);
                    return 1;
                }
                return 1;
            case WM_CLOSE:
                EndDialog(hDlg,0);
                return 1;
        }
        return 0;
    }

}

