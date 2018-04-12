#ifndef _SCENE_H
#define _SCENE_H

#include<vector>

class Scene
{
public:
	Scene();
	Scene(int len, int wid);
	~Scene();

	void SetObstacle(int index);//�����ϰ�
	bool IsObstacle(int index);//�Ƿ�Ϊ�ϰ�
	int ConnectType(int index1, int index2);//�ж�������������������

	void FindRoad(); //Ѱ�������һ������·��

	int LastIndex() { return length * width - 1; }
	int Length() { return length; }
	int Width() { return width; }
	enum CnctType { NotConnect, Neighbor, Bias };
private:
	int length; //��
	int width; //��
	int last;  //����λ��
	std::vector<bool> array;
};


#endif
