#ifndef _SCENE_H
#define _SCENE_H

#include<vector>

class Scene
{
public:
	Scene();
	Scene(int len, int wid);
	~Scene();

	void SetObstacle(int index);//设置障碍
	bool IsObstacle(int index);//是否为障碍
	int ConnectType(int index1, int index2);//判断两个坐标点的连接类型

	void FindRoad(); //寻找两点的一条可行路径

	int LastIndex() { return length * width - 1; }
	int Length() { return length; }
	int Width() { return width; }
	enum CnctType { NotConnect, Neighbor, Bias };
private:
	int length; //长
	int width; //宽
	int last;  //结束位置
	std::vector<bool> array;
};


#endif
