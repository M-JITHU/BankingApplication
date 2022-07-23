#include<iostream>
#include<math.h>
#include<time.h>
#include<exception>
#include<stdexcept>
#include<vector>
#include<windows.h>
    using namespace std;

    //single exception class for handling all kinds of erros
 class bankException : public runtime_error
    {
       public:
       int errorNo;
       string Message;
       bankException(int errorNo,string Message):runtime_error(Message)
       {
           this->errorNo=errorNo;
           this->Message=Message;
       }
       void errorMessage()
       {
           cout<<errorNo<<":"<<Message<<endl;

       }
   };

   class User
   {
        int userId;
        string userName;
        string password;
        int age;
        int mobileNo;
        string Address;
        string Qualification;
        bool ownsloan,ownsinsurance;

    public:
        static int autoUser;
        friend class bankApplication;

       /* User()
    {
        userId=0;
        userName="";
        password="";
        age=0;
        mobileNo=0;
        Address="";
        Qualification="";
	}*/

	void addUser(string userName,string password,int age,int mobileNo,string Address,string Qualification)
	{
	    this->userId=autoUser++; //auto assigning user id
        this->userName=userName;
        this->password=password;
        this->age=age;
        this->mobileNo=mobileNo;
        this->Address=Address;
        this->Qualification=Qualification;
        this->ownsloan=false;
        this->ownsinsurance=false;
	}

	void printUser()
	{

	    cout<<"the user details are:"<<endl;
        cout<<"-----------------------------------------"<<endl;
	    cout<<"the userID:"<<userId<<endl;
	    cout<<"userName:"<<userName<<endl;
	    cout<<"age:"<<age<<endl;
	    cout<<"mobile number:"<<mobileNo<<endl;
	    cout<<"address:"<<Address<<endl;
	    cout<<"qualifications:"<<Qualification<<endl;
	    cout<<"has loan:"<<ownsloan<<endl;
	    cout<<"has insurance"<<ownsinsurance<<endl;
	    cout<<"----------------------------------------"<<endl;
	}
};

 class BankAccount
 {
     protected:
	int accNo;
	int userID;
	string name;
	double accBal;
	bool type;

 public:
     static int autoAccount;
     static int noOfTransactions;
     friend class bankApplication;
	BankAccount()
	{
        accNo=0;
        accBal=0;
        type=false;
	}
	BankAccount(int userID, double accBal)
	{
        this->userID=userID;
        this->accBal=accBal;
	}
	virtual void credit(double amt) = 0;
    virtual void debit(double amt) = 0;
    virtual void printAccount() = 0;
 };

 class savingsAccount:public BankAccount
    {

     public:
     double penaltyAmount;

    public:
    savingsAccount(int userID,double accBal):BankAccount(userID,accBal)
    {
        type=true;
        accNo=autoAccount++;  //auto created accountnumber
    }
    void debit(double amt)
    {
        if(noOfTransactions<=5)
        {
            if((accBal-amt)>=100)
            {
               accBal-=amt;
               noOfTransactions++;
            }
            else
            {
                throw bankException(2002,"insufficient balance");
            }
        }

    }
    void credit(double amt)
    {
        if(noOfTransactions<=5)
           {
            accBal+=amt;
            noOfTransactions++;
           }
           else
            {
            throw bankException(3001,"you have reached your transaction limit ");
           }

    }
    void printAccount()
    {
        cout << " Account details - " << endl;
        cout << "User ID: " << userID<< endl;
        cout << "Account Number: " << accNo << endl;
        cout << "Balance: " << accBal << endl;
        if(type)
        {
          cout << "Bank Account type: savings account" << endl;
        }


    }
};

 class currentAccount:public BankAccount
    {
        public:
        currentAccount(int userID,double accBal):BankAccount(userID,accBal)
        {
            type=false;
            accNo=autoAccount++;
        }

        void debit(double amt)
        {
            if((accBal-amt)>=100)
            accBal-=amt;

        }
        void credit(double amt)
        {
           accBal+=amt;

        }
        void printAccount()
        {
         cout << " Account details - " << endl;
        cout << "User ID: " << userID<< endl;
        cout << "Account Number: " << accNo << endl;
        cout << "Balance: " << accBal << endl;
        if(!type)
        {
          cout << "Bank Account type: current account" << endl;
        }

        }


    };
    class loan
    {
        public:
        int    loanId,ch;
        string loanType;
        double loanAmount,intrest,period,total,monthPay,paidAmount,balanceAmount;


     loan(int loanId)
        {
            this->loanId = loanId;

        }
    void searchLoan()
    {
        cout << "choose type of loan you want: " << endl;
        cout<< "1. Education Loan." << endl;
        cout << "2. Home Loan " << endl;
        cout << "3. Vehicle Loan " << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            intrest = 6.0;
            loanType = "Education Loan";
            break;
        case 2:
            intrest= 10.0;
            loanType = "Home Loan";
            break;
        case 3:
            intrest = 8.0;
            loanType = "Vehicle Loan";
            break;
        default:
            cout << "incorrect choice." << endl;
            break;
        }
    }
    void addLoan()
    {
        searchLoan();
        cout << "Enter the loan amount: ";
        cin >>loanAmount;
        cout << "Enter the loanPeriod(in years): ";
        cin >> period;
        double
        totalIntrest=(period* loanAmount * (intrest / 100.00));
        total = loanAmount +totalIntrest;
        monthPay = total / (period * 12);

        cout << "Total amount to be paid: " << total << endl;
        cout << "Total interest: " <<totalIntrest<< endl;
        cout << "Monthly amount to be paid: " << monthPay << endl;
        balanceAmount = total;
        paidAmount= 0.0;
    }
    void editloan(double amt)
    {
        paidAmount += amt;
        balanceAmount -= amt;
    }
    void printLoan()
    {

        cout << "------------------------------------------------" << endl;
        cout << "Loan details of user with userId " << loanId << " is -" << endl;
        cout << "type of loan: " << loanType << endl;
        cout << "Total LoanAmount: " << total << endl;
        cout << "Interest provided: " << intrest<< endl;
        cout << "amount paid to bank: " << paidAmount << endl;
        cout << "remaining amount: " << balanceAmount << endl;
    }

};
    class insurance
    {
    public:
        int insuranceId,ch;
        string insuranceType;
        double insuranceAmount,bonus,totalIAmount;
        double insurancePeriod,premium;

    insurance(int insuranceId)
        {
            this->insuranceId= insuranceId;

        }
    void searchIunsurance()
    {
        cout<< "choose type of isurance you want: " << endl;
        cout<<"1.  life insurance" << endl;
        cout<<"2. Home insurance " << endl;
        cout<<"3. Vehicle insurance" << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            bonus=5000;
            insuranceType= "life insurance";
            break;
        case 2:
            bonus=10000;
            insuranceType = "Home insurance";
            break;
        case 3:
            bonus=2000;
            insuranceType = "Vehicle insurance";
            break;
        default:
            cout << "incorrect choice." << endl;
            break;
        }
    }
    void addinsurance()
    {
        searchIunsurance();
        cout << "Enter number of InsurancePeriod: "<<endl;
        cin >>insurancePeriod;
        cout<<"enter the insurance amount"<<endl;
        cin>>insuranceAmount;

        totalIAmount=(insuranceAmount+(bonus*insurancePeriod));
        bonus=bonus*(insurancePeriod*4);
        premium=insuranceAmount/(insurancePeriod*4);

        cout << "Total insurance amount: "<<totalIAmount<< endl;
        cout << "Total bonus: " << bonus<<endl;
        cout << "premium amount: " <<premium<< endl;
    }
    void printInsurance()
    {

        cout << "------------------------------------------------" << endl;
        cout << "insurance details of user with userId " << insuranceId<< " is -" << endl;
        cout << "type of insurance: " << insuranceType << endl;
        cout << "Total insuranceAmount: " <<totalIAmount<< endl;
        cout << "bonus amount: " <<bonus<< endl;
        cout << "premium to be paid"<<premium<<endl;
    }

};

    class bankApplication
    {
        public:
        string currentuser;
        int id;
        bool isLogged;
        vector<User> *users;
        vector<loan> *loans;
        vector<insurance> *insurances;
        vector<BankAccount *> *bankAccounts;


        private:
            static bankApplication *instance;
            bankApplication(vector<User> *users,vector<loan> *loans,vector<insurance> *insurances,vector<BankAccount *> *bankAccounts)
                {
                    this->users=users;
                    this->loans=loans;
                    this->insurances=insurances;
                    this->bankAccounts=bankAccounts;
                    isLogged=false;

                }
        public:
            //singleton design pattern
            static bankApplication *getInstance(vector<User> *users, vector<loan> *loans, vector<insurance> *insurances,
                                                vector<BankAccount *> *bankAccounts)
                {
                    if(!instance)
                    {
                      instance = new bankApplication(users, loans, insurances, bankAccounts);
                        return instance;
                    }
                }

    void createAccount()
        {

            int age,mobNo;
            string name,adrress,passwrd;
            string qualification,accname;
            cout<<"enter the user details"<<endl;
            cin>>name;
            cin>>passwrd;
            cin>>age;
            cin>>mobNo;
            cin>>adrress;
            cin>>qualification;
            User ua1;
            ua1.addUser(name,passwrd,age,mobNo,adrress,qualification);
            users->push_back(ua1);
            cout<<"User account for"<<name<<"/tis created sucessfully"<<endl;
        }
       void logIn()
    {
        string username, password;
        cout << "Enter UserName : ";
        cin >> username;
        cout << "Enter Password : ";
        cin >> password;
        for (int i = 0;i<users->size(); i++)
        {
            if (users->at(i).userName == username)
            {
                if (users->at(i).password == password)
                {
                    isLogged = true;
                    currentuser=username;
                    cout << "Succesfully logged in " << currentuser << endl;
                    id = users->at(i).userId;
                    break;
                }
                else
                {
                    throw  bankException(1001,"invalid credentials");
                    break;
                }
            }
        }
    }


    void createBankAccount()
    {
        int userId;
        string name;
        double balance = 0.0;

        for (int i=0;i<users->size(); i++)
        {
            if (users->at(i).userName == currentuser)
            {
                userId = users->at(i).userId;
            }
        }

        for (int i=0;i<bankAccounts->size();i++)
        {
            if (bankAccounts->at(i)->userID== userId)
            {
                throw bankException(4001,"you already have bankAccount cannot create another");
                break;
            }
        }
        int ch;
        BankAccount *accounts;
        cout << "for SavingsAccount 1." << endl;
        cout << "for CurrentAccount 2." << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
               balance=500;
               accounts = new savingsAccount(userId,balance);
               break;

        case 2:
               accounts = new currentAccount(userId,balance);
               break;

       default:
               cout << "Invalid choice." << endl;
               break;
        }
        bankAccounts->push_back(accounts);
        cout << "Bank Account for user\t " <<currentuser << " created " << endl;

    }

    void display()
    {
        int ch;
        cout << "1.FOR CURRENT USER DETAILS " << endl;
        cout << "2.FOR ALL USER DETAILS " << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
               for (int i=0;i<users->size();i++)
               {
                    if (users->at(i).userName == currentuser)
                    {
                       users->at(i).printUser();
                    }

               }
                break;

        case 2:
               for (int j=0;j<users->size();j++)
                {
                    users->at(j).printUser();
                }
                break;
       default:
               cout << "Invalid choice." << endl;
               break;
        }
    }

