import wx 
class MyFrame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self, None, -1, "10185102136 张靖", size=(800, 600))
    self.Bind(wx.EVT_MOTION, self.OnMouseMove)
    #self.Bind(wx.EVT_PAINT, self.OnPaint)
    self.x = self.y = 0
    #self.bt = self.ctrl = False
    self.menuBar=wx.MenuBar()
    menu=wx.Menu()
    self.menuBar.Append(menu,u"Mymenu")
    self.color=wx.Menu()
    self.color.Append(201,u"图标1\tCtrl+X",u"",wx.ITEM_RADIO)
    self.color.Append(202,u"图标2\tCtrl+Y",u"",wx.ITEM_RADIO)
    self.color.Append(203,u"图标3\tCtrl+Z",u"",wx.ITEM_RADIO)
    self.menuBar.Append(self.color,u"file")
    self.edit=wx.Menu()
    self.menuBar.Append(self.edit,u"edit")
    self.menuBar.Check(201,True)
    self.SetBackgroundColour(u"white")
    control=wx.Menu()
    control.Append(301,u"显示1\tCtrl+1",u"",wx.ITEM_CHECK)
    control.Append(302,u"显示2\tCtrl+2",u"",wx.ITEM_CHECK)
    control.Append(303,u"显示3\tCtrl+3",u"",wx.ITEM_CHECK)
    control.Append(304,u"显示4\tCtrl+4",u"",wx.ITEM_CHECK)
    self.menuBar.Append(control,u"background")
    menu=wx.Menu()
    IdAbout=menu.Append(-1,u"程序信息(&I)\tF1",)
    self.Bind(wx.EVT_MENU,self.OnHelp,IdAbout)
    self.menuBar.Append(menu,u"help")
    self.SetMenuBar(self.menuBar)
  def OnMouseMove(self, event):
    self.x,self.y=event.GetPosition()
    dc=wx.ClientDC(self)
    dc.Clear()
    #self.bt = event.LeftIsDown()
   # self.ctrl = wx.GetKeyState(wx.WXK_CONTROL)
    #dc.DrawText("MOUSE:(%04d,%04d) %10s %20s" %
               #   (self.x,self.y, ("CTRL" if self.ctrl else ""),
                 #  "MOUSE_BTN_LEFT" if self.bt else ""),50,60)

  def OnHelp(self,evt):
    wx.MessageBox(u"10185102136 张靖",u"张靖",
    wx.OK|wx.ICON_INFORMATION,self)
    event.Skip()
'''
  def OnPaint(self, event):
    dc=wx.PaintDC(self)
    dc.DrawText("MOUSE:(%04d,%04d) %10s %20s" %
                  (self.x,self.y, ("CTRL" if self.ctrl else ""),
                   "MOUSE_BTN_LEFT" if self.bt else ""),50,60)
'''

if __name__ == '__main__':
  app = wx.App() 
  frame = MyFrame()
  frame.Show(True)
  app.MainLoop()
