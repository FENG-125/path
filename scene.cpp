#include"scene.h"

Scene::Scene()
{
	Scene(80, 40);
}

Scene::Scene(int len, int wid)
{
	length = len;
	width = wid;
	array.resize(wid*len);
}

Scene::~Scene()
{
	array.clear();
}

void Scene::SetObstacle(int index)
{
	array[index] = true;//
}

bool Scene::IsObstacle(int index)
{
	if (index < length*width && index >= 0)
		return array[index];
	else
		return true;
}

int Scene::ConnectType(int index1, int index2)//判断两个坐标点的连接类型
{
	if (array[index1] == true || array[index2] == true)
	{
		return NotConnect;
	}
	int res = abs(index1 - index2);//记录2个索引的差值
	int min = index1 > index2 ? index1 : index2;

	//排除2个元素分别在最左边和最右边(行数相邻)的情况
	if ((index1 % length == 0) && ((index2 + 1) % length == 0))
	{
		return NotConnect;
	}
	else if (((index2 % length == 0) && ((index1 + 1) % length == 0)))
	{
		return NotConnect;
	}

	if (res == 0 || res == length || res == 1)
	{
		return Neighbor;
	}
	else if (res == length - 1)
	{
		if (array[min - 1] == 0 && array[min + length] == 0)
		{
			return Bias;//"斜对角连接"
		}
	}
	else if (res == length + 1)
	{
		if (array[min + 1] == 0 && array[min + length] == 0)
		{
			return Bias;
		}
	}
	return NotConnect;
}

void Scene::FindRoad() //寻找两点的一条可行路径
{

}