#include"individual.h"

void Individual::create()//创建个体
{
	srand(time(0));
	int index = 0;
	gene.push_back(index);//start

	//开始随机产生附近的索引并添加到gene中
	int end = scene.LastIndex();
	while (index != end)
	{
		int rdIndex = scene.NextIndex(index); //-1绝路
		//若取得的索引是障碍索引，则一直取到不是障碍为止
		while (scene.IsObstacle(rdIndex))
		{
			rdIndex = scene.NextIndex(index);
		}
		index = rdIndex;
		gene.push_back(index);
	}
	len = gene.size();
}

void Individual::Cut() //删减元素(优化)
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
				++it_left;//检查下一个元素

			it_right = gene.end();
		}
		len = gene.size();
	}
}



void Individual::Variation()//变异
{
	if (len != 0)
	{
		srand(time(0));
		int res = rand() % 100;
		if (res <= MutationProbability)//变异率
		{
			for (int j = 0; j < MutationNum; ++j)//变异点个数
			{
				//如果在变异过程中被删除了，退出变异操作
				if (len == 0)break;

				//随机选择变异位置
				int mutPos = rand() % (len - 2) + 1;

				//将iter更新到变异位置处
				std::vector<int>::iterator iter = gene.begin();
				for (int i = 0; i < mutPos; ++i)iter++;

				//随机选择一种变异方法
				int mutationKind = rand() % 3;
				switch (mutationKind)
				{
				case 1://变异点的元素随机变成其它非障碍元素 
				{//这里要求障碍物都是实心的,否则在插入时无法连接(或许可以删除该个体)
					int i = rand() % (scene.LastIndex() + 1);

					while (scene.IsObstacle(i))
					{
						i = rand() % (scene.LastIndex() + 1);
					}
					//更新该位置的基因内容
					*iter = i;
					//在变异位置进行插入运算
					Insert(mutPos);
					Insert((mutPos - 1));
				}break;
				case 2:		//删除该变异元素
				{
					iter = gene.erase(iter);
					Insert(mutPos - 1);
				}break;
				case 3:		//双点删除法
				{
					//判断是否是倒数第二个点
					if (gene[mutPos + 1] != scene.LastIndex())
					{
						//删除当前元素
						iter = gene.erase(iter);
						//删除当前元素后面的元素
						iter = gene.erase(iter);
						//在删除部位进行插入操作
						Insert(mutPos - 1);
					}
				}break;
				default: break;
				}
				//更新基因长度,以便下一个变异点确定变异位置
				len = gene.size();
			}
			Cut();//删减元素
		}
	}
}

void Individual::CalculateFitness() //计算并返回适应度
{
	if (len != 0)
	{
		std::vector<int>::iterator cmp = gene.begin();
		std::vector<int>::iterator begin = cmp;
		std::vector<int>::iterator end = gene.end();
		cmp++;
		int numOfBeeline = 0;   //直线数量
		int numOfBias = 0;		//斜线数量

								//依次比较相邻的2个索引,并记录下直线和斜线的数目
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
		//确定N的值   (N-8-sqrt(N-8)) / ((N-9)*D)	
		int blockNum = len;
		//计算路径的长度:D
		float pathLength = numOfBeeline + numOfBias * 1.412;
		//计算除数
		float divider = (blockNum - 9) * pathLength;
		//计算被除数
		float individer = blockNum - 8 - sqrt((long double)(blockNum - 8));
		//计算适应量
		long double result = individer / divider;
		fitness = result * 1.0e5;
	}
}


void Individual::Insert(int pos)  //插入操作
{
	//建立2个迭代器并指向断点两端的2个值
	std::vector<int>::iterator begin = gene.begin();
	std::vector<int>::iterator buf = gene.begin() + 1;
	for (int i = 0; i < pos; ++i)
	{
		++begin;
		++buf;
	}
	//保存交叉位置两端的值，便于以后进行比较
	int left = *begin;
	int right = *buf;

	//CheckIfBlack(left);// 判断是否是障碍点,如果是，则发出提示框
	//CheckIfBlack(right);

	//先判断该2个元素是否本来就可以连接
	if (scene.ConnectType(left, right) != scene.NotConnect)return;

	//保存禁止移动的类型，以便避免走出重复路径
	//该路径的确定方式为:与上一次移动方式相反的移动方式
	int forbidAction = -1;//-1表示无方向约束

	while (1)
	{
		//right传递的引用，所以会自动更新
		//返回从right位置向left位置移动的索引(并不总是向left移动)
		bool result = scene.FindRoad(left, right, forbidAction);

		//CheckIfBlack(left);
		//CheckIfBlack(right);

		if (!result)
		{//若寻找索引失败，则删除该个体
			gene.clear();
			fitness = 0;
			len = 0;
			return;
		}

		if (scene.ConnectType(right, 0) != scene.NotConnect)
		{
			//若得到的数和0是相连接的，则插入该数，并把0和该数之间的元素删除
			buf = gene.insert(buf, right);
			gene.erase(gene.begin() + 1, buf);
			break;
		}
		else if (scene.ConnectType(right, left) != scene.NotConnect)
		{
			//如果和left相连接，则插入该数，并停止插入元素
			buf = gene.insert(buf, right);
			break;
		}
		else //若没有达到结束条件，则插入该索引到基因当中	
			buf = gene.insert(buf, right);
	}
}