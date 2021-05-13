# -*- coding: utf8 -*- 
import wx
import os
import cstring
import estring
fflag1=0
fflag2=0
fflag3=0
rflag=1
lflag=1
class SubClassDialog1(wx.Dialog):
    def __init__(self):
        wx.Dialog.__init__(self,None,-1,"模式对话框",size=(300,300))
        self.Button1=wx.CheckBox(self,101,"位图1",pos=(55,55))
        self.Button2=wx.CheckBox(self,102,"位图2",pos=(55,105))
        self.Button3=wx.CheckBox(self,103,"位图3",pos=(55,155))
        okButton=wx.Button(self,wx.ID_OK,"确定",pos=(175,85))
        cancelButton=wx.Button(self,wx.ID_CANCEL,"取消",pos=(175,125))
        self.Bind(wx.EVT_BUTTON,self.OnOK,okButton)
        self.Bind(wx.EVT_BUTTON,self.Cancel,cancelButton)
        if(fflag1==1):
            self.Button1.SetValue(True)
        if(fflag2==1):
            self.Button2.SetValue(True)
        if(fflag3==1):
            self.Button3.SetValue(True)
    def OnOK(self,evt):
        global fflag1,fflag2,fflag3
        if(self.Button1.GetValue()==True):
            fflag1=1
        if(self.Button1.GetValue()==False):
            fflag1=0
        if(self.Button2.GetValue()):
            fflag2=1
        if(self.Button2.GetValue()==False):
            fflag2=0
        if(self.Button3.GetValue()):
            fflag3=1
        if(self.Button3.GetValue()==False):
            fflag3=0
        evt.Skip()
    def Cancel(self,evt):
        evt.Skip()
class SubClassDialog2(wx.Dialog):
    def __init__(self,parent):
        wx.Dialog.__init__(self,parent,-1,"无模式对话框",size=(300,300))
        self.Button1=wx.RadioButton(self,101,"位图1",pos=(55,55))
        self.Button2=wx.RadioButton(self,102,"位图2",pos=(55,105))
        self.Button3=wx.RadioButton(self,103,"位图3",pos=(55,155))
        okButton=wx.Button(self,wx.ID_OK,"确定",pos=(175,85))
        cancelButton=wx.Button(self,wx.ID_CANCEL,"取消",pos=(175,125))
        self.Bind(wx.EVT_BUTTON,self.OnOK,okButton)
        self.Bind(wx.EVT_BUTTON,self.Cancel,cancelButton)
        if(rflag==1):
            self.Button1.SetValue(True)
        if(rflag==2):
            self.Button2.SetValue(True)
        if(rflag==3):
            self.Button3.SetValue(True)
    def OnOK(self,evt):
        global rflag
        if(self.Button1.GetValue()==True):
            rflag=1
        if(self.Button2.GetValue()==True):
            rflag=2
        if(self.Button3.GetValue()==True):
            rflag=3
        self.GetParent().Refresh()
    def Cancel(self,evt):
        evt.Skip()