//function for applying loan;
    void applyLoan()

    {
        loan ln(id);
        ln.addLoan();
        for (int i=0;i<users->size();i++)
        {
            if (users->at(i).userId == id)
            {
                users->at(i).ownsloan = true;
            }
        }
        loans->push_back(ln);
    }
    //functio to pay loan

    void payLoan()
    {
        int amount;
        cout << "Enter the amount: ";
        cin >> amount;
        for (int i = 0; i < bankAccounts->size(); i++)
        {
            if (bankAccounts->at(i)->userID == id)
            {
                try
                {
                    bankAccounts->at(i)->debit(amount);
                }
                catch (bankException e)
                {
                    cout << e.what();
                }
            }
        }
        for (int i = 0; i < loans->size(); i++)
        {
            if (loans->at(i).loanId == id)
            {
                loans->at(i).editloan(amount);
                cout << "Successfully paid " << amount << " to bank." << endl;
            }
            else {
                cout<<"you dont have any loan"<<endl;
                throw bankException(1003,"don't have any Loan");
            }
        }
    }

   // displaying loan details
    void displayLoanDetails()
            {
                for (int i = 0; i < loans->size(); i++)
                {
                    if (loans->at(i).loanId ==id)
                    {
                        loans->at(i).printLoan();
                    }
                    else{
                        cout<<"you dont have any loan"<<endl;;
                        throw bankException(1003,"you don't have any kind of Loan");
                    }
                }
            }
        //BUY INSURANCE FUNCTION
         void buyInsurance()
            {
                insurance ins(id);
                ins.addinsurance();
                for (int i=0;i<users->size();i++)
                {
                    if (users->at(i).userId == id)
                    {
                        users->at(i).ownsinsurance= true;
                    }
                }
                insurances->push_back(ins);
            }

        //FUNNCTION DISPLAYING INSURANCE DETAILS
      void displayInsuranceDetails()
            {
                for (int i = 0; i < insurances->size(); i++)
                {
                    if (insurances->at(i).insuranceId ==id)
                    {
                        insurances->at(i).printInsurance();
                    }
                }
            }
            //FOR PRINTING ACCOUNT STATEMENT
