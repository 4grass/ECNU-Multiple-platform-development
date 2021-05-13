# -*- coding: utf8 -*- 
import wx
class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None,-1,u"10185102136 张靖",size=(800,600))
        panel=wx.Panel(self,-1)
        #wx.StaticText(panel,-1,u"进程ID :  模块名:",pos=(0,305))
        icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
        self.SetIcon(icon)
        self.menuBar=wx.MenuBar()
        menu=wx.Menu()
        self.IdCommand=menu.Append(-1,u"退出\tCtrl+Shift+Delete")
        self.Bind(wx.EVT_MENU,self.OnCommand,self.IdCommand)
        self.menuBar.Append(menu,u"File")
        self.color=wx.Menu()
        self.color.Append(201,u"图标1\tCtrl+X",u"",wx.ITEM_RADIO)
        self.color.Append(202,u"图标2\tCtrl+Y",u"",wx.ITEM_RADIO)
        self.color.Append(203,u"图标3\tCtrl+Z",u"",wx.ITEM_RADIO)
        self.Bind(wx.EVT_MENU_RANGE,self.OnColor,id=201,id2=203)
        self.menuBar.Append(self.color,u"&图标(&I)")
        self.menuBar.Check(201,True)
        self.SetBackgroundColour(u"Gray")
        self.flag1=0
        self.flag2=0
        self.flag3=0
        self.flag4=0
        self.tag=201
        self.hello1=wx.StaticText(self,-1,"",pos=(200,200))
        self.hello2=wx.StaticText(self,-1,"",pos=(200,300))
        self.hello3=wx.StaticText(self,-1,"",pos=(300,200))
        self.hello4=wx.StaticText(self,-1,"",pos=(300,300))
        self.hello5=wx.StaticText(self,-1,"",pos=(100,100))
        self.hello5.SetLabel(u"当前用位图1")
        control=wx.Menu()
        control.Append(301,u"显示1\tCtrl+1",u"",wx.ITEM_CHECK)
        control.Append(302,u"显示2\tCtrl+2",u"",wx.ITEM_CHECK)
        control.Append(303,u"显示3\tCtrl+3",u"",wx.ITEM_CHECK)
        control.Append(304,u"显示4\tCtrl+4",u"",wx.ITEM_CHECK)
        self.menuBar.Append(control,u"显示(&D)")
        self.Bind(wx.EVT_MENU_RANGE,self.OnControl,id=301,id2=304)
        self.changeable=True
        menu=wx.Menu()
        IdAbout=menu.Append(-1,u"程序信息(&I)\tF1",)
        self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
        self.menuBar.Append(menu,u"关于(&A)")
        self.SetMenuBar(self.menuBar)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
    def OnPaint(self,event):
        #print(1) 
        if (self.flag1==1):
            self.hello1.SetLabel(u"显示信息1")
        if (self.flag1==0):
            self.hello1.Destroy()
            self.hello1=wx.StaticText(self,-1,u"",pos=(200,200))
        if (self.flag2==1):
            self.hello2.SetLabel(u"显示信息2")
        if (self.flag2==0):
            self.hello2.Destroy()
            self.hello2=wx.StaticText(self,-1,u"",pos=(200,300))
        if (self.flag3==1):
            self.hello3.SetLabel(u"显示信息3")
        if (self.flag3==0):
            self.hello3.Destroy()
            self.hello3=wx.StaticText(self,-1,u"",pos=(300,200))
        if (self.flag4==1):
            self.hello4.SetLabel(u"显示信息4")
        if (self.flag4==0):
            self.hello4.Destroy()
            self.hello4=wx.StaticText(self,-1,u"",pos=(300,300))
    def OnCommand(self,evt):
        self.Close()
    def OnColor(self,evt):
        item=self.GetMenuBar().FindItemById(evt.GetId())
        text=item.GetItemLabel()
        if(wx.MessageBox(u"You selected item '%s'" %text,u"Color Menu",wx.YES_NO,self)==wx.YES):
            if self.changeable:
                self.tag=evt.GetId()
                if(self.tag==201):
                    icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
                    self.SetIcon(icon)
                    self.menuBar.EnableTop(2,True)
                    self.hello5.SetLabel(u"当前用位图1")
                if(self.tag==202):
                    icon=wx.Icon(name="icon2.ico",type=wx.BITMAP_TYPE_ICO)
                    self.SetIcon(icon)
                    self.menuBar.EnableTop(2,True)
                    self.hello5.SetLabel(u"当前用位图2")
                if(self.tag==203):
                    icon=wx.Icon(name="icon3.ico",type=wx.BITMAP_TYPE_ICO)
                    self.SetIcon(icon)
                    self.menuBar.EnableTop(2,False)
                    self.hello5.SetLabel(u"当前用位图3")
        else:
            self.menuBar.Check(self.tag,True)
    def OnControl(self,evt):
        if evt.GetId()==301:
            self.flag1=1-self.flag1
        if evt.GetId()==302:
            self.flag2=1-self.flag2
        if evt.GetId()==303:
            self.flag3=1-self.flag3
        if evt.GetId()==304:
            self.flag4=1-self.flag4
        self.Refresh()
        '''
        if (self.flag1==1):
            hello=wx.StaticText(self,-1,u"显示信息1",pos=(200,200))
        if (self.flag2==1):
            wx.StaticText(self,-1,u"显示信息2",pos=(300,200))
        if (self.flag3==1):
            wx.StaticText(self,-1,u"显示信息3",pos=(200,300))
        if (self.flag4==1):
            wx.StaticText(self,-1,u"显示信息4",pos=(300,300))
        '''
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
