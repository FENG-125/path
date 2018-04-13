#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include<windows.h>


class Interface
{
public:
	//初始化环境中障碍的内容
	void InitBlock();
	//初始化位图
	void InitBitmap();
	//初始化矩形数据(内部初始化了各个矩形中心的坐标，以便绘制直线)
	void InitRect();
	//拓展化操作,使得不正规的障碍拓展为方形障碍
	void ExtendIndex();

private:
	HWND   hWnd;		//当前窗体的句柄
	HDC	   hdc;			//窗体的DC
	HDC    mdc;			//与窗体兼容的DC
	HDC	   bufDC;		//缓冲DC

	HINSTANCE hInst;                     //当前实例
	TCHAR szTitle[100];		 // 标题栏文字
	TCHAR szWindowClass[100]; // 标题栏文字

							  //绘图资源
	HBITMAP	bgBitmap;			//背景位图
	HBITMAP	blockBitmap[2];		//障碍位图1
	HBITMAP	selectBitmap;		//选择位图
	HPEN	pPath = CreatePen(PS_SOLID, 3, RGB(35, 170, 100));
	//创建绘制最佳路径的画笔
};

#endif // !_INTERFACE_H_