class MyFrame(wx.Frame):
    def __init__(self):
        if lflag==1:
            wx.Frame.__init__(self,None,-1,u"10185102136 张靖",size=(800,600))
            panel=wx.Panel(self,-1)
            #wx.StaticText(panel,-1,u"进程ID :  模块名:",pos=(0,305))
            icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
            self.SetIcon(icon)
            self.menuBar=wx.MenuBar()
            menu=wx.Menu()
            self.IdCommand=menu.Append(1,cstring.a1)
            self.Bind(wx.EVT_MENU,self.OnCommand,self.IdCommand)
            self.menuBar.Append(menu,cstring.a)
            self.color=wx.Menu()
            self.color.Append(201,cstring.b1,u"")
            self.color.Append(202,cstring.b2,u"")
            self.color.Append(203,cstring.b3,u"")
            self.Bind(wx.EVT_MENU_RANGE,self.OnColor,id=201,id2=203)
            self.menuBar.Append(self.color,cstring.b)
            self.SetBackgroundColour(u"white")
            self.flag1=1
            self.hello1=wx.StaticText(self,-1,"",pos=(100,100))
            control=wx.Menu()
            control.Append(301,cstring.c1,u"",wx.ITEM_RADIO)
            control.Append(302,cstring.c2,u"",wx.ITEM_RADIO)
            control.Append(303,cstring.c3,u"",wx.ITEM_RADIO)
            self.menuBar.Append(control,cstring.c)
            self.Bind(wx.EVT_MENU_RANGE,self.OnControl,id=301,id2=303)
            language=wx.Menu()
            language.Append(401,cstring.d1,u"")
            language.Append(402,cstring.d2,u"")
            self.menuBar.Append(language,cstring.d)
            self.changeable=True
            self.Bind(wx.EVT_MENU_RANGE,self.Language,id=401,id2=402)
            menu=wx.Menu()
            IdAbout=menu.Append(-1,cstring.e1,)
            self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
            self.menuBar.Append(menu,cstring.e)
            self.SetMenuBar(self.menuBar)
            self.Bind(wx.EVT_PAINT, self.OnPaint)
        if lflag==2:
            wx.Frame.__init__(self,None,-1,u"10185102136 张靖",size=(800,600))
            panel=wx.Panel(self,-1)
            #wx.StaticText(panel,-1,u"进程ID :  模块名:",pos=(0,305))
            icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
            self.SetIcon(icon)
            self.menuBar=wx.MenuBar()
            menu=wx.Menu()
            self.IdCommand=menu.Append(-1,cstring.a1)
            self.Bind(wx.EVT_MENU,self.OnCommand,self.IdCommand)
            self.menuBar.Append(menu,estring.a)
            self.color=wx.Menu()
            self.color.Append(201,estring.b1,u"")
            self.color.Append(202,estring.b2,u"")
            self.color.Append(203,estring.b3,u"")
            self.Bind(wx.EVT_MENU_RANGE,self.OnColor,id=201,id2=203)
            self.menuBar.Append(self.color,estring.b)
            self.SetBackgroundColour(u"white")
            self.flag1=1
            self.hello1=wx.StaticText(self,-1,"",pos=(100,100))
            control=wx.Menu()
            control.Append(301,estring.c1,u"",wx.ITEM_RADIO)
            control.Append(302,estring.c2,u"",wx.ITEM_RADIO)
            control.Append(303,estring.c3,u"",wx.ITEM_RADIO)
            self.menuBar.Append(control,estring.c)
            self.Bind(wx.EVT_MENU_RANGE,self.OnControl,id=301,id2=303)
            language=wx.Menu()
            language.Append(401,estring.d1,u"")
            language.Append(402,estring.d2,u"")
            self.menuBar.Append(language,estring.d)
            self.changeable=True
            self.Bind(wx.EVT_MENU_RANGE,self.Language,id=401,id2=402)
            menu=wx.Menu()
            IdAbout=menu.Append(-1,estring.e1,)
            self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
            self.menuBar.Append(menu,estring.e)
            self.SetMenuBar(self.menuBar)
            self.Bind(wx.EVT_PAINT, self.OnPaint)
    def Language(self,evt):
        global lflag
        if evt.GetId()==401:
            lflag=1
            self.menuBar.Remove(4)
            self.menuBar.Remove(3)
            self.menuBar.Remove(2)
            self.menuBar.Remove(1)
            self.menuBar.Remove(0)
            icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
            self.SetIcon(icon)
            self.menuBar=wx.MenuBar()
            menu=wx.Menu()
            self.IdCommand=menu.Append(1,cstring.a1)
            self.Bind(wx.EVT_MENU,self.OnCommand,self.IdCommand)
            self.menuBar.Append(menu,cstring.a)
            self.color=wx.Menu()
            self.color.Append(201,cstring.b1,u"")
            self.color.Append(202,cstring.b2,u"")
            self.color.Append(203,cstring.b3,u"")
            self.Bind(wx.EVT_MENU_RANGE,self.OnColor,id=201,id2=203)
            self.menuBar.Append(self.color,cstring.b)
            self.SetBackgroundColour(u"white")
            self.flag1=1
            self.hello1=wx.StaticText(self,-1,"",pos=(100,100))
            control=wx.Menu()
            control.Append(301,cstring.c1,u"",wx.ITEM_RADIO)
            control.Append(302,cstring.c2,u"",wx.ITEM_RADIO)
            control.Append(303,cstring.c3,u"",wx.ITEM_RADIO)
            self.menuBar.Append(control,cstring.c)
            self.Bind(wx.EVT_MENU_RANGE,self.OnControl,id=301,id2=303)
            language=wx.Menu()
            language.Append(401,cstring.d1,u"")
            language.Append(402,cstring.d2,u"")
            self.menuBar.Append(language,cstring.d)
            self.changeable=True
            self.Bind(wx.EVT_MENU_RANGE,self.Language,id=401,id2=402)
            menu=wx.Menu()
            IdAbout=menu.Append(-1,cstring.e1,)
            self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
            self.menuBar.Append(menu,cstring.e)
            self.SetMenuBar(self.menuBar)
            self.Bind(wx.EVT_PAINT, self.OnPaint)
            self.Refresh()
        if evt.GetId()==402:
            lflag=2
            self.menuBar.Remove(4)
            self.menuBar.Remove(3)
            self.menuBar.Remove(2)
            self.menuBar.Remove(1)
            self.menuBar.Remove(0)
            icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
            self.SetIcon(icon)
            self.menuBar=wx.MenuBar()
            menu=wx.Menu()
            self.IdCommand=menu.Append(-1,cstring.a1)
            self.Bind(wx.EVT_MENU,self.OnCommand,self.IdCommand)
            self.menuBar.Append(menu,estring.a)
            self.color=wx.Menu()
            self.color.Append(201,estring.b1,u"")
            self.color.Append(202,estring.b2,u"")
            self.color.Append(203,estring.b3,u"")
            self.Bind(wx.EVT_MENU_RANGE,self.OnColor,id=201,id2=203)
            self.menuBar.Append(self.color,estring.b)
            self.SetBackgroundColour(u"white")
            self.hello1=wx.StaticText(self,-1,"",pos=(100,100))
            control=wx.Menu()
            control.Append(301,estring.c1,u"",wx.ITEM_RADIO)
            control.Append(302,estring.c2,u"",wx.ITEM_RADIO)
            control.Append(303,estring.c3,u"",wx.ITEM_RADIO)
            self.menuBar.Append(control,estring.c)
            self.Bind(wx.EVT_MENU_RANGE,self.OnControl,id=301,id2=303)
            language=wx.Menu()
            language.Append(401,estring.d1,u"")
            language.Append(402,estring.d2,u"")
            self.menuBar.Append(language,estring.d)
            self.changeable=True
            self.Bind(wx.EVT_MENU_RANGE,self.Language,id=401,id2=402)
            menu=wx.Menu()
            IdAbout=menu.Append(-1,estring.e1,)
            self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
            self.menuBar.Append(menu,estring.e)
            self.SetMenuBar(self.menuBar)
            self.Bind(wx.EVT_PAINT, self.OnPaint)
            self.Refresh()
    def OnPaint(self,event):
        global fflag1,fflag2,fflag3,rflag
        #print(1)
        dc=wx.PaintDC(self)
        if(lflag==1):
            if (self.flag1==1):
                self.hello1.SetLabel(cstring.f1)
            if (self.flag1==2):
                self.hello1.SetLabel(cstring.f2)
            if (self.flag1==3):
                self.hello1.SetLabel(cstring.f3)
            if(fflag1==1):
                image=wx.Image(name="bitmap1.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(200,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(fflag2==1):
                image=wx.Image(name="bitmap2.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(200,300,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(fflag3==1):
                image=wx.Image(name="bitmap3.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(200,400,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(rflag==1):
                image=wx.Image(name="bitmap1.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(300,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(rflag==2):
                image=wx.Image(name="bitmap2.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(300,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(rflag==3):
                image=wx.Image(name="bitmap3.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(300,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
        if(lflag==2):
            if (self.flag1==1):
                self.hello1.SetLabel(estring.f1)
            if (self.flag1==2):
                self.hello1.SetLabel(estring.f2)
            if (self.flag1==3):
                self.hello1.SetLabel(estring.f3)
            if(fflag1==1):
                image=wx.Image(name="bitmap1.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(200,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(fflag2==1):
                image=wx.Image(name="bitmap2.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(200,300,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(fflag3==1):
                image=wx.Image(name="bitmap3.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(200,400,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(rflag==1):
                image=wx.Image(name="bitmap1.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(300,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(rflag==2):
                image=wx.Image(name="bitmap2.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(300,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
            if(rflag==3):
                image=wx.Image(name="bitmap3.bmp",type=wx.BITMAP_TYPE_BMP)
                Bitmap=image.ConvertToBitmap()
                dcMem=wx.MemoryDC()
                dcMem.SelectObject(Bitmap)
                dc.Blit(300,200,image.GetWidth(),image.GetHeight(),dcMem,0,0,wx.COPY)
    def OnCommand(self,evt):
        self.Close()
    def OnColor(self,evt):
        if evt.GetId()==201:
            dialog=SubClassDialog1()
            result=dialog.ShowModal()
            self.Refresh()
        if evt.GetId()==202:
            dialog=SubClassDialog2(self)
            dialog.Show()
            self.Refresh()
        if evt.GetId()==203:
            dialog=wx.FileDialog(None,u"选择文件",os.getcwd(),"","",wx.FD_OPEN)
            if(dialog.ShowModal()==wx.ID_OK):
                text=u"所选文件名:"+dialog.GetPath()
                wx.MessageBox(u"You selected item '%s'" %text,u"Color Menu",wx.YES|wx.ICON_INFORMATION,self)
            dialog.Destroy()
            self.Refresh()
    def OnControl(self,evt):
        if evt.GetId()==301:
            cursor=wx.Cursor(wx.Cursor(wx.CURSOR_ARROW))
            frame.SetCursor(cursor)
            self.flag1=1
            self.Refresh()
        if evt.GetId()==302:
            cursor=wx.Cursor(wx.Cursor(wx.CURSOR_CROSS))
            frame.SetCursor(cursor)
            self.flag1=2
            self.Refresh()
        if evt.GetId()==303:
            cursor=wx.Cursor(cursorName="cursor1.cur",type=wx.BITMAP_TYPE_CUR)
            frame.SetCursor(cursor)
            self.flag1=3
            self.Refresh()
        
    def OnHelp(self,evt):
        wx.MessageBox(u"10185102136 张靖",u"张靖",
        wx.OK|wx.ICON_INFORMATION,self)
    def OnClose(self,evt):
        self.Close()

if __name__=='__main__':
    app=wx.App()
    frame=MyFrame()
    frame.Show(True)
    app.MainLoop()
