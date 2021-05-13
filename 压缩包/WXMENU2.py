#_*_coding:utf-8_*_ 
 
import wx 
class MyFrame(wx.Frame):
  def __init__(self):
    wx.Frame.__init__(self, None, -1, u"My Frame", size=(800, 500))
    # Create the menubar
    self.menuBar = wx.MenuBar()

    # add a menu 
    menu = wx.Menu()

    # add an item to the menu, using \tKeyName automatically
    # creates an accelerator, the third param is some help text
    # that will show up in the statusbar
#    self.IdCommand = wx.NewId()
#    menu.Append(self.IdCommand, u"命令(&R)\tCtrl+R", "This the text in the Statusbar")
    # bind the menu event to an event handler
#    self.Bind(wx.EVT_MENU, self.OnCommand, id=self.IdCommand)
    
    self.IdCommand=menu.Append(-1, u"命令(&R)\tCtrl+R", "This the text in the Statusbar")
    self.Bind(wx.EVT_MENU, self.OnCommand, self.IdCommand)

    menu.AppendSeparator()

    menu.Append(wx.ID_EXIT, u"E&xit\tAlt-X", u"Exit this simple sample")
    # bind the menu event to an event handler
    self.Bind(wx.EVT_MENU, self.OnClose, id=wx.ID_EXIT)

    # and put the menu on the menubar
    self.menuBar.Append(menu, u"&File")

    self.color = wx.Menu()
    # Radio items
    self.color.Append(201, u"White", u"", wx.ITEM_RADIO)
    self.color.Append(202, u"Gray", u"", wx.ITEM_RADIO)
    self.color.Append(203, u"Black", u"", wx.ITEM_RADIO)
#    self.Bind(wx.EVT_MENU, self.OnColor,id=201)
#    self.Bind(wx.EVT_MENU, self.OnColor,id=202)
#    self.Bind(wx.EVT_MENU, self.OnColor,id=203)
    self.Bind(wx.EVT_MENU_RANGE, self.OnColor,id=201,id2=203)

    self.menuBar.Append(self.color, u"&Color")
    self.menuBar.Check(202,True)	
    self.SetBackgroundColour(u"Gray")

    control = wx.Menu()
    # Check items
    control.Append(301, u"Enable", u"Enable/Disable BG change", wx.ITEM_CHECK)
    self.menuBar.Append(control, u"Con&trol")
    self.Bind(wx.EVT_MENU, self.OnControl,id=301)
    self.menuBar.Check(301,True)	
    self.changeable = True

    # and another menu 
    menu = wx.Menu()

    IdAbout = menu.Append(-1, u"&About\tF1", u"Help tip")

    # bind the menu event to an event handler
    self.Bind(wx.EVT_MENU, self.OnHelp, IdAbout)

    # and put the menu on the menubar
    self.menuBar.Append(menu, u"&Help")
    self.SetMenuBar(self.menuBar)
	
    self.CreateStatusBar()
    self.Bind(wx.EVT_PAINT, self.OnPaint)

  def OnPaint(self, evt):
    dc=wx.PaintDC(self)
    # draw something in client area
    evt.Skip()

  def OnCommand(self, evt):
    wx.MessageBox(u"Sorry,运行命令 not implemented yet！",
           "Message", 
		   wx.OK | wx.ICON_EXCLAMATION, self)

  def OnColor(self, evt):
    item = self.GetMenuBar().FindItemById(evt.GetId())
#    text = item.GetText()
    text = item.GetItemLabel()
    wx.MessageBox(u"You selected item '%s'" % text,
           u"Color Menu", wx.OK | wx.ICON_INFORMATION, self)
    if self.changeable:
      self.SetBackgroundColour(text)
      self.Refresh()
    else:
      dc=wx.ClientDC(self)
      dc.SetTextForeground(u'red')
      dc.DrawText(u"不能改变BG!",100,50)
	 
  def OnControl(self, evt):
    self.changeable = evt.IsChecked()
#    self.GetMenuBar().Enable(self.IdCommand, self.changeable)
    self.GetMenuBar().Enable(self.IdCommand.GetId(), self.changeable)

  def OnHelp(self, evt):
    wx.MessageBox(u"This is a wxPython program for Menu Demo",
           u"About Menu", wx.OK | wx.ICON_INFORMATION, self)
	
  def OnClose(self, evt):
    self.Close()

if __name__ == u'__main__':
  app = wx.App()
  frame = MyFrame()
  frame.Show(True)
  app.MainLoop()
