#include <windows.h>
#include "CURVE.h"
#include <iostream>
#include <fstream>
#include <commdlg.h>
OPENFILENAME ofn ;
using namespace std;
ofstream fs2;
HINSTANCE hInst;      // current instance
HWND hWnd;
int zhuangtai=0;
int diedai=0;
int flag=0;
int nState=0;
int rState=0;
BOOL fErase=FALSE;
BOOL rErase=FALSE;
POINT point[4];
POINT point2[3];
POINT spoint1[10000];
POINT spoint2[10000]; //存储三角形坐标
POINT tpoint2[10000];
POINT tpoint1[10000];
POINT rpoint1[10000];
POINT rpoint2[10000];
int trnext2=0;
int trnext1=0;
int tnext2=0;
int tnext1=0;
int next2=0;
int next1=0;
TCHAR szFile[260]=" ";
PAINTSTRUCT PtStr;
int WINAPI WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{  if (!InitApplication(hInstance)) return FALSE;

   if (!InitInstance(hInstance,nCmdShow)) return FALSE;

   MSG msg;
   while (GetMessage(&msg, NULL, 0, 0))
   {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
   }
   return (int)msg.wParam;
}

BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    wc.style         = NULL;
    wc.lpfnWndProc   = (WNDPROC)MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.lpszClassName = TEXT("curveWClass");
    wc.lpszMenuName  = TEXT("curveMenu");
    return RegisterClass(&wc);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd  =     CreateWindow(TEXT("curveWClass"),
                            TEXT("curve demo  Window "),
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            NULL,
                            NULL,
                            hInstance,
                            NULL);

   if (!hWnd) return FALSE;
   nCmdShow=SW_SHOWMAXIMIZED;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    HDC temp;
   int xPos,yPos;
    BOOL                      bSuccess ;
    static TCHAR szFilter[] = TEXT ("Bitmap Files (*.BMP)\0*.bmp\0")
                               TEXT ("All Files (*.*)\0*.*\0\0") ;
    static HDC  hdcClient, hdcWindow ;
     LPCTSTR szFileName=TEXT("10185102136张靖");
     LPCTSTR szTitleName=TEXT("10185102136张靖");
       static HDC hdcMem;
      HBITMAP hBitmap;
     PAINTSTRUCT ps ;
    static BITMAPFILEHEADER * pbmfh ;
   switch (message) {
        case WM_CREATE:
        ZeroMemory(&ofn,sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);				//数据结构长度
		ofn.hwndOwner=hWnd;
        ofn.lpstrFile=szFile;
        ofn.nMaxFile=sizeof(szFile);
        	ofn.lpstrFilter ="All Files (*.*)\0*.*\0";
			//文件过滤器
        ofn.nFilterIndex=1;
        ofn.lpstrFileTitle=NULL;
        ofn.nMaxFileTitle=0;
        ofn.lpstrInitialDir=NULL;
        ofn.Flags=OFN_HIDEREADONLY|OFN_CREATEPROMPT;
        break;
      case WM_LBUTTONDOWN:
          xPos=LOWORD(lParam);   yPos=HIWORD(lParam);
          SetCapture(hWnd);
          hdc=GetDC(hWnd);
          SetROP2(hdc,R2_NOTXORPEN);
          switch (nState){
            case 0:
              point[0].x=xPos;  point[0].y=yPos;
              spoint1[next1].x=xPos; spoint1[next1].y=yPos;
              next1++;
              nState=1;
              break;
            case 2:
              MoveToEx(hdc,point[0].x,point[0].y,NULL);
              LineTo(hdc,point[3].x,point[3].y);
              point[1].x=xPos;   point[1].y=yPos;
              point[2].x=xPos;   point[2].y=yPos;
              PolyBezier(hdc,point,4);
              nState=3;
              fErase=TRUE;
              break;
            case 4:
              PolyBezier(hdc,point,4);
              point[2].x=xPos;   point[2].y=yPos;
              PolyBezier(hdc,point,4);
              nState=5;
              fErase=TRUE;
              break;
          }
          ReleaseDC(hWnd,hdc);
          break;
      case WM_RBUTTONDOWN:
          xPos=LOWORD(lParam);   yPos=HIWORD(lParam);
          SetCapture(hWnd);
          hdc=GetDC(hWnd);
          SetROP2(hdc,R2_NOTXORPEN);
          switch (rState){
            case 0:
              point2[0].x=xPos;  point2[0].y=yPos;
              spoint2[next2].x=xPos; spoint2[next2].y=yPos;
              next2=next2+1;
              rState=1;
              break;
            case 2:
              point2[2].x=xPos;   point2[2].y=yPos;
              rState=3;
              MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
              LineTo(hdc,point2[2].x,point2[2].y);
              MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
              LineTo(hdc,point2[2].x,point2[2].y);
              cout<<"point2[0]: "<<point2[0].x<<" "<<point2[0].y<<endl;
              cout<<"point2[1]: "<<point2[1].x<<" "<<point2[1].y<<endl;
              cout<<"point2[2]: "<<point2[2].x<<" "<<point2[2].y<<endl;
              rErase=TRUE;
              break;
          }
          ReleaseDC(hWnd,hdc);
          break;
      case WM_LBUTTONUP:
          xPos=LOWORD(lParam);   yPos=HIWORD(lParam);
          fErase=FALSE;
          switch (nState){
            case 1:
              point[3].x=xPos;   point[3].y=yPos;
              spoint1[next1].x=xPos; spoint1[next1].y=yPos;
              next1++;
              nState=2;
              break;
            case 3:
              point[1].x=xPos;   point[1].y=yPos;
              spoint1[next1].x=xPos; spoint1[next1].y=yPos;
              next1++;
              nState=4;
              break;
            case 5:
              point[2].x=xPos;   point[2].y=yPos;
              spoint1[next1].x=xPos; spoint1[next1].y=yPos;
              next1++;
              nState=0;
              break;
          }
          ReleaseCapture();
          break;
     case WM_RBUTTONUP:
          xPos=LOWORD(lParam);   yPos=HIWORD(lParam);
          rErase=FALSE;
          switch (rState){
            case 1:
              point2[1].x=xPos;   point2[1].y=yPos;
              spoint2[next2].x=xPos; spoint2[next2].y=yPos;
              rState=2;
              next2=next2+1;
              break;
            case 3:
              point[2].x=xPos;   point[2].y=yPos;
              spoint2[next2].x=xPos; spoint2[next2].y=yPos;
              rState=0;
              next2=next2+1;
              break;
          }
          ReleaseCapture();
          break;
        case WM_PAINT: //画图
                if(flag==1)
                {
                    hdc=BeginPaint(hWnd,&PtStr);
                    SetROP2(hdc,R2_NOTXORPEN);
                    diedai=next2/3;
                zhuangtai=next2-diedai*3;
                for(int i=0;i<next2;i++)
                {
                    rpoint2[i].x=spoint2[i].x;
                    rpoint2[i].y=spoint2[i].y;
                }
                for(int i=0;i<next1;i++)
                {
                    rpoint1[i].x=spoint1[i].x;
                    rpoint1[i].y=spoint1[i].y;
                }
                trnext2=next2;
                trnext1=next1;
                for(int i=0;i<diedai;i++)
                {
                    cout<<i<<endl;
                    point2[0].x=spoint2[i*3].x;
                    point2[1].x=spoint2[i*3+1].x;
                    point2[2].x=spoint2[i*3+2].x;
                    point2[0].y=spoint2[i*3].y;
                    point2[1].y=spoint2[i*3+1].y;
                    point2[2].y=spoint2[i*3+2].y;
                     cout<<"point2[0]: "<<point2[0].x<<" "<<point2[0].y<<endl;
                  cout<<"point2[1]: "<<point2[1].x<<" "<<point2[1].y<<endl;
                  cout<<"point2[2]: "<<point2[2].x<<" "<<point2[2].y<<endl;
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                    LineTo(hdc,point2[2].x,point2[2].y);
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[2].x,point2[2].y);
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                    LineTo(hdc,point2[0].x,point2[0].y);
                }
                if(zhuangtai==2)
                {
                    rState=2;
                     point2[0].x=spoint2[next2-2].x;
                    point2[1].x=spoint2[next2-1].x;
                    point2[0].y=spoint2[next2-2].y;
                    point2[1].y=spoint2[next2-1].y;
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[1].x,point2[1].y);
                }
                flag=0;
                diedai=next1/4;
                zhuangtai=next1-diedai*4;
                trnext1=next1;
                cout<<next1<<endl;
                cout<<zhuangtai<<endl;
                for(int i=0;i<diedai;i++)
                {
                    point[0].x=spoint1[i*4].x;
                    point[3].x=spoint1[i*4+1].x;
                    point[1].x=spoint1[i*4+2].x;
                    point[2].x=spoint1[i*4+3].x;
                    point[0].y=spoint1[i*4].y;
                    point[3].y=spoint1[i*4+1].y;
                    point[1].y=spoint1[i*4+2].y;
                    point[2].y=spoint1[i*4+3].y;
                    PolyBezier(hdc,point,4);
                }
                if(zhuangtai==2)
                {
                    //cout<<"yes"<<endl;
                    nState=2;
                    point[0].x=spoint1[next1-2].x;
                    point[3].x=spoint1[next1-1].x;
                    point[0].y=spoint1[next1-2].y;
                    point[3].y=spoint1[next1-1].y;
                    MoveToEx(hdc,point[0].x,point[0].y,NULL);
                    LineTo(hdc,point[3].x,point[3].y);
                }
                if(zhuangtai==3)
                {
                    nState=4;
                    point[0].x=spoint1[next1-3].x;
                    point[3].x=spoint1[next1-2].x;
                    point[1].x=spoint1[next1-1].x;
                    point[2].x=spoint1[next1-1].x;
                    point[0].y=spoint1[next1-3].y;
                    point[3].y=spoint1[next1-2].y;
                    point[1].y=spoint1[next1-1].y;
                    point[2].y=spoint1[next1-1].y;
                    PolyBezier(hdc,point,4);
                }
            }
            if(flag==3)
                {
                    hdc=BeginPaint(hWnd,&PtStr);
                    SetROP2(hdc,R2_NOTXORPEN);
                    next2=trnext2;
                    diedai=next2/3;
                zhuangtai=next2-diedai*3;
                for(int i=0;i<diedai;i++)
                {
                    //cout<<i<<endl;
                    point2[0].x=rpoint2[i*3].x;
                    point2[1].x=rpoint2[i*3+1].x;
                    point2[2].x=rpoint2[i*3+2].x;
                    point2[0].y=rpoint2[i*3].y;
                    point2[1].y=rpoint2[i*3+1].y;
                    point2[2].y=rpoint2[i*3+2].y;
                    // cout<<"point2[0]: "<<point2[0].x<<" "<<point2[0].y<<endl;
                  //cout<<"point2[1]: "<<point2[1].x<<" "<<point2[1].y<<endl;
                  //cout<<"point2[2]: "<<point2[2].x<<" "<<point2[2].y<<endl;
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                    LineTo(hdc,point2[2].x,point2[2].y);
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[2].x,point2[2].y);
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                    LineTo(hdc,point2[0].x,point2[0].y);
                }
                if(zhuangtai==2)
                {

                    rState=2;
                     point2[0].x=rpoint2[next2-2].x;
                    point2[1].x=rpoint2[next2-1].x;
                    point2[0].y=rpoint2[next2-2].y;
                    point2[1].y=rpoint2[next2-1].y;
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[1].x,point2[1].y);
                }
                next1=trnext1;
                diedai=next1/4;
                zhuangtai=next1-diedai*4;
                for(int i=0;i<diedai;i++)
                {
                    point[0].x=rpoint1[i*4].x;
                    point[3].x=rpoint1[i*4+1].x;
                    point[1].x=rpoint1[i*4+2].x;
                    point[2].x=rpoint1[i*4+3].x;
                    point[0].y=rpoint1[i*4].y;
                    point[3].y=rpoint1[i*4+1].y;
                    point[1].y=rpoint1[i*4+2].y;
                    point[2].y=rpoint1[i*4+3].y;
                    PolyBezier(hdc,point,4);
                }
                if(zhuangtai==2)
                {
                    //cout<<"yes"<<endl;
                    nState=2;
                    point[0].x=rpoint1[next1-2].x;
                    point[3].x=rpoint1[next1-1].x;
                    point[0].y=rpoint1[next1-2].y;
                    point[3].y=rpoint1[next1-1].y;
                    MoveToEx(hdc,point[0].x,point[0].y,NULL);
                    LineTo(hdc,point[3].x,point[3].y);
                }
                if(zhuangtai==3)
                {
                    nState=4;
                    point[0].x=rpoint1[next1-3].x;
                    point[3].x=rpoint1[next1-2].x;
                    point[1].x=rpoint1[next1-1].x;
                    point[2].x=rpoint1[next1-1].x;
                    point[0].y=rpoint1[next1-3].y;
                    point[3].y=rpoint1[next1-2].y;
                    point[1].y=rpoint1[next1-1].y;
                    point[2].y=rpoint1[next1-1].y;
                    PolyBezier(hdc,point,4);
                }
                flag=0;
            }
            else
            {
                hdc=BeginPaint(hWnd,&PtStr);
                    SetROP2(hdc,R2_NOTXORPEN);
                    diedai=next2/3;
                zhuangtai=next2-diedai*3;
                for(int i=0;i<diedai;i++)
                {
                    point2[0].x=spoint2[i*3].x;
                    point2[1].x=spoint2[i*3+1].x;
                    point2[2].x=spoint2[i*3+2].x;
                    point2[0].y=spoint2[i*3].y;
                    point2[1].y=spoint2[i*3+1].y;
                    point2[2].y=spoint2[i*3+2].y;
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                    LineTo(hdc,point2[2].x,point2[2].y);
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[2].x,point2[2].y);
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                    LineTo(hdc,point2[0].x,point2[0].y);
                }
                if(zhuangtai==2)
                {
                    rState=2;
                     point2[0].x=spoint2[next2-2].x;
                    point2[1].x=spoint2[next2-1].x;
                    point2[0].y=spoint2[next2-2].y;
                    point2[1].y=spoint2[next2-1].y;
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[1].x,point2[1].y);
                }
                flag=0;
                diedai=next1/4;
                zhuangtai=next1-diedai*4;
                for(int i=0;i<diedai;i++)
                {
                    point[0].x=spoint1[i*4].x;
                    point[3].x=spoint1[i*4+1].x;
                    point[1].x=spoint1[i*4+2].x;
                    point[2].x=spoint1[i*4+3].x;
                    point[0].y=spoint1[i*4].y;
                    point[3].y=spoint1[i*4+1].y;
                    point[1].y=spoint1[i*4+2].y;
                    point[2].y=spoint1[i*4+3].y;
                    PolyBezier(hdc,point,4);
                }
                if(zhuangtai==2)
                {
                    //cout<<"yes"<<endl;
                    nState=2;
                    point[0].x=spoint1[next1-2].x;
                    point[3].x=spoint1[next1-1].x;
                    point[0].y=spoint1[next1-2].y;
                    point[3].y=spoint1[next1-1].y;
                    MoveToEx(hdc,point[0].x,point[0].y,NULL);
                    LineTo(hdc,point[3].x,point[3].y);
                }
                if(zhuangtai==3)
                {
                    nState=4;
                    point[0].x=spoint1[next1-3].x;
                    point[3].x=spoint1[next1-2].x;
                    point[1].x=spoint1[next1-1].x;
                    point[2].x=spoint1[next1-1].x;
                    point[0].y=spoint1[next1-3].y;
                    point[3].y=spoint1[next1-2].y;
                    point[1].y=spoint1[next1-1].y;
                    point[2].y=spoint1[next1-1].y;
                    PolyBezier(hdc,point,4);
                }
            }
            break;
      case WM_MOUSEMOVE:
          xPos=LOWORD(lParam);         yPos=HIWORD(lParam);
          if(wParam&MK_LBUTTON){
              hdc=GetDC(hWnd);
              SetROP2(hdc,R2_NOTXORPEN);
              switch (nState){
                case 1:
                    if(fErase){
                      //  cout<<"fuck"<<endl;
                        MoveToEx(hdc,point[0].x,point[0].y,NULL);
                        LineTo(hdc,point[3].x,point[3].y);
                    }
                    point[3].x=xPos;    point[3].y=yPos;
                    MoveToEx(hdc,point[0].x,point[0].y,NULL);
                    LineTo(hdc,point[3].x,point[3].y);
                  break;
                case 3:
                    if(fErase)  PolyBezier(hdc,point,4);
                    point[1].x=xPos;     point[1].y=yPos;
                    point[2].x=xPos;     point[2].y=yPos;
                    PolyBezier(hdc,point,4);
                    break;
                case 5:
                    if(fErase)  PolyBezier(hdc,point,4);
                    point[2].x=xPos;     point[2].y=yPos;
                    PolyBezier(hdc,point,4);
                    break;
              }
              fErase=TRUE;
              ReleaseDC(hWnd,hdc);
          }
          if(wParam&MK_RBUTTON){
              hdc=GetDC(hWnd);
              SetROP2(hdc,R2_NOTXORPEN);
              switch (rState){
                case 1:
                    if(rErase){
                        MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                        LineTo(hdc,point2[1].x,point2[1].y);
                    }
                    point2[1].x=xPos;    point2[1].y=yPos;
                    MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                    LineTo(hdc,point2[1].x,point2[1].y);
                  break;
                case 3:
                    if(rErase)
                    {
                        MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                        LineTo(hdc,point2[2].x,point2[2].y);
                        MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                        LineTo(hdc,point2[2].x,point2[2].y);
                    }
                    point2[2].x=xPos;     point2[2].y=yPos;
                    MoveToEx(hdc,point2[1].x,point2[1].y,NULL);
                      LineTo(hdc,point2[2].x,point2[2].y);
                      MoveToEx(hdc,point2[0].x,point2[0].y,NULL);
                      LineTo(hdc,point2[2].x,point2[2].y);
                    break;
              }
              rErase=TRUE;
              ReleaseDC(hWnd,hdc);
          }
          break;
      case WM_COMMAND:
          switch (LOWORD(wParam)) {
            case IDM_ABOUT:
                DialogBox(hInst,TEXT("AboutBox"),hWnd,(DLGPROC)DlgAboutProc);
                break;
            case IDM_new:
                InvalidateRect(hWnd,NULL,true);
                nState=0;
                rState=0;
                fErase=FALSE;
                rErase=FALSE;
                next2=0;
                next1=0;
                break;
            case IDM_open:
                hdc=GetDC(hWnd);
                nState=0;
                rState=0;
                fErase=FALSE;
                rErase=FALSE;
                next2=tnext2;
                next1=tnext1;
                flag=1;
                InvalidateRect(hWnd,NULL,true);
                //open先全部失效，然后打开save保存的点，哈哈哈。
                break;
            case IDM_save:
                diedai=next2/3;
                zhuangtai=next2-diedai*3;
                for(int i=0;i<next2;i++)
                {
                    tpoint2[i].x=spoint2[i].x;
                    tpoint2[i].y=spoint2[i].y;
                    tpoint1[i].x=tpoint1[i].x;
                    tpoint1[i].y=tpoint1[i].y;
                }
                tnext2=next2;
                tnext1=next1;
                //我把点给保存下来了，存放到tpoint里面。
                break;
            case IDM_saveas:
                ofn.lpstrTitle = "打开";				//通用对话框标题
                if(GetSaveFileName(&ofn)==TRUE)
                {
                    MessageBox(hWnd,szFile,"文件名",MB_OK);
                }//显示对话框
                  fs2.open(szFile);
                  if(!fs2)
                  {
                      cout<<"no"<<endl;
                  }
                  fs2<<"这个是曲线坐标点的保存"<<endl;
                  for(int i=0;i<next1;i++)
                  {
                    fs2<<spoint1[i].x<<"    "<<spoint1[i].y<<endl;
                  }
                  fs2<<"这个是三角形坐标点的保存"<<endl;
                  for(int i=0;i<next2;i++)
                  {
                    fs2<<spoint2[i].x<<"    "<<spoint2[i].y<<endl;
                  }
                  fs2.close();
                break;
            case IDM_recent:
                flag=3;
                InvalidateRect(hWnd,NULL,true);
                //我把点给保存下来了，存放到tpoint里面。
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return (DefWindowProc(hWnd, message, wParam, lParam));
         }
         break;

      case WM_DESTROY:
         PostQuitMessage(0);
         break;

      default:
         return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return 0;
}

BOOL CALLBACK DlgAboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      case WM_INITDIALOG:
         return TRUE;

      case WM_COMMAND:
         if (LOWORD(wParam)==IDOK) {
             EndDialog(hDlg,TRUE);
             return TRUE;
         }
         break;
   }
   return FALSE;
}



