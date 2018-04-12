#pragma once
#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include<vector>
#include<cmath>
#include<ctime>
#include"scene.h"
class Individual
{
public:
	void create();//创建个体
	void Cut(); //删减元素(优化)
	float Fitness() { return fitness; } //返回适应度
	void Variation(); //变异
private:
	void CalculateFitness();//计算适应度
	int NextIndex(int index);//返回下一个下标
	bool Left(int &index);   //判断能否向左
	bool Right(int &index);
	bool Upper(int &index);
	bool Down(int &index);
	void Insert(int pos);  //插入操作
private:
	std::vector<int> gene;	//个体的基因(元素)
	int	len;		//基因的长度
	int	fitness;	//个体适应度
	int MutationProbability;//变异率
	int MutationNum;        //变异点个数
	int CrossProbability;//交叉率
	static Scene scene;
};

#endif // !_INDIVIDUAL_H_ 
