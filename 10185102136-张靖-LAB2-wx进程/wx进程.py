# -*- coding: utf8 -*- 

import psutil
import wx
class MyFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self,None,-1,u"10185102136 张靖",size=(800,600))
        icon=wx.Icon(name="icon1.ico",type=wx.BITMAP_TYPE_ICO)
        self.SetIcon(icon)
        panel=wx.Panel(self,-1)
        i=0
        wx.StaticText(panel,-1,u"进程ID :  模块名:",pos=(0,i))
        i=i+20
        ACCESS_DENIED=''
        
        for pid in sorted(psutil.pids()):
          try:
            p = psutil.Process(pid)
            pinfo = p.as_dict(ad_value=ACCESS_DENIED)
            s=str(hex(pid))
            s=s[2:]
            while(len(s)<5):
                s='0'+s
            wx.StaticText(panel,-1,s,pos=(0,i))
            wx.StaticText(panel,-1,pinfo['name'],pos=(50,i))
            print(u"%05x      %s"%(pid,pinfo['name']))
            i=i+20
            
          except psutil.NoSuchProcess: pass
if __name__=='__main__':
    app=wx.App()
    frame=MyFrame()
    frame.Show(True)
    app.MainLoop()
