#include<iostream>
#include<cstring>
#define NAME_LEN 20
using namespace std;
typedef struct
{
	int accID; //���� ��ȣ
	int balance; //�ܾ�
	int cusName[NAME_LEN]; //���̸�
} Account;
Account* arr = new Account[100];
int AccCount = 0;
void AddAcc()
{
	if (AccCount >= 100)
	{
		cout << "���� ���� �ѵ� �ʰ�" << endl;
		return;
	}
	cout << "�ű� ���� ����" << endl;
	cout << "ID �Է�: ";
	cin >> arr[AccCount].accID;
	for (int i = 0; i < AccCount; i++)
	{
		if (arr[i].accID == arr[AccCount].accID)
		{
			cout << "���� ��ȣ �ߺ�" << endl;
			return;
		}
		else if (arr[AccCount].accID <= 0)
		{
			cout << "���� ��ȣ �ҷ�" << endl;
			return;
		}
	}
	cout << "���� �̸�: ";cin >> arr[AccCount].cusName[NAME_LEN];
	cout << "���� �輳 �ʱ� �Աݾ��� 10�� �̻� �Ա�" << endl;
	cout << "�ݾ�: "; cin >> arr[AccCount].balance;
	if (arr[AccCount].balance < 10)
	{
		cout << "�Աݵ� �ݾ��� 10�� �̸�" << endl;
		return;
	}
	AccCount++;
	cout << "���� �輳 ����" << endl;
	return;
}
void Deposit()
{
	if (AccCount == 0)
	{
		cout << "������ ���� ����" << endl;
		return;
	}
	int ID = 0;
	int money = 0;
	cout << "���� ��ȣ �Է�: "; cin >> ID;
	for (int i = 0; i < AccCount; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "�Աݾ�: "; cin >> money;
			if (money <= 0)
			{
				cout << "0���� �Ա� �� �� ����" << endl;
			}
			arr[i].balance += money;
			cout << money << "�Ա�Ȯ�� ���� �ݾ���" << arr[i].balance << endl;
		}
		else
		{
			cout << "���¹�ȣ�� ã�� �� ����" << endl;
		}
	}
}
void Drawal()
{
	if (AccCount == 0)
	{
		cout << "������ ���� ����" << endl;
		return;
	}
	int ID = 0;
	int money = 0;
	cout << "���� ��ȣ �Է�: "; cin >> ID;
	for (int i = 0; i < AccCount; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "��ݾ�: "; cin >> money;
			if (money <= 0)
			{
				cout << "0���� ��� �� �� ����" << endl;
			}
			arr[i].balance -= money;
			cout << money << "���Ȯ�� ���� �ݾ���" << arr[i].balance << endl;
			return;
		}
		cout << "���¹�ȣ�� ã�� �� ����." << endl;
	}
}
void PrintAllInfo()
{
	if (AccCount == 0)
	{
		cout << "������ ���� ����" << endl;
		return;
	}
	for (int i = 0; i < AccCount; i++)
	{
		cout << "���� �̸�: " << arr[i].cusName[NAME_LEN] << endl;
		cout << "���� ��ȣ: " << arr[i].accID << endl;
		cout << "���� �ݾ�: " << arr[i].balance << endl;
	}
	return;
}
void MenuSelection()
{
	cout << "\n";
	cout << "___SELECT___" << endl;
	cout << "1_����_����:" << endl;
	cout << "2_��___��:" << endl;
	cout << "3_��___��:" << endl;
	cout << "4_��������_��ü_���:" << endl;
	cout << "5_���α׷�_����:" << endl;
}
int main(void)
{
	int select;
	while (true) {
		MenuSelection();
		cout << "���� : ";
		cin >> select;
		switch (select) {
		case 1:
			AddAcc();
			break;
		case 2:
			Deposit();
			break;
		case 3:
			Drawal();
			break;
		case 4:
			PrintAllInfo();
			break;
		case 5: delete[] arr;
			return 0;
		default:
			cout << "�߸��� �޴� ��ȣ�Դϴ�." << endl;
			break;
		}
	}
}