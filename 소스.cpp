#include <iostream>

using namespace std;
#define NAME_LEN 20
class Account {
private:
	int accountid;
	int balance;
	char* customer;
	char* registernum;
public:
	Account() :accountid(-2147483648), balance(0), customer(NULL), registernum(NULL) {}
	Account(const Account& account) :accountid(account.accountid), balance(account.balance),
		customer(new char[NAME_LEN]), registernum(new char[NAME_LEN]) 
	{
		strcpy(account.customer, this->customer);
		strcpy(account.registernum, this->registernum);
	}
	~Account() 
	{
		if (this->customer != NULL) delete[] customer;
		if (this->registernum != NULL) delete[] registernum;
	}
	Account(int accountid, int balance, char*& customer, char*& registernum)
		:accountid(accountid), balance(balance), customer(customer), registernum(registernum) {}
	const int getaccountid() const 
	{
		return this->accountid;
	}
	const int getBalance() const 
	{
		return this->balance;
	}
	const bool deposit(int amount) 
	{
		if (amount < 0) return false;
		this->balance += amount;
		return true;
	}
	const bool withdraw(int amount) 
	{
		if (amount < 0) return false;
		this->balance -= amount;
		return true;
	}
	const char* getName() const 
	{
		return this->customer;
	}
	const char* getregisternum() const 
	{
		return this->registernum;
	}
};
class Bank 
{
private:
	Account* accounts;
	int top;
public:
	Bank(int max) 
	{
		accounts = new Account[max]();
		top = 0;
	}
	~Bank() 
	{
		if (this->accounts != NULL) delete[] accounts;
	}
	const bool hasaccountid(const int accountid) const 
	{
		return getAccNum(accountid) != -1;
	}
	const int getAccNum(const int accountid) const 
	{
		int i;
		for (i = 0; i < top; i++) 
		{
			if (accounts[i].getaccountid() == accountid) return i;
		}
		return -1;
	}
	Account* getAccount(const int accountid) const 
	{
		int no = this->getAccNum(accountid);
		if (no == -1) return NULL;
		return &accounts[no];
	}
	const void addAccount(const int accountid, const int balance, char*& customer, char*& registernum) 
	{
		if (hasaccountid(accountid)) 
		{
			cout << "ID�ߺ�" << endl;
			return;
		}
		if (top == 99) 
		{
			cout << "���°��������ѵ��ʰ�" << endl;
			return;
		}
		if (balance < 10) 
		{
			cout << "���°�����10���̻��Ա��ʼ�" << endl;
			return;
		}
		Account acc(accountid, balance, customer, registernum);
		accounts[top] = acc;
		top++;
		cout << "���°����Ϸ�" << endl;
	}
	const bool bankDeposit(int accountid, int value) 
	{
		Account* account = this->getAccount(accountid);
		if (account == NULL) 
		{
			cout << "ID��ã��������" << endl;
			return false;
		}
		if (!account->deposit(value)) 
		{
			cout << "�Է°�����" << endl;
			return false;
		}
		else 
		{
			cout << value << "���ԱݿϷ�" << endl;
			return true;
		}
	}
	const bool bankWithdraw(int accountid, int value) 
	{
		Account* account = this->getAccount(accountid);
		if (account == NULL) 
		{
			cout << "ID��ã��������" << endl;
			return false;
		}
		if (!account->withdraw(value)) 
		{
			cout << "�Է°�����" << endl;
			return false;
		}
		else 
		{
			cout << value << "����ݿϷ�" << endl;
			return true;
		}

	}
	const bool printAccountData(int accountid) const {
		const Account* account = this->getAccount(accountid);
		if (account == NULL) 
		{
			cout << "ID��ã��������" << endl;
			return false;
		}
		cout << "���¹�ȣ : " << account->getaccountid() << endl;
		cout << "�ݾ� : " << account->getBalance() << endl;
		cout << "������ : " << account->getName() << endl;
		return true;
	}
};
class AccountManager 
{
private:
	int select;
	Bank* bank;
	bool running;
	const void Menu() const 
	{
		cout << "\n";
		cout << "___SELECT___" << endl;
		cout << "1_����_����:" << endl;
		cout << "2_��___��:" << endl;
		cout << "3_��___��:" << endl;
		cout << "4_��������_��ü_���:" << endl;
		cout << "5_���α׷�_����:" << endl;
	}
	const int inputInt(const char* text) const 
	{
		int value;
		cout << text << ":";
		cin >> value;
		return value;
	}
	char* inputCharArray(const char* text) const 
	{
		char* value = new char[NAME_LEN];
		cout << text << ":";
		cin >> value;
		return value;
	}
	void Selection() 
	{
		cin >> select;
		int accountid, balance;
		char* customer;
		char* cusNum;
		switch (select) {
		case 1:
			cout << "[���°���]" << endl;
			accountid = inputInt("����ID");
			customer = inputCharArray("��  ��");
			cusNum = inputCharArray("�ֹι�ȣ");
			balance = inputInt("�Աݾ�");
			bank->addAccount(accountid, balance, customer, cusNum);
			break;
		case 2:
			cout << "[��   ��]" << endl;
			accountid = inputInt("����ID");
			balance = inputInt("�Աݾ�");
			bank->bankDeposit(accountid, balance);
			break;
		case 3:
			cout << "[��   ��]" << endl;
			accountid = inputInt("����ID");
			balance = inputInt("��ݾ�");
			bank->bankWithdraw(accountid, balance);
			break;
		case 4:
			cout << "[��������]" << endl;
			accountid = inputInt("����ID");
			bank->printAccountData(accountid);
			break;
		case 5:
			cout << "���α׷��� ����˴ϴ�." << endl;
			running = false;
			break;
		default:
			cout << "�߸��� ���Դϴ�." << endl;
		}
	}
public:
	AccountManager()
		:bank(new Bank(100)), select(0), running(true) {}
	AccountManager(const AccountManager& bankApp)
		:bank(bankApp.bank), select(bankApp.select), running(bankApp.running) {}
	~AccountManager() 
	{
		if (this->bank != NULL) delete bank;
	}
	const void run() 
	{
		while (this->running) 
		{
			this->Menu();
			this->Selection();
		}
	}
};
int main()
{
	AccountManager bankApplication;
	bankApplication.run();
	return 0;
}