//�ϰ��ļ�
#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Boss : public Worker
{
public:
	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	virtual  void showInfo();

	//��ȡ��λ��Ϣ 
	virtual string getDeptName();
};