#include <iostream>
#include "workerManager.h" 
#include "worker.h"
#include "employee.h"
#include "manager.h" 
#include "boss.h" 
using namespace std;

int main()
{


	int choice = 0;
	//ʵ���������߶���
	WorkerManager wm;

	while (true)
	{
		//����չʾ�˵���Ա����
		wm.Show_Menu();

		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
			/*
			0.�˳��������
			1.����ְ����Ϣ
			2.��ʾְ����Ϣ
			3.ɾ����ְְ��
			4.�޸�ְ����Ϣ
			5.����ְ����Ϣ
			6.���ձ������
			7.��������ĵ�
			 */
		case 0:
			wm.ExitSystem();
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls"); //���� 
			break;

		}
	}


	system("pause"); //�������� 
	return 0;
}