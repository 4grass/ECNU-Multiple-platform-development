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
        self.IdCommand=menu.Append(-1,u"退出\tCtrl+R","This is the text in statu")
        self.Bind(wx.EVT_MENU,self.OnCommand,self.IdCommand)
        self.menuBar.Append(menu,u"File")
        self.color=wx.Menu()
        self.color.Append(201,u"White",u"",wx.ITEM_RADIO)
        self.color.Append(202,u"Gray",u"",wx.ITEM_RADIO)
        self.color.Append(203,u"Black",u"",wx.ITEM_RADIO)
        self.Bind(wx.EVT_MENU_RANGE,self.OnColor,id=201,id2=203)
        self.menuBar.Append(self.color,u"&Color")
        self.menuBar.Check(202,True)
        self.SetBackgroundColour(u"Gray")
        control=wx.Menu()
        control.Append(301,u"Eable",u"Enable/Disable BG change",wx.ITEM_CHECK)
        self.menuBar.Append(control,u"Con&trol")
        self.Bind(wx.EVT_MENU,self.OnControl,id=301)
        self.menuBar.Check(301,True)
        self.changeable=True
        menu=wx.Menu()
        IdAbout=menu.Append(-1,u"&About\tF1",u"Help tip")
        self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
        self.menuBar.Append(menu,u"&Help")
        self.SetMenuBar(self.menuBar)
        self.CreateStatusBar()
        self.Bind(wx.EVT_PAINT,self.OnPaint)
    def OnPaint(self,evt):
        dc=wx.PaintDC(self)
        evt.Skip()
    def OnCommand(self,evt):
        wx.MessageBox(u"Sorry,运行命令 not implemented yet!",
            "Message",
                wx.OK|wx.ICON_EXCLAMATION,self)
    def OnColor(self,evt):
        item=self.GetMenuBar().FindItemById(evt.GetId())
        text=item.GetItemLabel()
        wx.MessageBox(u"You selected item '%s'" %text,u"Color Menu",wx.OK|wx.ICON_INFORMATION,self)
        if self.changeable:
            self.SetBackgroundColour(text)
            self.Refresh()
        else:
            print(1)
            dc=wx.ClientDC(self)
            dc.SetTextForeground(u'red')
            dc.DrawText(u"不能改变BG!",100,50)
    def OnControl(self,evt):
        self.changeable=evt.IsChecked()
        self.GetMenuBar().Enable(self.IdCommand.GetId(),self.changeable)
    def OnHelp(self,evt):
        wx.MessageBox(u"This is a wxPython program for Menu Demo",u"About Menu",
        wx.OK|wx.ICON_INFORMATION,self)
    def OnClose(self,evt):
        self.Close()
            
if __name__=='__main__':
    app=wx.App()
    frame=MyFrame()
    frame.Show(True)
    app.MainLoop()
