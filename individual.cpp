#include"individual.h"

void Individual::create()//��������
{
	srand(time(0));
	int index = 0;
	gene.push_back(index);//start

	//��ʼ���������������������ӵ�gene��
	int end = scene.LastIndex();
	while (index != end)
	{
		int rdIndex = scene.NextIndex(index); //-1��·
		//��ȡ�õ��������ϰ���������һֱȡ�������ϰ�Ϊֹ
		while (scene.IsObstacle(rdIndex))
		{
			rdIndex = scene.NextIndex(index);
		}
		index = rdIndex;
		gene.push_back(index);
	}
	len = gene.size();
}

void Individual::Cut() //ɾ��Ԫ��(�Ż�)
{
	if (len != 0)
	{
		std::vector<int>::iterator it_left = gene.begin();
		std::vector<int>::iterator it_right = gene.end();
		while (it_left != gene.end())
		{
			--it_right;
			while (it_right != it_left)
			{
				if (scene.ConnectType(*it_right, *it_left) != scene.NotConnect)
					break;
				else
					--it_right;
			}

			if (it_right != it_left)
			{
				if (*it_right == *it_left)
				{
					it_left = gene.erase(it_left, it_right);
					++it_left;
				}
				else
				{
					it_left = gene.erase(it_left + 1, it_right);
				}
			}
			else
				++it_left;//�����һ��Ԫ��

			it_right = gene.end();
		}
		len = gene.size();
	}
}



void Individual::Variation()//����
{
	if (len != 0)
	{
		srand(time(0));
		int res = rand() % 100;
		if (res <= MutationProbability)//������
		{
			for (int j = 0; j < MutationNum; ++j)//��������
			{
				//����ڱ�������б�ɾ���ˣ��˳��������
				if (len == 0)break;

				//���ѡ�����λ��
				int mutPos = rand() % (len - 2) + 1;

				//��iter���µ�����λ�ô�
				std::vector<int>::iterator iter = gene.begin();
				for (int i = 0; i < mutPos; ++i)iter++;

				//���ѡ��һ�ֱ��췽��
				int mutationKind = rand() % 3;
				switch (mutationKind)
				{
				case 1://������Ԫ���������������ϰ�Ԫ�� 
				{//����Ҫ���ϰ��ﶼ��ʵ�ĵ�,�����ڲ���ʱ�޷�����(�������ɾ���ø���)
					int i = rand() % (scene.LastIndex() + 1);

					while (scene.IsObstacle(i))
					{
						i = rand() % (scene.LastIndex() + 1);
					}
					//���¸�λ�õĻ�������
					*iter = i;
					//�ڱ���λ�ý��в�������
					Insert(mutPos);
					Insert((mutPos - 1));
				}break;
				case 2:		//ɾ���ñ���Ԫ��
				{
					iter = gene.erase(iter);
					Insert(mutPos - 1);
				}break;
				case 3:		//˫��ɾ����
				{
					//�ж��Ƿ��ǵ����ڶ�����
					if (gene[mutPos + 1] != scene.LastIndex())
					{
						//ɾ����ǰԪ��
						iter = gene.erase(iter);
						//ɾ����ǰԪ�غ����Ԫ��
						iter = gene.erase(iter);
						//��ɾ����λ���в������
						Insert(mutPos - 1);
					}
				}break;
				default: break;
				}
				//���»��򳤶�,�Ա���һ�������ȷ������λ��
				len = gene.size();
			}
			Cut();//ɾ��Ԫ��
		}
	}
}

void Individual::CalculateFitness() //���㲢������Ӧ��
{
	if (len != 0)
	{
		std::vector<int>::iterator cmp = gene.begin();
		std::vector<int>::iterator begin = cmp;
		std::vector<int>::iterator end = gene.end();
		cmp++;
		int numOfBeeline = 0;   //ֱ������
		int numOfBias = 0;		//б������

								//���αȽ����ڵ�2������,����¼��ֱ�ߺ�б�ߵ���Ŀ
		for (; begin != end && cmp != end; ++begin, ++cmp)
		{
			int result = scene.ConnectType(*begin, *cmp);
			switch (result)
			{
			case scene.Bias:
				numOfBias++; break;
			case scene.Neighbor:
				numOfBeeline++; break;
			default: break;
			}
		}
		//ȷ��N��ֵ   (N-8-sqrt(N-8)) / ((N-9)*D)	
		int blockNum = len;
		//����·���ĳ���:D
		float pathLength = numOfBeeline + numOfBias * 1.412;
		//�������
		float divider = (blockNum - 9) * pathLength;
		//���㱻����
		float individer = blockNum - 8 - sqrt((long double)(blockNum - 8));
		//������Ӧ��
		long double result = individer / divider;
		fitness = result * 1.0e5;
	}
}


void Individual::Insert(int pos)  //�������
{
	//����2����������ָ��ϵ����˵�2��ֵ
	std::vector<int>::iterator begin = gene.begin();
	std::vector<int>::iterator buf = gene.begin() + 1;
	for (int i = 0; i < pos; ++i)
	{
		++begin;
		++buf;
	}
	//���潻��λ�����˵�ֵ�������Ժ���бȽ�
	int left = *begin;
	int right = *buf;

	//CheckIfBlack(left);// �ж��Ƿ����ϰ���,����ǣ��򷢳���ʾ��
	//CheckIfBlack(right);

	//���жϸ�2��Ԫ���Ƿ����Ϳ�������
	if (scene.ConnectType(left, right) != scene.NotConnect)return;

	//�����ֹ�ƶ������ͣ��Ա�����߳��ظ�·��
	//��·����ȷ����ʽΪ:����һ���ƶ���ʽ�෴���ƶ���ʽ
	int forbidAction = -1;//-1��ʾ�޷���Լ��

	while (1)
	{
		//right���ݵ����ã����Ի��Զ�����
		//���ش�rightλ����leftλ���ƶ�������(����������left�ƶ�)
		bool result = scene.FindRoad(left, right, forbidAction);

		//CheckIfBlack(left);
		//CheckIfBlack(right);

		if (!result)
		{//��Ѱ������ʧ�ܣ���ɾ���ø���
			gene.clear();
			fitness = 0;
			len = 0;
			return;
		}

		if (scene.ConnectType(right, 0) != scene.NotConnect)
		{
			//���õ�������0�������ӵģ���������������0�͸���֮���Ԫ��ɾ��
			buf = gene.insert(buf, right);
			gene.erase(gene.begin() + 1, buf);
			break;
		}
		else if (scene.ConnectType(right, left) != scene.NotConnect)
		{
			//�����left�����ӣ�������������ֹͣ����Ԫ��
			buf = gene.insert(buf, right);
			break;
		}
		else //��û�дﵽ����������������������������	
			buf = gene.insert(buf, right);
	}
}