#pragma once   //��ֹͷ�ļ��ظ����� 
#include <iostream>  //���������ͷ�ļ� 
#include "worker.h"
using namespace std;  //ʹ�ñ�׼�����ռ� 

#include <fstream>
#define FILENAME "empFile.txt"

class WorkerManager
{
public:
	//���캯�� 
	WorkerManager();
	//�˵�չʾ 
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//��¼Ա������
	int m_EmpNum;

	//ְ������ָ��
	Worker ** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾ ְ��
	void Show_Emp();

	//ɾ��ְ��
	void Del_Emp();

	//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int  IsExist(int id);
	int *IsExist(std::string name);  //���������� 

   // �޸�ְ��
	void Mod_Emp();

	// ����ְ��
	void Find_Emp();

	//����Ա��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//�������� 
	~WorkerManager();
};