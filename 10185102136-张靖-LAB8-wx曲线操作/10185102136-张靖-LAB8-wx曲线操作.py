# -*- coding: utf8 -*- 
import wx  
import os
class MyFrame(wx.Frame):
  def __init__(self):
    self.flag=0
    self.nstate=0
    self.fErase=0
    self.rErase=0
    self.rstate=0
    self.trnext1=0
    self.trnext2=0
    wx.Frame.__init__(self, None, -1, u"10185102136 张靖", size=(800, 600))
    self.Bind(wx.EVT_PAINT, self.OnPaint)
    #self.Bind(wx.EVT_SIZE, self.OnSize)
    self.Bind(wx.EVT_MOTION, self.OnMouseMove)
    self.Bind(wx.EVT_LEFT_DOWN,self.OnLBUTTONDOWN)
    self.Bind(wx.EVT_LEFT_UP,self.OnLBUTTONUP)
    self.Bind(wx.EVT_RIGHT_DOWN,self.OnRBUTTONDOWN)
    self.Bind(wx.EVT_RIGHT_UP,self.OnRBUTTONUP)
    self.ps = [-1,-1,-1,-1]
    self.ps2= [-1,-1,-1]
    self.spoint1=[-1 for i in range(10000)]
    self.spoint2=[-1 for i in range(10000)]
    self.tpoint1=[-1 for i in range(10000)]
    self.tpoint2=[-1 for i in range(10000)]
    self.rpoint1=[-1 for i in range(10000)]
    self.rpoint2=[-1 for i in range(10000)]
    self.tnext1=0
    self.tnext2=0
    self.next1=0
    self.next2=0
    self.menuBar=wx.MenuBar()
    menu=wx.Menu()
    self.IdCommand1=menu.Append(101,"exit")
    self.Bind(wx.EVT_MENU,self.OnClose,self.IdCommand1)
    self.IdCommand2=menu.Append(102,"new")
    self.Bind(wx.EVT_MENU,self.new,self.IdCommand2)
    self.IdCommand3=menu.Append(103,"save")
    self.Bind(wx.EVT_MENU,self.save,self.IdCommand3)
    self.IdCommand4=menu.Append(104,"open")
    self.Bind(wx.EVT_MENU,self.open,self.IdCommand4)
    self.IdCommand5=menu.Append(105,"recent")
    self.Bind(wx.EVT_MENU,self.recent,self.IdCommand5)
    self.IdCommand6=menu.Append(106,"saveas")
    self.Bind(wx.EVT_MENU,self.saveas,self.IdCommand6)
    self.IdCommand7=menu.Append(107,"help")
    self.Bind(wx.EVT_MENU,self.OnHelp,self.IdCommand7)
    self.menuBar.Append(menu,u"file")
    self.SetMenuBar(self.menuBar)
  def OnLBUTTONDOWN(self, event):
    dc=wx.ClientDC(self)
    dc.SetPen(wx.Pen("black", 5))
    p = event.GetPosition()
    dc.SetLogicalFunction(wx.INVERT)
    if(self.nstate==0):
      self.ps[0]=p
      self.nstate=1
      self.spoint1[self.next1]=p
      self.next1=self.next1+1
    if(self.nstate==2):
      dc.DrawLine(self.ps[0].x,self.ps[0].y,self.ps[3].x,self.ps[3].y)
      self.ps[1]=p
      self.ps[2]=p
      self.fErase=1
      self.nstate=3
      dc.DrawSpline(self.ps)
    if(self.nstate==4):
      dc.DrawSpline(self.ps)
      self.ps[2]=p
      dc.DrawSpline(self.ps)
      self.nstate=5
      self.fErase=1
  def OnRBUTTONDOWN(self, event):
    dc=wx.ClientDC(self)
    dc.SetPen(wx.Pen("black", 5))
    p = event.GetPosition()
    dc.SetLogicalFunction(wx.INVERT)
    if(self.rstate==0):
      self.ps2[0]=p
      self.rstate=1
      self.spoint2[self.next2]=p
      self.next2=self.next2+1
    if(self.rstate==2):
      self.ps2[2]=p
      self.rstate=3
      dc.DrawLine(self.ps2[1].x,self.ps2[1].y,self.ps2[2].x,self.ps2[2].y)
      dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[2].x,self.ps2[2].y)
      self.rErase=1
  def OnLBUTTONUP(self, event):
    dc=wx.ClientDC(self)
    dc.SetPen(wx.Pen("black", 5))
    p = event.GetPosition()
    dc.SetLogicalFunction(wx.INVERT)
    self.fErase=0
    if(self.nstate==1):
      self.ps[3]=p
      self.nstate=2
      self.spoint1[self.next1]=p
      self.next1=self.next1+1
    if(self.nstate==3):
      self.ps[1]=p
      self.nstate=4
      self.spoint1[self.next1]=p
      self.next1=self.next1+1
    if(self.nstate==5):
      self.ps[2]=p
      self.nstate=0
      self.spoint1[self.next1]=p
      self.next1=self.next1+1
  def OnRBUTTONUP(self, event):
    dc=wx.ClientDC(self)
    dc.SetPen(wx.Pen("black", 5))
    p = event.GetPosition()
    dc.SetLogicalFunction(wx.INVERT)
    self.rErase=0
    if(self.rstate==1):
      self.ps2[1]=p
      self.rstate=2
      self.spoint2[self.next2]=p
      self.next2=self.next2+1
    if(self.rstate==3):
      self.ps2[2]=p
      self.rstate=0
      self.spoint2[self.next2]=p
      self.next2=self.next2+1
  def OnMouseMove(self, event):
    p = event.GetPosition()
    dc=wx.ClientDC(self)
    dc.SetPen(wx.Pen("black", 5))
    dc.SetLogicalFunction(wx.INVERT)
    if (event.LeftIsDown() and self.nstate==1):
      if(self.fErase==1):
        dc.DrawLine(self.ps[0].x,self.ps[0].y,self.ps[3].x,self.ps[3].y)
      self.ps[3]=p
      dc.DrawLine(self.ps[0].x,self.ps[0].y,self.ps[3].x,self.ps[3].y)
      self.fErase=1
    if (event.LeftIsDown() and self.nstate==3):
      if(self.fErase==1):
        dc.DrawSpline(self.ps)
      self.ps[1]=p
      self.ps[2]=p
      dc.DrawSpline(self.ps)
      self.fErase=1
    if (event.LeftIsDown() and self.nstate==5):
      if(self.fErase==1):
        dc.DrawSpline(self.ps)
      self.ps[2]=p
      dc.DrawSpline(self.ps)
      self.fErase=1
    if(event.RightIsDown() and self.rstate==1):
      if(self.rErase):
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[1].x,self.ps2[1].y)
      self.ps2[1]=p
      dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[1].x,self.ps2[1].y)
      self.rErase=1
    if(event.RightIsDown() and self.rstate==3):
      if(self.rErase):
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[2].x,self.ps2[2].y)
        dc.DrawLine(self.ps2[1].x,self.ps2[1].y,self.ps2[2].x,self.ps2[2].y)
      self.ps2[2]=p
      dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[2].x,self.ps2[2].y)
      dc.DrawLine(self.ps2[1].x,self.ps2[1].y,self.ps2[2].x,self.ps2[2].y)
      self.rErase=1
  def OnHelp(self,evt):
    print(1)
    wx.MessageBox(u"10185102136 张靖",u"左键曲线，右键三角形",
    wx.OK|wx.ICON_INFORMATION,self)
  def new(self,evt):
    self.nstate=0
    self.rstate=0
    self.fErase=0
    self.rErase=0
    self.next1=0
    self.next2=0
    self.Refresh()
  def save(self,evt):
    self.tnext2=self.next2
    self.tnext1=self.next1
    for i in range(0,self.next1):
      self.tpoint1[i]=self.spoint1[i]
    for i in range(0,self.next2):
      self.tpoint2[i]=self.spoint2[i]
  def open(self,evt):
    self.nstate=0
    self.rstate=0
    self.fErase=0
    self.rErase=0
    self.next1=self.tnext1
    self.next2=self.tnext2
    self.flag=1
    self.Refresh()
  def recent(self,evt):
    self.nstate=0
    self.rstate=0
    self.fErase=0
    self.rErase=0
    self.flag=3
    self.next1=self.trnext1
    self.next2=self.trnext2
    self.Refresh()
  def OnClose(self,evt):
    self.Close()
  def saveas(self,evt):
    dialog=wx.FileDialog(None,u"选择文件",os.getcwd(),"","",wx.FD_SAVE)
    if(dialog.ShowModal()==wx.ID_OK):
        filename=dialog.GetPath()
        text=u"所选文件名:"+dialog.GetPath()
        wx.MessageBox(u"You selected item '%s'" %text,u"Color Menu",wx.YES_NO|wx.ICON_INFORMATION,self)
        dialog.Destroy()
        with open(filename, 'w') as file_object:
          print(1)
          file_object.write("曲线坐标\n")
          for i in range(0,self.next1):
            file_object.write(str(self.spoint1[i].x))
            file_object.write("\t")
            file_object.write(str(self.spoint1[i].y))
            file_object.write("\n")
          file_object.write("三角形坐标\n")
          for i in range(0,self.next2):
            file_object.write(str(self.spoint2[i].x))
            file_object.write("\t")
            file_object.write(str(self.spoint2[i].y))
            file_object.write("\n")

  def OnPaint(self, event):
    dc = wx.PaintDC(self)
    dc.SetPen(wx.Pen("black", 5))
    dc.SetLogicalFunction(wx.INVERT)
    if(self.flag==1):
      diedai=self.next2//3
      zhuangtai=self.next2-diedai*3
      self.trnext1=self.next1
      self.trnext2=self.next2
      for i in range(0,self.next2):
        self.rpoint2[i]=self.tpoint2[i]
      for i in range(0,self.next1):
        self.rpoint1[i]=self.tpoint1[i]
      for i in range(0,diedai):
        self.ps2[0]=self.tpoint2[i*3]
        self.ps2[1]=self.tpoint2[i*3+1]
        self.ps2[2]=self.tpoint2[i*3+2]
        dc.DrawLine(self.ps2[1].x,self.ps2[1].y,self.ps2[2].x,self.ps2[2].y)
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[2].x,self.ps2[2].y)
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[1].x,self.ps2[1].y)
      if(zhuangtai==2):
        self.rstate=2
        self.ps2[0]=self.tpoint2[self.next2-2]
        self.ps2[1]=self.tpoint2[self.next2-1]
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[1].x,self.ps2[1].y)
      self.flag=0
      diedai=self.next1//4
      zhuangtai=self.next1-diedai*4
      for i in range(0,diedai):
        self.ps[0]=self.tpoint1[i*4]
        self.ps[3]=self.tpoint1[i*4+1]
        self.ps[1]=self.tpoint1[i*4+2]
        self.ps[2]=self.tpoint1[i*4+3]
        dc.DrawSpline(self.ps)
      if(zhuangtai==2):
        self.nstate=2
        self.ps[0]=self.tpoint1[self.next1-2]
        self.ps[3]=self.tpoint1[self.next1-1]
        dc.DrawLine(self.ps[0].x,self.ps[0].y,self.ps[3].x,self.ps[3].y)
      if(zhuangtai==3):
        self.nstate=4
        self.ps[0]=self.tpoint1[self.next1-3]
        self.ps[3]=self.tpoint1[self.next1-2]
        self.ps[1]=self.tpoint1[self.next1-1]
        self.ps[2]=self.tpoint1[self.next1-1]
        dc.DrawSpline(self.ps)
    if(self.flag==3):
      diedai=self.next2//3
      zhuangtai=self.next2-diedai*3
      for i in range(0,diedai):
        self.ps2[0]=self.rpoint2[i*3]
        self.ps2[1]=self.rpoint2[i*3+1]
        self.ps2[2]=self.rpoint2[i*3+2]
        dc.DrawLine(self.ps2[1].x,self.ps2[1].y,self.ps2[2].x,self.ps2[2].y)
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[2].x,self.ps2[2].y)
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[1].x,self.ps2[1].y)
      if(zhuangtai==2):
        self.rstate=2
        self.ps2[0]=self.rpoint2[self.next2-2]
        self.ps2[1]=self.rpoint2[self.next2-1]
        dc.DrawLine(self.ps2[0].x,self.ps2[0].y,self.ps2[1].x,self.ps2[1].y)
      self.flag=0
      diedai=self.next1//4
      zhuangtai=self.next1-diedai*4
      for i in range(0,diedai):
        self.ps[0]=self.rpoint1[i*4]
        self.ps[3]=self.rpoint1[i*4+1]
        self.ps[1]=self.rpoint1[i*4+2]
        self.ps[2]=self.rpoint1[i*4+3]
        dc.DrawSpline(self.ps)
      if(zhuangtai==2):
        self.nstate=2
        self.ps[0]=self.rpoint1[self.next1-2]
        self.ps[3]=self.rpoint1[self.next1-1]
        dc.DrawLine(self.ps[0].x,self.ps[0].y,self.ps[3].x,self.ps[3].y)
      if(zhuangtai==3):
        self.nstate=4
        self.ps[0]=self.rpoint1[self.next1-3]
        self.ps[3]=self.rpoint1[self.next1-2]
        self.ps[1]=self.rpoint1[self.next1-1]
        self.ps[2]=self.rpoint1[self.next1-1]
        dc.DrawSpline(self.ps)
if __name__ == '__main__':
  app = wx.App()
  frame = MyFrame()
  frame.Show(True)
  app.MainLoop()


