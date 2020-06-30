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
			cout << "ID중복" << endl;
			return;
		}
		if (top == 99) 
		{
			cout << "계좌개설가능한도초과" << endl;
			return;
		}
		if (balance < 10) 
		{
			cout << "계좌개설시10원이상입금필수" << endl;
			return;
		}
		Account acc(accountid, balance, customer, registernum);
		accounts[top] = acc;
		top++;
		cout << "계좌개설완료" << endl;
	}
	const bool bankDeposit(int accountid, int value) 
	{
		Account* account = this->getAccount(accountid);
		if (account == NULL) 
		{
			cout << "ID를찾을수없음" << endl;
			return false;
		}
		if (!account->deposit(value)) 
		{
			cout << "입력값오류" << endl;
			return false;
		}
		else 
		{
			cout << value << "원입금완료" << endl;
			return true;
		}
	}
	const bool bankWithdraw(int accountid, int value) 
	{
		Account* account = this->getAccount(accountid);
		if (account == NULL) 
		{
			cout << "ID를찾을수없음" << endl;
			return false;
		}
		if (!account->withdraw(value)) 
		{
			cout << "입력값오류" << endl;
			return false;
		}
		else 
		{
			cout << value << "원출금완료" << endl;
			return true;
		}

	}
	const bool printAccountData(int accountid) const {
		const Account* account = this->getAccount(accountid);
		if (account == NULL) 
		{
			cout << "ID를찾을수없음" << endl;
			return false;
		}
		cout << "계좌번호 : " << account->getaccountid() << endl;
		cout << "금액 : " << account->getBalance() << endl;
		cout << "소유주 : " << account->getName() << endl;
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
		cout << "1_계좌_개설:" << endl;
		cout << "2_입___금:" << endl;
		cout << "3_출___금:" << endl;
		cout << "4_계좌정보_전체_출력:" << endl;
		cout << "5_프로그램_종료:" << endl;
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
			cout << "[계좌개설]" << endl;
			accountid = inputInt("계좌ID");
			customer = inputCharArray("이  름");
			cusNum = inputCharArray("주민번호");
			balance = inputInt("입금액");
			bank->addAccount(accountid, balance, customer, cusNum);
			break;
		case 2:
			cout << "[입   금]" << endl;
			accountid = inputInt("계좌ID");
			balance = inputInt("입금액");
			bank->bankDeposit(accountid, balance);
			break;
		case 3:
			cout << "[출   금]" << endl;
			accountid = inputInt("계좌ID");
			balance = inputInt("출금액");
			bank->bankWithdraw(accountid, balance);
			break;
		case 4:
			cout << "[계좌정보]" << endl;
			accountid = inputInt("계좌ID");
			bank->printAccountData(accountid);
			break;
		case 5:
			cout << "프로그램이 종료됩니다." << endl;
			running = false;
			break;
		default:
			cout << "잘못된 값입니다." << endl;
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