void printAccountStatement()
    {
        if (isLogged)
        {
            for (int i = 0; i < users->size(); i++)
            {
                if (users->at(i).userName == currentuser)
                {
                    for (int j = 0; j < bankAccounts->size(); j++)
                    {
                        if (users->at(i).userId == bankAccounts->at(j)->userID)
                        {
                            cout << "Account statement of " << users->at(i).userName << " is -" << endl; // << bankAccounts->at(j)->balance << endl; // change
                            bankAccounts->at(j)->printAccount();
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "you are not logged in" << endl;
        }
    }

        //FUNCTION TO DEPOSIT AMOUNT
     void depositAmount()
    {
        if (isLogged)
        {
            double amount;
            cout<<"enter the amount to be deposited"<<endl;
            cin>>amount;
            for (int i = 0; i < users->size(); i++)
            {
                if (users->at(i).userName == currentuser)
                {
                    for (int j = 0; j < bankAccounts->size(); j++)
                    {
                        if (users->at(i).userId == bankAccounts->at(j)->userID)
                        {
                            bankAccounts->at(j)->credit(amount);
                            cout << "amount is deposited successfully in"<<""<< users->at(i).userName << " account" << endl;
                            cout<<"balance is"<<bankAccounts->at(i)->accBal<<endl;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "First Login." << endl;
        }
    }

    //FUNCTION TO WITHDRAW AMOUNT
    void withdrawAmount()
    {
        if (isLogged)
        {
            double amount;
            cout<<"enter the amount"<<endl;
            cin>>amount;
            for (int i = 0; i < users->size(); i++)
            {
                if (users->at(i).userName == currentuser)
                {
                    for (int j = 0; j < bankAccounts->size(); j++)
                    {
                        if (users->at(i).userId == bankAccounts->at(j)->userID)
                        {
                            bankAccounts->at(j)->debit(amount);
                            cout << "amount of "<<amount<<" is debited from" << users->at(i).userName << " account successfully" << endl;
                            cout<<"balance is"<<bankAccounts->at(i)->accBal<<endl;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "First Login." << endl;
        }
    }

};


int User::autoUser = 2100; //STATIC VARIBALE AUTO USER INTITIALIZED WHENEVER YOU CREATE NEW USER IT WILL AUTOMATICALLY ASSIGN A USER ID
int BankAccount::autoAccount = 2002;
int BankAccount::noOfTransactions=0; //STATIC VARIBALE AUTO USER INTITIALIZED WHENEVER YOU CREATE NEW BANKACCOUNT IT WILL AUTOMATICALLY CREATEM NEW ACCOUNTNUMBER
bankApplication *bankApplication::instance=0;//SINGLETON VARIABLE INITIALIZED TO ZERO
void intro();

int main()
{
    char ch;
	intro();
        User u1,u2;
        u1.addUser("anand","anand123",23,93428,"kudligi","degree");
        u2.addUser("jithu","jithu123",22,93428,"hubli","puc");


        vector<User> users={u1,u2};

        savingsAccount s1(2100,500.00),s2(2101,4000.00);

        vector<BankAccount*>accounts={&s1,&s2};
        vector<loan>loans;
        vector<insurance>insurances;

        bankApplication *application = application->getInstance(&users,&loans,&insurances,&accounts);
	do
	{
	    //MAIN MENU FOR NON LOGIN USERS
		system("cls");
		cout<<"\n\n\tMAIN MENU";
		cout<<"\n\t01. CREATE USER ACCOUNT";
		cout<<"\n\t02. LOGIN";
		cout<<"\n\t03. CREATE BANKACCOUNT";
		cout<<"\n\t04. PRINT ALL USER DETAILS";
		cout<<"\n\t05. PRINT ACCOUNT STATEMENT";
		cout<<"\n\t06. LOAN";
		cout<<"\n\t07. DEPOSIT AMOUNT";
		cout<<"\n\t08. WITHDRAW AMOUNT";
		cout<<"\n\t09. INSURANCE";
		cout<<"\n\t00. EXIT";
		cout<<"\n\tSelect Your Option (1-10) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
              application->createAccount();//FOR CREATING NEW USER
              cout<<"congratulations"<<endl;
			break;
		case '2':
                try
                {
                 application->logIn();//TO LOGIN IF THE CREDNTIALS ARE NOT VALID IT WILL SHOW RUNTIME ERROR
                }
                catch(bankException e)
                {
                   cout<<e.what();
                }


			break;
		case '3': if(application->isLogged){
                        try{
                        application->createBankAccount();//CREATING BANKACCOUNT FOR ALREADY EXISTING USER
                        }
                            catch(bankException err)
                        {
                            cout<<err.what();
                        }
		          }
		          else{
                    cout<<"you are not logged in "<<endl;
		          }
			    break;

		case '4':
                if(application->isLogged){
                        application->display(); //DISPLAYING USER DEATILS
                            }
                        else{
                            cout<<"you are not logged in"<<endl;
                            }
                         break;

		case '5':
                if (application->isLogged){
                    application->printAccountStatement();//PRITINING CURRENT USER ACCOUNT STATEMENT
                    }
                else{
                        cout << "you are not logged in" << endl;
                    }
                break;

        case '6':
                if(application->isLogged){
                char choice;
                cout<<"choose your preference"<<endl;
                cout<<"a. apply for loan"<<endl;
                cout<<"b. pay loan"<<endl;
                cout<<"c. display loan details"<<endl;
                cin>>choice;
                switch(choice)
                {
                case 'a':
                            if (application->isLogged){
                                application->applyLoan();//LOGGED IN USER CAN APPLY LOAN
                            }
                            else{
                                cout << "you are not logged in" << endl;
                            }
                            break;

                case 'b':
                         if (application->isLogged){
                                try{
                                    application->payLoan();
                                }
                                catch(bankException err2)
                                {
                                    cout<<err2.what();
                                }
                            }
                            else{
                                cout << "you are not logged in" << endl;
                            }
                            break;
                case 'c':
                         if (application->isLogged){
                                try{
                                     application->displayLoanDetails();//DEPLAYS LOAN DETAILS ONLY WHEN USER HAS LOAN
                                }
                                catch(bankException err3)
                                {
                                     cout<<err3.what();
                                }
                            }
                            else{
                                cout << "you are not logged in" << endl;
                            }
                            break;
                }
                }
                else{
                    cout<<"you are not logged in"<<endl;
                }
                break;

        case '7':

                if (application->isLogged){
                    application->depositAmount();//TO DEPOSIT AMOUNT
                }
                else{
                    cout << "you are not logged in" << endl;
                }
                break;

        case '8':

                if (application->isLogged){
                    application->withdrawAmount();  //TO WITHDRAW AMOUNT
                }
                else{
                    cout << "you are not logged in" << endl;
                }
                break;
        case '9':
                        if(application->isLogged){
                        char choice;
                        cout<<"choose your preference"<<endl;
                        cout<<"a. buy insurance"<<endl;
                        cout<<"b. display insurance details"<<endl;
                        cin>>choice;
                        switch(choice)
                        {
                        case 'a':
                                    if (application->isLogged){
                                        application->buyInsurance();
                                    }
                                    else{
                                        cout << "you are not logged in" << endl;
                                    }
                                    break;

                        case 'b':
                                 if (application->isLogged){
                                    application->displayInsuranceDetails();
                                    }
                                    else{
                                        cout << "you are not logged in" << endl;
                                    }
                                    break;
                        }
                        }
                        else{
                            cout<<"you are not logged in"<<endl;
                        }
                        break;

        case '0':
			cout<<"\n\n\tThanks for using bank management system";
			exit(0);
			break;
		    default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='9');

    return 0;
}

        void intro()
        {
            cout << "|) .    _. |      /\\        | *  _  . _ *     _o" << endl;
            cout << "|) /-\\ | | |<    /--\\ |) |) | | (_ /-\\| | () | |" << endl;
            cout << "                         |  |         |               " << endl;
            //cout<<"\n  BANK APPLICATION";
            cout<<"\n MADE BY :Team-03"<<endl;
            cout<<"JITHEDNDRA M";
            cout<<"\nAMIT S NAMAVALI"<<endl;
            cout<<"KLE TECHNOLOGICAL UNIVERSITY"<<endl;
            cout<<"LETS START";
            cin.get();
        }

