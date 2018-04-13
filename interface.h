#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include<windows.h>


class Interface
{
public:
	//��ʼ���������ϰ�������
	void InitBlock();
	//��ʼ��λͼ
	void InitBitmap();
	//��ʼ����������(�ڲ���ʼ���˸����������ĵ����꣬�Ա����ֱ��)
	void InitRect();
	//��չ������,ʹ�ò�������ϰ���չΪ�����ϰ�
	void ExtendIndex();

private:
	HWND   hWnd;		//��ǰ����ľ��
	HDC	   hdc;			//�����DC
	HDC    mdc;			//�봰����ݵ�DC
	HDC	   bufDC;		//����DC

	HINSTANCE hInst;                     //��ǰʵ��
	TCHAR szTitle[100];		 // ����������
	TCHAR szWindowClass[100]; // ����������

							  //��ͼ��Դ
	HBITMAP	bgBitmap;			//����λͼ
	HBITMAP	blockBitmap[2];		//�ϰ�λͼ1
	HBITMAP	selectBitmap;		//ѡ��λͼ
	HPEN	pPath = CreatePen(PS_SOLID, 3, RGB(35, 170, 100));
	//�����������·���Ļ���
};

#endif // !_INTERFACE_H_

