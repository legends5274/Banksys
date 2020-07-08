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
			cout << "해당 이름과 주민번호로 된 계정이 이미 존재합니다." << endl;
			return;
		}
		if (top == BANK_SIZE - 1)
		{
			cout << "은행이 가득 찼습니다." << endl;
			return;
		}
		Account acc(customer, registernum);
		accounts[top++] = acc;
		cout << "계정이 생성되었습니다" << endl;
	}
	const void createBankBook(const char* customer, const char* registernum, const int accID, const int balance, const int type)
	{
		Account* account = this->getAccount(customer, registernum);
		if (account == NULL)
		{
			cout << "존재하지 않는 계정입니다." << endl;
			return;
		}
		if (getBankBook(accID) != NULL)
		{
			cout << "해당 계좌번호는 이미 존재합니다." << endl;
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
			cout << "잘못된 계좌 종류입니다." << endl;
			return;
		}
		if (balance < 10)
		{
			cout << "계좌개설 시 10원이상의 입금액을 넣어야 합니다." << endl;
			return;
		}
		if (!isNormalBankBook && account->getNormalBankBookTop() == 0)
		{
			cout << "입금계좌를 개설하기 위해서는 보통계좌가 개설되어 있어야 합니다." << endl;
			return;
		}
		if (account->createBankBook(accID, balance, isNormalBankBook))
		{
			if (isNormalBankBook)
			{
				cout << "보통계좌가 개설되었습니다." << endl;
			}
			else
			{
				cout << "입금계좌가 개설되었습니다." << endl;
			}
		}
		else
		{
			if (isNormalBankBook)
			{
				cout << "더이상 보통계좌를 생성할 수 없습니다." << endl;
			}
			else
			{
				cout << "더이상 입금계좌를 생성할 수 없습니다." << endl;
			}
		}
	}
	const bool bankDeposit(int accID, int value)
	{
		BankBook* bankBook = this->getBankBook(accID);
		if (bankBook == NULL)
		{
			cout << "계좌가 존재하지 않습니다." << endl;
			return false;
		}
		if (bankBook->deposit(value))
		{
			cout << value << "원을 입금했습니다." << endl;
			return true;
		}
		else
		{
			cout << "값이 0보다 작을 수는 없습니다." << endl;
			return false;
		}
	}
	const bool bankWithdraw(int accID, int value)
	{
		BankBook* bankBook = this->getBankBook(accID);
		if (bankBook == NULL)
		{
			cout << "계좌가 존재하지 않습니다." << endl;
			return false;
		}
		if (bankBook->withdraw(value))
		{
			cout << value << "원을 출금했습니다." << endl;
			return true;
		}
		else
		{
			cout << "값이 0보다 작을 수는 없습니다." << endl;
			return false;
		}
	}
	const bool printAccountData(const char* customer, const char* registernum) const
	{
		const Account* account = this->getAccount(customer, registernum);
		if (account == NULL)
		{
			cout << "존재하지 않는 ID입니다." << endl;
			return false;
		}
		cout << "소유주 : " << account->getName() << endl;
		cout << "주민번호 : " << account->getregisternum() << endl;
		BankBook* bankb;
		int top;
		bankb = account->getNormalBankBook();
		top = account->getNormalBankBookTop();
		for (int i = 0; i < top; i++)
		{
			cout << "보통계좌(" << bankb[i].getBankBookID() << ") " << bankb[i].getBalance() << "원" << endl;
		}
		bankb = account->getDepositBankBook();
		top = account->getDepositBankBookTop();
		for (int i = 0; i < top; i++)
		{
			cout << "예금계좌(" << bankb[i].getBankBookID() << ") " << bankb[i].getBalance() << "원" << endl;
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
		cout << "1. 계정생성" << endl;
		cout << "2_계좌_개설:" << endl;
		cout << "3_입___금:" << endl;
		cout << "4_출___금:" << endl;
		cout << "5_계좌정보_전체_출력:" << endl;
		cout << "6_프로그램_종료:" << endl;
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
			cout << "[계정생성]" << endl;
			customer = inputCharArray("이  름");
			registernum = inputCharArray("주민번호");
			bank->createAccount(customer, registernum);
			break;
		case 2:
			cout << "[계좌개설]" << endl;
			customer = inputCharArray("이  름");
			registernum = inputCharArray("주민번호");
			accID = inputInt("계좌번호");
			select2 = inputInt("계좌종류(1:보통, 2:입금)");
			balance = inputInt("입금액");
			bank->createBankBook(customer, registernum, accID, balance, select2);
			break;
		case 3:
			cout << "[입   금]" << endl;
			accID = inputInt("계좌번호");
			balance = inputInt("입금액");
			bank->bankDeposit(accID, balance);
			break;
		case 4:
			cout << "[출   금]" << endl;
			accID = inputInt("계좌번호");
			balance = inputInt("출금액");
			bank->bankWithdraw(accID, balance);
			break;
		case 5:
			cout << "[계좌정보]" << endl;
			customer = inputCharArray("이  름");
			registernum = inputCharArray("주민번호");
			bank->printAccountData(customer, registernum);
			break;
		case 6:
			cout << "프로그램이 종료됩니다." << endl;
			running = false;
			break;
		default:
			cout << "잘못된 값입니다." << endl;
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
