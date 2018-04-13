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

int Scene::ConnectType(int index1, int index2)//�ж�������������������
{
	if (array[index1] == true || array[index2] == true)
	{
		return NotConnect;
	}
	int res = abs(index1 - index2);//��¼2�������Ĳ�ֵ
	int min = index1 > index2 ? index1 : index2;

	//�ų�2��Ԫ�طֱ�������ߺ����ұ�(��������)�����
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
			return Bias;//"б�Խ�����"
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

bool Scene::FindRoad(int first, int &second, int &ForbidFlag) //Ѱ�������һ������·��
{
	srand(time(0));
	//ȷ��second����� first��λ�ù�ϵ
	int res = ComparePos(first, second);
	switch (res)
	{
	case UP: 
	{
		if (Down(second, ForbidFlag))
			return true;
		else if (rand() % 2)
		{//���� ����
			if (Right(second, ForbidFlag))
				return true;
			else if (Left(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//���� ����
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
		{//���� ����
			if (Right(second, ForbidFlag))
				return true;
			else if (Left(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//���� ����
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
		{//���� ����
			if (Down(second, ForbidFlag))
				return true;
			else if (Upper(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//���� ����
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
		{//���� ����
			if (Down(second, ForbidFlag))
				return true;
			else if (Upper(second, ForbidFlag))
				return true;
			else return false;
		}
		else
		{//���� ����
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
		{//���ܹ�ֱ�Ӳ��뵽���½ǣ������Ȳ������½ǵ�����,�����½�ֹ����
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
		{//�����ֹ���ұ��ߣ����������
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
		{//�����ֹ������ߣ������ұ���
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
		{//�����ֹ���ұ��ߣ����������
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
		{//�����ֹ������ߣ������ұ���
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
	if (index == 0)    //0�����������
	{
		int result = rand() % 2;
		switch (result)
		{
		case 0:   //���ұ߿�ʼ�ж�
		{
			if (Right(index,flag))
				break;
			else
				Down(index,flag);
		}break;
		case 1:    //���±߿�ʼ�ж�
		{
			if (Down(index,flag))
				break;
			else
				Right(index,flag);
		}break;
		default: break;
		}
	}
	else if (index == L - 1)  //���Ͻ�
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
	else if (index == L * (W - 1))  //���½�
	{
		int result = rand() % 2;
		switch (result)
		{
		case 0:		//��-��
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
	else if (index == LastIndex()) //���½�
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
	{	//����һ�����
		int result = rand() % 4;
		switch (result)
		{
		case 0:  //��������    ˳ʱ��
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
		case 3:		//���±߿�ʼ�ж�
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
	if (index % length != 0) //���������һ��
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
	if ((index + 1) % length != 0)//�������ұ�һ��
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

//�ж�right�����left�ķ���
int Scene::ComparePos(int left, int right)
{
	//ȷ��left��right�������λ������
	int left_x = left % length;
	int left_y = left / length;

	int right_x = right % length;
	int right_y = right / length;

	//��ʼ�ж�
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
		//���򷢳�������ʾ
		char error[30] = "wrong pos in CompareIndex";
		//MessageBox(hWnd, TEXT(error), NULL, MB_OK);
		return -1;
	}
}