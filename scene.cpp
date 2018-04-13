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

bool Scene::FindRoad(int first, int &second, int &ForbidFlag) //寻找两点的一条可行路径
{
	srand(time(0));
	//确定second相对于 first的位置关系
	int res = ComparePos(first, second);
	switch (res)
	{
	case UP: 
	{
		if (Down(second, ForbidFlag))
			return true;
		else if (rand() % 2)
		{//先右 后左
			if (Right(second, ForbidFlag))
				return true;
			else if (Left(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//先左 后右
			if (Left(second, ForbidFlag))
				return true;
			else if (Right(second, ForbidFlag))
				return true;
			else return false;
		}
	}
	case DOWN:
	{
		if (Upper(second, ForbidFlag))
			return true;
		else if (rand() % 2)
		{//先右 后左
			if (Right(second, ForbidFlag))
				return true;
			else if (Left(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//先左 后右
			if (Left(second, ForbidFlag))
				return true;
			else if (Right(second, ForbidFlag))
				return true;
			else return false;
		}
	}
	case LEFT:
	{
		if (Right(second, ForbidFlag))
			return true;
		else if (rand() % 2)
		{//先下 后上
			if (Down(second, ForbidFlag))
				return true;
			else if (Upper(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//先上 后下
			if (Upper(second, ForbidFlag))
				return true;
			else if (Down(second, ForbidFlag))
				return true;
			else return false;
		}
	}
	case RIGHT:
	{
		if (Left(second, ForbidFlag))
			return true;
		else if (rand() % 2)
		{//先下 后上
			if (Down(second, ForbidFlag))
				return true;
			else if (Upper(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//先上 后下
			if (Upper(second, ForbidFlag))
				return true;
			else if (Down(second, ForbidFlag))
				return true;
			else return false;
		}
	}
	case UP_LEFT:
	{
		if (ConnectType(second, second + (length + 1)) != NotConnect && ForbidFlag != DOWN_RIGHT)
		{//若能够直接插入到右下角，则优先插入右下角的索引,并更新禁止动作
			second += (length + 1);
			ForbidFlag = UP_LEFT;
			return true;
		}
		else if (rand() % 2)
		{
			if (Right(second, ForbidFlag))
				return true;
			else if (Down(second, ForbidFlag))
				return true;
		}
		else
		{
			if (Down(second, ForbidFlag))
				return true;
			else if (Right(second, ForbidFlag))
				return true;

		}
		if (ForbidFlag == RIGHT)
		{//如果禁止往右边走，则往左边走
			if (Left(second, ForbidFlag))
				return true;
			else return false;
		}
		else if (ForbidFlag == DOWN)
		{
			if (Upper(second, ForbidFlag))
				return true;
			else return false;
		}
		else return false;
	}
	case  UP_RIGHT:
	{
		if (ConnectType(second, second + (length - 1)) != NotConnect && ForbidFlag != DOWN_LEFT)
		{
			second += (length - 1);
			ForbidFlag = UP_RIGHT;
			return true;
		}
		else if (rand() % 2)
		{
			if (Left(second, ForbidFlag))
				return true;
			else if (Down(second, ForbidFlag))
				return true;
		}
		else
		{
			if (Down(second, ForbidFlag))
				return true;
			else if (Left(second, ForbidFlag))
				return true;
		}
		if (ForbidFlag == LEFT)
		{//如果禁止往左边走，则往右边走
			if (Right(second, ForbidFlag))
				return true;
			else return false;
		}
		else if (ForbidFlag == DOWN)
		{
			if (Upper(second, ForbidFlag))
				return true;
			else return false;
		}
		else return false;
	}
	case DOWN_LEFT:
	{
		if (ConnectType(second, second - (length - 1)) != NotConnect && ForbidFlag != UP_RIGHT)
		{
			second -= (length - 1);
			ForbidFlag = DOWN_LEFT;
			return true;
		}
		else if (rand() % 2)
		{
			if (Right(second, ForbidFlag))
				return true;
			else if (Upper(second, ForbidFlag))
				return true;
		}
		else
		{
			if (Upper(second, ForbidFlag))
				return true;
			else if (Right(second, ForbidFlag))
				return true;
		}
		if (ForbidFlag == RIGHT)
		{//如果禁止往右边走，则往左边走
			if (Left(second, ForbidFlag))
				return true;
			else return false;
		}
		else if (ForbidFlag == UP)
		{
			if (Down(second, ForbidFlag))
				return true;
			else return false;
		}
		else return false;
	}
	case DOWN_RIGHT:
	{
		if (ConnectType(second, second - (length + 1)) != NotConnect && ForbidFlag != UP_LEFT)
		{
			second -= (length + 1);
			ForbidFlag = DOWN_RIGHT;
			return true;
		}
		else if (rand() % 2)
		{
			if (Left(second, ForbidFlag))
				return true;
			else if (Upper(second, ForbidFlag))
				return true;
		}
		else
		{
			if (Upper(second, ForbidFlag))
				return true;
			else if (Left(second, ForbidFlag))
				return true;
		}
		if (ForbidFlag == LEFT)
		{//如果禁止往左边走，则往右边走
			if (Right(second, ForbidFlag))
				return true;
			else return false;
		}
		else if (ForbidFlag == UP)
		{
			if (Down(second, ForbidFlag))
				return true;
			else return false;
		}
		else return false;
	}
	default: return false;
	}

}

int Scene::NextIndex(int index)
{
	int start = index;
	int L = length;
	int W = width;
	int flag = -2;
	if (index == 0)    //0号索引的情况
	{
		int result = rand() % 2;
		switch (result)
		{
		case 0:   //从右边开始判断
		{
			if (Right(index,flag))
				break;
			else
				Down(index,flag);
		}break;
		case 1:    //从下边开始判断
		{
			if (Down(index,flag))
				break;
			else
				Right(index,flag);
		}break;
		default: break;
		}
	}
	else if (index == L - 1)  //右上角
	{
		int result = rand() % 2;
		switch (result)
		{
		case 0:
		{
			if (Left(index,flag))
				break;
			else
				Down(index,flag);
		}break;
		case 1:
		{
			if (Down(index, flag))
				break;
			else
				Left(index, flag);
		}break;
		default: break;
		}
	}
	else if (index == L * (W - 1))  //左下角
	{
		int result = rand() % 2;
		switch (result)
		{
		case 0:		//右-上
		{
			if (Right(index, flag))
				break;
			else
				Upper(index, flag);
		}break;
		case 1:
		{
			if (Upper(index, flag))
				break;
			else
				Right(index, flag);
		}
		break;
		default: break;
		}
	}
	else if (index == LastIndex()) //右下角
	{
		int result = rand() % 2;
		switch (result)
		{
		case 0:
		{
			if (Left(index, flag))
				break;
			else
				Upper(index, flag);
		}break;
		case 1:
		{
			if (Upper(index, flag))
				break;
			else
				Left(index, flag);
		}break;
		default: break;
		}
	}
	else
	{	//处理一般情况
		int result = rand() % 4;
		switch (result)
		{
		case 0:  //左上右下    顺时针
		{
			if (Left(index, flag))
				break;
			else if (Upper(index, flag))
				break;
			else if (Right(index, flag))
				break;
			else
				Down(index, flag);
		}break;
		case 1:
		{
			if (Upper(index, flag))
				break;
			else if (Right(index, flag))
				break;
			else if (Down(index, flag))
				break;
			else
				Left(index, flag);
		}break;
		case 2:
		{
			if (Right(index, flag))
				break;
			else if (Down(index, flag))
				break;
			else if (Left(index, flag))
				break;
			else
				Upper(index, flag);
		}break;
		case 3:		//从下边开始判断
		{
			if (Down(index, flag))
				break;
			else if (Left(index, flag))
				break;
			else if (Upper(index, flag))
				break;
			else
				Right(index, flag);
		}break;
		default: break;
		}
	}

	if (index == start) return -1;
	return index;
}

bool Scene::Left(int &index, int &flag)
{
	if (index % length != 0) //不在最左边一列
	{
		if (!IsObstacle(index - 1) && flag != LEFT)
		{
			--index;
			if (flag != -2)
				flag = RIGHT;
			return true;
		}
	}
	return false;
}
bool Scene::Right(int &index, int &flag)
{
	if ((index + 1) % length != 0)//不在最右边一列
	{
		if (!IsObstacle(index + 1) && flag != RIGHT)
		{
			++index;
			if (flag != -2)
				flag = LEFT;
			return true;
		}
	}
	return false;
}
bool Scene::Upper(int &index, int &flag)
{
	if (!IsObstacle(index - length) && flag != UP)
	{
		index -= length;
		if (flag != -2)
			flag = DOWN;
		return true;
	}
	return false;
}
bool Scene::Down(int &index, int &flag)
{
	if (!IsObstacle(index + length) && flag != DOWN)
	{
		index += length;
		if (flag != -2)
			flag = UP;
		return true;
	}
	return false;
}

//判断right相对于left的方向
int Scene::ComparePos(int left, int right)
{
	//确定left和right相对起点的位置坐标
	int left_x = left % length;
	int left_y = left / length;

	int right_x = right % length;
	int right_y = right / length;

	//开始判断
	if (left_x == right_x)
	{
		if (right_y>left_y)
		{
			return DOWN;
		}
		else return UP;
	}
	else if (left_y == right_y)
	{
		if (right_x>left_x)
		{
			return RIGHT;
		}
		else return LEFT;
	}
	else if (left_x>right_x)
	{
		if (left_y>right_y)
		{
			return UP_LEFT;
		}
		else return DOWN_LEFT;
	}
	else if (left_x<right_x)
	{
		if (left_y>right_y)
		{
			return UP_RIGHT;
		}
		else return DOWN_RIGHT;
	}
	else
	{
		//否则发出错误提示
		char error[30] = "wrong pos in CompareIndex";
		//MessageBox(hWnd, TEXT(error), NULL, MB_OK);
		return -1;
	}
}