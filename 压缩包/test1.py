#coding:utf8

import wx

class Example(wx.Frame):

    def __init__(self, *args, **kwargs):

        super(Example, self).__init__(*args, **kwargs) 

        self.InitUI()

    def InitUI(self):    

        caidanlan = wx.MenuBar()#创建菜单栏

        caidan = wx.Menu() #创建一个菜单

        xuanxiang = wx.MenuItem(caidan,1,u'&退出')#一个选项

        xuanxiang.SetBitmap(wx.Bitmap('exit.jpg'))#添加一个图标

        caidan.AppendItem(xuanxiang)#将选项添加到菜单中

###############新加内容#############

        imp=wx.Menu()#创建一个菜单

        imp.Append(wx.ID_ANY,'text')#向菜单添加选项

        imp.Append(wx.ID_ANY,'excel')#向菜单添加选项

        caidan.AppendMenu(wx.ID_ANY,u'引用',imp)#将菜单imp添加到菜单caidan

####################################

        self.Bind(wx.EVT_MENU, self.OnQuit, id=1)#选项与动作绑定，这样点击该选项就会执行退出动作

        caidanlan.Append(caidan, u'&下拉菜单') #将创建好的菜单添加到菜单栏

        self.SetMenuBar(caidanlan) #将菜单栏添加到窗口Frame

        self.SetSize((300, 200))

        self.SetTitle(u'菜单')

        self.Centre()

        self.Show(True)

    def OnQuit(self, e):

        self.Close()

def main():

    ex = wx.App()

    Example(None)

    ex.MainLoop()    

if __name__ == '__main__':

    main()
