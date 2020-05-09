#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <string.h>

//ͳ���ļ������� 
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ���������� 
//		cout<<id<<"   "<<name<<"   "<<dId<<endl;
		num++;
	}

	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker * worker = NULL;
		if (dId == 1) //��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}

		else if (dId == 2) //����
		{
			worker = new Manager(id, name, dId);
		}

		else if (dId == 3) //�ϰ�
		{
			worker = new Boss(id, name, dId);
		}


		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ� 
	ifs.close();

}

//���캯�� 
WorkerManager::WorkerManager()
{
	//1.�ļ������� 
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
		//1.�ļ������� 
	if (!ifs.is_open())
	{
		//		cout<<"�ļ�������"<<endl;
				//��ʼ������
				//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2. �ļ����ڣ�������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
//		 cout<<"�ļ�Ϊ��"<<endl; 
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	//	  cout <<"ְ������Ϊ��"<<num<<endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	// ���ļ��е����ݣ��浽������
	this->init_Emp();

}

//�������� 
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�   д�ļ�

	 //��ÿ��������д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();

}


//���ְ�� 
void WorkerManager::Add_Emp()
{
	cout << "���������ְ��������" << endl;

	int addNum = 0; //�����û����������
	cin >> addNum;
	if (addNum > 0)
	{
		//���

		 //���� ����¿ռ��С 
		int newSize = this->m_EmpNum + addNum;  //�¿ռ����� =  ԭ����¼���� +  �������� 

		 //�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//			delete[]  this->m_EmpArray;
					//�������������
		for (int i = 0; i < addNum; i++)
		{
			int ret;
			int id;//ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��

			cout << "�������" << i + 1 << "����ְ����ţ�" << endl;
			cin >> id;
			ret = this->IsExist(id);
			while (ret != -1)
			{
				cout << "ְ������Ѵ��ڣ����������룺" << endl;
				cin >> id;
				ret = this->IsExist(id);
			}
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ����λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum] = worker;
			this->m_EmpNum = this->m_EmpNum + 1;

			this->m_EmpArray = newSpace;
			this->m_FileIsEmpty = false;

		}
		//�ͷ�ԭ�пռ�
//			 delete[]  this->m_EmpArray;

			 //�����¿ռ��ָ��
//			 this->m_EmpArray = newSpace;

			 //�����µ�ְ������
//			  this->m_EmpNum = newSize; 

			//����ְ����Ϊ�ձ�־
//			this->m_FileIsEmpty = false; 
//			  
		this->save();
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
	}
	else
	{
		cout << "�������������" << endl;
	}
	system("pause");
	system("cls");
}

//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ���� 
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return index;
}

//�ж�ְ���Ƿ����  ���������� 
int *WorkerManager::IsExist(std::string name)
{
	int arr[100] = {};
	int num = 0;
	int * res;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Name == name)
		{
			//�ҵ�ְ��
			arr[num] = i;
			num++;
		}
	}

	res = new int[num+1];
	res[0] = num;
	for (int j = 0; j < num+1; j++)
	{
		res[j+1] = arr[j];
	}
	return res;
}

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//��ְ�����ɾ��
		cout << "������Ҫɾ����Ա����ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)   //���ڲ�ɾ��ְ�� 
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//����ǰ��
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}

			this->m_EmpNum--;  //���������м�¼��Ա���� 
			this->save();
			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ�ְ��" << endl;
		}
	}
	//������� ����
	system("pause");
	system("cls");
}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		int id;
		cout << "������Ҫ�޸ĵ�ְ����ţ�" << endl;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1) {
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������λ��" << endl;
			cout << "1.��ְͨ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				cout << "�����λ����" << endl;
				break;
			}
			//�������� ��������
			this->m_EmpArray[ret] = worker;
			cout << "�޸���ɣ�" << endl;

			//���� ���ļ��� 
			this->save();
		}
		else
		{
			cout << "Ҫ�޸ĵ�Ա��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

//����Ա��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڣ����¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҷ�ʽ��" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��Ա������������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//����Ų�
			int id;
			cout << "������ְ����ţ�" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//�ҵ�Ա��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else if (select == 2) {
			//����������
			string name;
			cout << "������ְ��������" << endl;
			cin >> name;
			int *ret = this->IsExist(name);
			int num_length = ret[0];
			cout << num_length << endl;
			if (num_length != 0)
			{
				//�ҵ�Ա��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				for(int i=0;i<num_length;i++)
				{
					this->m_EmpArray[ret[i+1]] ->showInfo();
				}	

				if (ret != NULL) {

					ret = NULL;
				}
				
			}
			else
			{
				cout << "����ʧ��" << endl;
			}
		}
		else
		{
			cout << "��ѡ����ȷ�Ĳ��ҷ�ʽ��" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//����Ա��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼���" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��ְ���Ž�������" << endl;
		cout << "2.��ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;

		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minormax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //����
				{
					if (m_EmpArray[minormax]->m_Id > m_EmpArray[j]->m_Id)
					{
						minormax = j;
					}
				}
				else  //����
				{
					if (m_EmpArray[minormax]->m_Id < m_EmpArray[j]->m_Id)
					{
						minormax = j;
					}
				}
			}
			if (i != minormax)
			{
				Worker *temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minormax];
				m_EmpArray[minormax] = temp;
			}


		}
	}
	cout << "����ɹ� ��" << endl;
	this->save();  //�����ļ�
	this->Show_Emp();
	system("pause");
	
}

//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();


		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}
	}
}

//�˵�չʾ 
void WorkerManager::Show_Menu()
{
	cout << "*****************************************************" << endl;
	cout << "****************��ӭʹ��ְ������ϵͳ*****************" << endl;
	cout << "*******************0.�˳��������********************" << endl;
	cout << "*******************1.����ְ����Ϣ********************" << endl;
	cout << "*******************2.��ʾְ����Ϣ********************" << endl;
	cout << "*******************3.ɾ����ְְ��********************" << endl;
	cout << "*******************4.�޸�ְ����Ϣ********************" << endl;
	cout << "*******************5.����ְ����Ϣ********************" << endl;
	cout << "*******************6.���ձ������********************" << endl;
	cout << "*******************7.��������ĵ�********************" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
}

//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳����� 
}