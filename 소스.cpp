#include <iostream>
using namespace std;
#define TEXT_LEN 20
#define BANK_BOOK_SIZE 100
#define BANK_SIZE 10
class BankBook
{
private:
	int bankBookID;
	double balance;
protected:
	virtual double getInterestAmount() = 0;
	BankBook() : bankBookID(-2147483648), balance(0.0) {}
	BankBook(int bankBookID, double balance) : bankBookID(bankBookID), balance(balance) {}
	virtual ~BankBook() {}
public:
	const int getBankBookID() const
	{
		return this->bankBookID;
	}
	const double getBalance() const
	{
		return this->balance;
	}
	const bool deposit(double amount)
	{
		if (amount < 0) return false;
		this->balance += amount;
		this->balance += getInterestAmount();
		return true;
	}
	const bool withdraw(double amount)
	{
		if (amount < 0) return false;
		this->balance -= amount;
		return true;
	}
};
class NormalBankBook : public BankBook {
protected:
	virtual double getInterestAmount() final
	{
		return BankBook::getBalance() * 0.01;
	}
public:
	NormalBankBook() : BankBook() {}
	NormalBankBook(int id, int amount) : BankBook(id, amount) {}
};
class DepositBankBook : public BankBook
{
protected:
	virtual double getInterestAmount() final
	{
		return BankBook::getBalance() * 0.02;
	}
public:
	DepositBankBook() : BankBook() {}
	DepositBankBook(int id, int amount) : BankBook(id, amount) {}
};
class Account
{
private:
	char* customer;
	char* registernum;
	NormalBankBook* normalBankBook;
	DepositBankBook* depositBankBook;
	int normalBankBookTop;
	int depositBankBookTop;
public:
	Account() :customer(NULL), registernum(NULL), normalBankBook(NULL), depositBankBook(NULL),
		normalBankBookTop(0), depositBankBookTop(0) {}
	Account(const Account& account) :
		customer(new char[TEXT_LEN]), registernum(new char[TEXT_LEN]),
		normalBankBook(account.normalBankBook), depositBankBook(account.depositBankBook),
		normalBankBookTop(account.normalBankBookTop), depositBankBookTop(account.depositBankBookTop)
	{
		strcpy(this->customer, account.customer);
		strcpy(this->registernum, account.registernum);
	}
	Account(const char* customer, const char* registernum) :
		customer(new char[TEXT_LEN]), registernum(new char[TEXT_LEN]),
		normalBankBook(new NormalBankBook[BANK_BOOK_SIZE]), depositBankBook(new DepositBankBook[BANK_BOOK_SIZE]),
		normalBankBookTop(0), depositBankBookTop(0)
	{
		strcpy(this->customer, customer);
		strcpy(this->registernum, registernum);
	}
	virtual ~Account()
	{
		if (this->customer != NULL) delete[] customer;
		if (this->registernum != NULL) delete[] registernum;
	}
	bool createBankBook(int id, int amount, bool isNormalBankBook)
	{
		if (isNormalBankBook)
		{
			if (this->normalBankBookTop == BANK_BOOK_SIZE)
			{
				return false;
			}
			this->normalBankBook[normalBankBookTop++] = NormalBankBook(id, amount);
			return true;
		}
		else
		{
			if (this->depositBankBookTop == BANK_BOOK_SIZE)
			{
				return false;
			}
			this->depositBankBook[depositBankBookTop++] = DepositBankBook(id, amount);
			return true;
		}
	}
	char* getName() const
	{
		return this->customer;
	}
	char* getregisternum() const
	{
		return this->registernum;
	}
	NormalBankBook* getNormalBankBook() const
	{
		return this->normalBankBook;
	}
	DepositBankBook* getDepositBankBook() const
	{
		return this->depositBankBook;
	}
	int getNormalBankBookTop() const
	{
		return this->normalBankBookTop;
	}
	int getDepositBankBookTop() const
	{
		return this->depositBankBookTop;
	}
	BankBook* getBankBook(bool isNormalBankBook)
	{
		if (isNormalBankBook)
		{
			return this->normalBankBook;
		}
		else
		{
			return this->depositBankBook;
		}
	}
private:
	Account* accounts;
	int top;
public:
	Bank(int maxSize) : accounts(new Account[maxSize]()), top(0) {}
	virtual ~Bank()
	{
		if (this->accounts != NULL) delete[] accounts;
	}
	const bool hasBankBookID(const int accID) const
	{
		return getBankBook(accID) != NULL;
	}
	BankBook* getBankBook(const int accID) const
	{
		for (int i = 0; i < top; i++)
		{
			Account acc = this->accounts[i];
			BankBook* bankb;
			int bankBookTop;
			bankb = acc.getNormalBankBook();
			bankBookTop = acc.getNormalBankBookTop();
			for (int j = 0; j < bankBookTop; j++)
			{
				if (bankb[j].getBankBookID() == accID) return &bankb[j];
			}
			bankb = acc.getDepositBankBook();
			bankBookTop = acc.getDepositBankBookTop();
			for (int j = 0; j < bankBookTop; j++)
			{
				if (bankb[j].getBankBookID() == accID) return &bankb[j];
			}
		}
		return NULL;
	}
	const int getAccNum(const char* customer, const char* registernum) const
	{
		for (int i = 0; i < top; i++)
		{
			Account acc = this->accounts[i];

			if (strcmp(acc.getName(), customer) == 0 &&
				strcmp(acc.getregisternum(), registernum) == 0)
			{
				return i;
			}
		}
		return -1;
	}
	const bool hasAccount(const char* customer, const char* registernum) const
	{
		return getAccNum(customer, registernum) != -1;
	}
	Account* getAccount(const char* customer, const char* registernum) const
	{
		int no = this->getAccNum(customer, registernum);
		if (no == -1) return NULL;
		return &accounts[no];
	}
	const void createAccount(char* customer, char* registernum)
	{
		if (hasAccount(customer, registernum))
		{
			cout << "�ش� �̸��� �ֹι�ȣ�� �� ������ �̹� �����մϴ�." << endl;
			return;
		}
		if (top == BANK_SIZE - 1)
		{
			cout << "������ ���� á���ϴ�." << endl;
			return;
		}
		Account acc(customer, registernum);
		accounts[top++] = acc;
		cout << "������ �����Ǿ����ϴ�" << endl;
	}
	const void createBankBook(const char* customer, const char* registernum, const int accID, const int balance, const int type)
	{
		Account* account = this->getAccount(customer, registernum);
		if (account == NULL)
		{
			cout << "�������� �ʴ� �����Դϴ�." << endl;
			return;
		}
		if (getBankBook(accID) != NULL)
		{
			cout << "�ش� ���¹�ȣ�� �̹� �����մϴ�." << endl;
			return;
		}
		bool isNormalBankBook;
		switch (type)
		{
		case 1:
			isNormalBankBook = true;
			break;
		case 2:
			isNormalBankBook = false;
			break;
		default:
			cout << "�߸��� ���� �����Դϴ�." << endl;
			return;
		}
		if (balance < 10)
		{
			cout << "���°��� �� 10���̻��� �Աݾ��� �־�� �մϴ�." << endl;
			return;
		}
		if (!isNormalBankBook && account->getNormalBankBookTop() == 0)
		{
			cout << "�Աݰ��¸� �����ϱ� ���ؼ��� ������°� �����Ǿ� �־�� �մϴ�." << endl;
			return;
		}
		if (account->createBankBook(accID, balance, isNormalBankBook))
		{
			if (isNormalBankBook)
			{
				cout << "������°� �����Ǿ����ϴ�." << endl;
			}
			else
			{
				cout << "�Աݰ��°� �����Ǿ����ϴ�." << endl;
			}
		}
		else
		{
			if (isNormalBankBook)
			{
				cout << "���̻� ������¸� ������ �� �����ϴ�." << endl;
			}
			else
			{
				cout << "���̻� �Աݰ��¸� ������ �� �����ϴ�." << endl;
			}
		}
	}
	const bool bankDeposit(int accID, int value)
	{
		BankBook* bankBook = this->getBankBook(accID);
		if (bankBook == NULL)
		{
			cout << "���°� �������� �ʽ��ϴ�." << endl;
			return false;
		}
		if (bankBook->deposit(value))
		{
			cout << value << "���� �Ա��߽��ϴ�." << endl;
			return true;
		}
		else
		{
			cout << "���� 0���� ���� ���� �����ϴ�." << endl;
			return false;
		}
	}
	const bool bankWithdraw(int accID, int value)
	{
		BankBook* bankBook = this->getBankBook(accID);
		if (bankBook == NULL)
		{
			cout << "���°� �������� �ʽ��ϴ�." << endl;
			return false;
		}
		if (bankBook->withdraw(value))
		{
			cout << value << "���� ����߽��ϴ�." << endl;
			return true;
		}
		else
		{
			cout << "���� 0���� ���� ���� �����ϴ�." << endl;
			return false;
		}
	}
	const bool printAccountData(const char* customer, const char* registernum) const
	{
		const Account* account = this->getAccount(customer, registernum);
		if (account == NULL)
		{
			cout << "�������� �ʴ� ID�Դϴ�." << endl;
			return false;
		}
		cout << "������ : " << account->getName() << endl;
		cout << "�ֹι�ȣ : " << account->getregisternum() << endl;
		BankBook* bankb;
		int top;
		bankb = account->getNormalBankBook();
		top = account->getNormalBankBookTop();
		for (int i = 0; i < top; i++)
		{
			cout << "�������(" << bankb[i].getBankBookID() << ") " << bankb[i].getBalance() << "��" << endl;
		}
		bankb = account->getDepositBankBook();
		top = account->getDepositBankBookTop();
		for (int i = 0; i < top; i++)
		{
			cout << "���ݰ���(" << bankb[i].getBankBookID() << ") " << bankb[i].getBalance() << "��" << endl;
		}
		return true;
	}
};
class AccountManager
{
private:
	int select;
	Bank* bank;
	bool running;
	int inputInt(const char* text) const
	{
		int value;
		cout << text << ":";
		cin >> value;
		return value;
	}
	char* inputCharArray(const char* text) const
	{
		char* value = new char[TEXT_LEN];
		cout << text << ":";
		cin >> value;
		return value;
	}
public:
	AccountManager()
		:bank(new Bank(BANK_SIZE)), select(0), running(true) {}
	AccountManager(const AccountManager& bankApp)
		:bank(bankApp.bank), select(bankApp.select), running(bankApp.running) {}
	virtual ~AccountManager()
	{
		if (this->bank != NULL) delete bank;
	}
public:
	const void printMenu() const
	{
		cout << "___SELECT___" << endl;
		cout << "1. ��������" << endl;
		cout << "2_����_����:" << endl;
		cout << "3_��___��:" << endl;
		cout << "4_��___��:" << endl;
		cout << "5_��������_��ü_���:" << endl;
		cout << "6_���α׷�_����:" << endl;
	}
	void cycle()
	{
		cin >> select;
		int accID, balance, select2;
		char* customer = NULL;
		char* registernum = NULL;
		cout << endl;
		switch (select)
		{
		case 1:
			cout << "[��������]" << endl;
			customer = inputCharArray("��  ��");
			registernum = inputCharArray("�ֹι�ȣ");
			bank->createAccount(customer, registernum);
			break;
		case 2:
			cout << "[���°���]" << endl;
			customer = inputCharArray("��  ��");
			registernum = inputCharArray("�ֹι�ȣ");
			accID = inputInt("���¹�ȣ");
			select2 = inputInt("��������(1:����, 2:�Ա�)");
			balance = inputInt("�Աݾ�");
			bank->createBankBook(customer, registernum, accID, balance, select2);
			break;
		case 3:
			cout << "[��   ��]" << endl;
			accID = inputInt("���¹�ȣ");
			balance = inputInt("�Աݾ�");
			bank->bankDeposit(accID, balance);
			break;
		case 4:
			cout << "[��   ��]" << endl;
			accID = inputInt("���¹�ȣ");
			balance = inputInt("��ݾ�");
			bank->bankWithdraw(accID, balance);
			break;
		case 5:
			cout << "[��������]" << endl;
			customer = inputCharArray("��  ��");
			registernum = inputCharArray("�ֹι�ȣ");
			bank->printAccountData(customer, registernum);
			break;
		case 6:
			cout << "���α׷��� ����˴ϴ�." << endl;
			running = false;
			break;
		default:
			cout << "�߸��� ���Դϴ�." << endl;
		}
	}
	const bool isRunning()
	{
		return this->running;
	}
};

int main() {
	AccountManager manager;
	while (manager.isRunning())
	{
		manager.printMenu();
		manager.cycle();
	}
	return 0;
}
