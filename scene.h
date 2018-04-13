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

	void SetObstacle(int index);//设置障碍
	bool IsObstacle(int index);//是否为障碍
	int ConnectType(int index1, int index2);//判断两个坐标点的连接类型
	
	//寻找两点的一条可行路径,从second到first
	bool FindRoad(int first, int &second, int &ForbidFlag);

	int LastIndex() { return length * width - 1; }
	int Length() { return length; }
	int Width() { return width; }

	enum CnctType { NotConnect, Neighbor, Bias };//连接类型
	enum Position //相对位置
	{
		UP, DOWN, LEFT, RIGHT, UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT
	};

	int NextIndex(int index);//返回下一个下标
	bool Left(int &index,int &flag);//判断能否向左 flag -1 FindRoad  -2 NextIndex
	bool Right(int &index, int &flag);
	bool Upper(int &index, int &flag);
	bool Down(int &index, int &flag);
	int ComparePos(int left, int right);//确定右边元素与左边元素的相对位置
private:
	int length; //长
	int width; //宽
	int last;  //结束位置
	std::vector<bool> array;
};


#endif
