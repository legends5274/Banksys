#include<iostream>
#include<cstring>
#define NAME_LEN 20
using namespace std;
typedef struct
{
	int accID; //계좌 번호
	int balance; //잔액
	int cusName[NAME_LEN]; //고객이름
} Account;
Account* arr = new Account[100];
int AccCount = 0;
void AddAcc()
{
	if (AccCount >= 100)
	{
		cout << "계좌 개설 한도 초과" << endl;
		return;
	}
	cout << "신규 계좌 개설" << endl;
	cout << "ID 입력: ";
	cin >> arr[AccCount].accID;
	for (int i = 0; i < AccCount; i++)
	{
		if (arr[i].accID == arr[AccCount].accID)
		{
			cout << "계좌 번호 중복" << endl;
			return;
		}
		else if (arr[AccCount].accID <= 0)
		{
			cout << "계좌 번호 불량" << endl;
			return;
		}
	}
	cout << "계좌 이름: ";cin >> arr[AccCount].cusName[NAME_LEN];
	cout << "계좌 계설 초기 입금액을 10원 이상 입금" << endl;
	cout << "금액: "; cin >> arr[AccCount].balance;
	if (arr[AccCount].balance < 10)
	{
		cout << "입금된 금액이 10원 미만" << endl;
		return;
	}
	AccCount++;
	cout << "계좌 계설 성공" << endl;
	return;
}
void Deposit()
{
	if (AccCount == 0)
	{
		cout << "개설된 계좌 없음" << endl;
		return;
	}
	int ID = 0;
	int money = 0;
	cout << "계좌 번호 입력: "; cin >> ID;
	for (int i = 0; i < AccCount; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "입금액: "; cin >> money;
			if (money <= 0)
			{
				cout << "0원은 입금 할 수 없음" << endl;
			}
			arr[i].balance += money;
			cout << money << "입금확인 남은 금액은" << arr[i].balance << endl;
		}
		else
		{
			cout << "계좌번호를 찾을 수 없음" << endl;
		}
	}
}
void Drawal()
{
	if (AccCount == 0)
	{
		cout << "개설된 계좌 없음" << endl;
		return;
	}
	int ID = 0;
	int money = 0;
	cout << "계좌 번호 입력: "; cin >> ID;
	for (int i = 0; i < AccCount; i++)
	{
		if (arr[i].accID == ID)
		{
			cout << "출금액: "; cin >> money;
			if (money <= 0)
			{
				cout << "0원은 출금 할 수 없음" << endl;
			}
			arr[i].balance -= money;
			cout << money << "출금확인 남은 금액은" << arr[i].balance << endl;
			return;
		}
		cout << "계좌번호를 찾을 수 없음." << endl;
	}
}
void PrintAllInfo()
{
	if (AccCount == 0)
	{
		cout << "개설된 계좌 없음" << endl;
		return;
	}
	for (int i = 0; i < AccCount; i++)
	{
		cout << "계좌 이름: " << arr[i].cusName[NAME_LEN] << endl;
		cout << "계좌 변호: " << arr[i].accID << endl;
		cout << "계좌 금액: " << arr[i].balance << endl;
	}
	return;
}
void MenuSelection()
{
	cout << "\n";
	cout << "___SELECT___" << endl;
	cout << "1_계좌_개설:" << endl;
	cout << "2_입___금:" << endl;
	cout << "3_출___금:" << endl;
	cout << "4_계좌정보_전체_출력:" << endl;
	cout << "5_프로그램_종료:" << endl;
}
int main(void)
{
	int select;
	while (true) {
		MenuSelection();
		cout << "선택 : ";
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
			cout << "잘못된 메뉴 번호입니다." << endl;
			break;
		}
	}
}