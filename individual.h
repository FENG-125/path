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
	void create();//��������
	void Cut(); //ɾ��Ԫ��(�Ż�)
	float Fitness() { return fitness; } //������Ӧ��
	void Variation(); //����
private:
	void CalculateFitness();//������Ӧ��
	int NextIndex(int index);//������һ���±�
	bool Left(int &index);   //�ж��ܷ�����
	bool Right(int &index);
	bool Upper(int &index);
	bool Down(int &index);
	void Insert(int pos);  //�������
private:
	std::vector<int> gene;	//����Ļ���(Ԫ��)
	int	len;		//����ĳ���
	int	fitness;	//������Ӧ��
	int MutationProbability;//������
	int MutationNum;        //��������
	int CrossProbability;//������
	static Scene scene;
};

#endif // !_INDIVIDUAL_H_ 
