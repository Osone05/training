from tkinter import *
#from tkinter import ttk

class imageClass():
    def __init__(self):
        self.canvasList = []
        self.imgList = []
        self.pX = -1
        self.pY = -1
    def canvas(self,_x,_y,w,h):
        self.drawCanvas = Canvas(bg="white", width=w, height=h)
        self.drawCanvas.place(x=_x, y=_y)
        self.drawCanvas.create_line(w,0,w,h,fill="black")
        self.canvasWidth = w
        self.canvasHeight = h
        self.btn = Button(text='リセット', command = self.canvasReset)
        self.btn.place(x=w+10, y=50)
    def image(self,_img,_x,_y,w,h):
        self.imgList.append(PhotoImage(file=_img))
        #index = len(self.imgList)
        self.canvasList.append(Canvas(bg="black", width=w, height=h))
        index = len(self.canvasList)-1
        self.canvasList[index].place(x=_x, y=_y)
        self.canvasList[index].create_image(0, 0, image=self.imgList[index], anchor=NW)
    def canvasReset(self):
        self.drawCanvas.delete("all")
        self.drawCanvas.create_line(self.canvasWidth,0,self.canvasWidth,self.canvasHeight,fill="black")
    def eventChecker(self):
        #for i in range(len(self.canvasList)):
            #canvas = self.canvasList[i]
            #canvas.bind('<ButtonPress-1>', self.mousePressed)
        self.drawCanvas.bind('<B1-Motion>',self.mouseDragged)
    def mouseDragged(self,event):
         if self.isInsideCanvas(self.pX,self.pY) and self.isInsideCanvas(event.x,event.y):
            self.drawCanvas.create_line(self.pX,self.pY,event.x,event.y)
            self.pX = event.x
            self.pY = event.y
         else :
             self.pX = event.x
             self.pY = event.y
    def isInsideCanvas(self,x,y):
        if x<0 or x>self.canvasWidth or y<0 or y>self.canvasHeight:
            return False
        return True
    
        


root = Tk()
root.title('マウスドラッグで描画')
#Windowサイズの指定__________________________________________________
width = 400
height = 200
x = (root.winfo_screenwidth() - width) // 2
y = (root.winfo_screenheight() - height) // 2
geometory = f'{width}x{height}+{x}+{y}'  
root.geometry(geometory)
#キャンバスの作成________________________________________________________
imgClass = imageClass()
imgClass.canvas(0,0,width*0.8,height)
imgClass.eventChecker()
#________________________________________________________________________
root.mainloop()