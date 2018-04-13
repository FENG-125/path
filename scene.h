#ifndef _SCENE_H
#define _SCENE_H

#include<vector>
#include<ctime>
#include<windows.h>
class Scene
{
public:
	Scene();
	Scene(int len, int wid);
	~Scene();

	void SetObstacle(int index);//�����ϰ�
	bool IsObstacle(int index);//�Ƿ�Ϊ�ϰ�
	int ConnectType(int index1, int index2);//�ж�������������������
	
	//Ѱ�������һ������·��,��second��first
	bool FindRoad(int first, int &second, int &ForbidFlag);

	int LastIndex() { return length * width - 1; }
	int Length() { return length; }
	int Width() { return width; }

	enum CnctType { NotConnect, Neighbor, Bias };//��������
	enum Position //���λ��
	{
		UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT
	};

	int NextIndex(int index);//������һ���±�
	bool Left(int &index,int &flag);//�ж��ܷ����� flag -1 FindRoad  -2 NextIndex
	bool Right(int &index, int &flag);
	bool Upper(int &index, int &flag);
	bool Down(int &index, int &flag);
	int ComparePos(int left, int right);//ȷ���ұ�Ԫ�������Ԫ�ص����λ��
private:
	int length; //��
	int width; //��
	int last;  //����λ��
	std::vector<bool> array;
};


#endif
