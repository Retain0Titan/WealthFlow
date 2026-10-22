#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Structures
struct User {
    char name[50];
    char dob[20];
    char pin[5];
    char email[50];
    int userid;
};

struct Account {
    int Ac_num;
    int userid;
    float Ac_balance;
    char Ac_type[20];
    char Ac_DOO[20];
};

struct Transaction {
    int Trans_ID;
    float amt;
    char DOT[20];
    char type[20];
    int Ac_num;
    char Desc[30];
};

struct Expense {
    float amt;
    int Expen_ID;
    char DOE[20];
    char method[20];
    int category_ID;
    char Desc[30];
};

struct Category {
    int category_ID;
    char category_name[20];
};

// Global Variables
int currentUSERID = 0 ;

// Functions

int generateUserID();
void createUser();
void login();
void main_menu();
void start_page();
void banking_tracker();
void expense_tracker();
void reports();
void search();
void settings();
void logout();
void viewAccount();
void deposit();
void withdraw();
void transfer();
void transHistory();
void addExpense();
void viewExpense();
void editExpense();
void deleteExpense();
void categories();
void accSummary();
void transSummary();
void expenSummary();
void cateSummary();
void IvE();
void profSet();
void changePIN();
void categMana();
void backupData();
void createAcc();
int generateAccID();
int accExists( int Ac_num );

// Helper Functions
int accOwned( int Ac_num );
float getBalance( int Ac_num );
void setBalance( int Ac_num, float newBalance );
int generateTransID();
void saveTransaction( float amt, char DOT[], char type[], int Ac_num, char Desc[] );
int generateExpenID();
void initCategories();
void showCategories();
int categoryExists( int category_ID );
int categoryInUse( int category_ID );
void getCategoryName( int category_ID, char name[] );
int chooseCategory();
void chooseMethod( char method[] );
float categoryTotal( int category_ID );
void copyFile( char source[], char dest[] );

int main(){
    srand(time(NULL));
    initCategories();
    start_page();
    return 0;
}

// Starting Page
void start_page(){
    int startChoice;
        printf("\n============================================");
        printf("\n       WELCOME TO THE BANKING SYSTEM        ");
        printf("\n============================================");
        printf("\n   1.    Create Account                     ");
        printf("\n   2.    Login                              ");
        printf("\n   3.    Exit                               ");
        printf("\n============================================");
        printf("\nEnter the choice : ");
    while (1){
        scanf("%d", &startChoice);

        if ( startChoice == 1 ){
            createUser();
            break;
            
        }
        else if ( startChoice == 2 ){
            login();
            break;
            
        }
        else if ( startChoice == 3 ){
            printf("Thank You for Using Banking System  ");
            break;
        }
        printf("Invalid Choice ! Please enter the choice again :  ");
    }
}
int generateUserID(){
    int userid;
    userid = rand() % 900000 + 100000;
    return userid;
}
void createUser(void){
    struct User u1;
    char tempPin[20];
    FILE *fp;
    fp = fopen("Users.txt","a");

    if ( fp == NULL ){
        printf("Error Opening....");
        return;
    }
    
    printf("\n================================");
    printf("\n         Creating User          ");
    printf("\n================================");

    printf("\nEnter Your Name :");
    scanf(" %s", u1.name);

    printf("Enter Your Date of Birth in the formate (DD/MM/YYYY) :");
    scanf(" %s", u1.dob);

    printf("Enter Your Email :");
    scanf(" %s", u1.email);

    printf("Enter Your Desidered PIN (4 digits) :");
    
    while (1){
        scanf("%19s", tempPin);
        int valid = 1;

        if ( strlen(tempPin) != 4 ){
            valid = 0;
        }
        else{
            for ( int i = 0; i < 4; i++ ){
                if ( tempPin[i] < '0' || tempPin[i] > '9'){
                    valid = 0 ;
                    break;
                }
            }
        }

        if ( valid == 1 ){
            strcpy(u1.pin, tempPin);
            break;
        }
        printf("Invalid PIN ! Please Enter the PIN Again :");
    }
    u1.userid = generateUserID();

    printf("\n--------------USER DETAILS---------------");
    printf("\nUser name : %s", u1.name);
    printf("\nDate of Birth : %s", u1.dob);
    printf("\nEmail ID : %s", u1.email);
    printf("\nDesired PIN : %s", u1.pin);
    printf("\nUser ID : %d", u1.userid);
    printf("\n-----------------------------------------");
    
    fprintf(fp,"%d : %s : %s : %s : %s  \n",u1.userid ,u1.pin, u1.email ,u1.dob ,u1.name);
   
    if ( fclose(fp) == EOF ){
        printf("Error Saving the data....");
    }
    printf("\nSuccesfully Saved the data");
    printf("\n");

    currentUSERID = u1.userid;

    for ( int wait = 0 ; wait < 5 ; wait++ ){
        printf("\nPlease Wait...");
        printf("\n ");
    }
    main_menu();
}
void login(){
    struct User u1;
    FILE *fp;
    int loginId;
    char loginPin[5];
    int found;
    int loginChoice;

    printf("\n=====================================");
    printf("\n             Login Page              ");
    printf("\n=====================================");
    printf("\n  Enter the User ID : ");
    while (1){
        found = 0;

        if (scanf(" %d", &loginId) != 1 ){
            printf("\nInvalid User ID input !");
            scanf("%*s");
            loginId = 0;
        }

        printf("\n  Enter the PIN : ");
        if (scanf(" %4s", loginPin) != 1 ){
            printf("\nInvalid Pin input !");
        }

        if ( strlen(loginPin) != 4 ){
            printf("\nPIN must contain exactly 4 digits ! ");
        }
        else{
            for ( int i =0; i < 4; i++ ){
                if (loginPin[i] < '0' || loginPin[i] > '9' ){
                    printf("\nPIN must contain exactly 4 digits ! ");
                    break;
                }
            }
        }

        fp = fopen("Users.txt","r");

        if ( fp == NULL ){
            printf("\nError Opening....");
            printf("\nNo users found ! Please Create an Account first.");
            start_page();
            return;
        }

        while (fscanf(fp, "%d : %4s : %s : %s : %s ", &u1.userid ,u1.pin ,u1.email ,u1.dob ,u1.name) == 5 ){
            if ( loginId == u1.userid && strcmp(loginPin, u1.pin) == 0 ){
                found = 1 ;
                break;
            }
        }

        fclose(fp);

        if ( found ){
            currentUSERID = u1.userid;
            printf("\n Login Successful ! Welcome %s. ", u1.name);
            main_menu();
            return;
        }
        else{
            printf("\nIncorrect User ID or PIN !");
            printf("\nDo you want to exit the program ?");
            printf("\n  1. Yes  2. No ");
            printf("\nEnter the choice : ");
            while(1){
                scanf("%d",&loginChoice);
                if ( loginChoice == 1 ){
                    start_page();
                    return;
                }
                if ( loginChoice == 2 ){
                    login();
                    return;
                } 
                printf("Enter Valid Choice !");
                
            }
            
        }
    }
}

// Main Menu
void main_menu(){
    int menuChoice;
    printf("\n=====================================");
    printf("\n              Main Menu              ");
    printf("\n=====================================");
    printf("\n  1.  Banking Tracker                ");
    printf("\n  2.  Expense Tracker                ");
    printf("\n  3.  Reports                        ");
    printf("\n  4.  Search                         ");
    printf("\n  5.  Settings                       ");
    printf("\n  6.  LogOut                         ");
    printf("\n=====================================");
    printf("\nEnter the choice : ");
    while (1){
        scanf("%d", &menuChoice);

        if ( menuChoice == 1 ){
            banking_tracker();
            break;
        }
        else if ( menuChoice == 2 ){
            expense_tracker();
            break;
        }
        else if ( menuChoice == 3 ){
            reports();
            break;
        }
        else if ( menuChoice == 4 ){
            search();
            break;
        }
        else if ( menuChoice == 5 ){
            settings();
            break;
        }
        else if ( menuChoice == 6 ){
            logout();
            break;
        }
        printf("Invalid Choice ! Please Enter the Choice Again : ");
    }
}

// Banking Tracker
void banking_tracker(){
    int bankChoice;
    printf("\n======================================");
    printf("\n            Banking Tracker           ");
    printf("\n======================================");
    printf("\n     1.    Create Account             ");
    printf("\n     2.    View Account               ");
    printf("\n     3.    Deposit                    ");
    printf("\n     4.    Withdrawal                 ");
    printf("\n     5.    Transfer                   ");
    printf("\n     6.    Transaction History        ");
    printf("\n     7.    Back                       ");
    printf("\n======================================");
    printf("\nEnter the choice : ");
    while (1){
        scanf("%d", &bankChoice);

        if ( bankChoice == 1 ){
            createAcc();
            break;
        }
        else if ( bankChoice == 2 ){
            viewAccount();
            break;
        }
        else if ( bankChoice == 3 ){
            deposit();
            break;
        }
        else if ( bankChoice == 4 ){
            withdraw();
            break;
        }
        else if ( bankChoice == 5 ){
            transfer();
            break;
        }
        else if ( bankChoice == 6 ){
            transHistory();
            break;
        }
        else if ( bankChoice == 7 ){
            main_menu();
            
            break;
        }
        printf("Invalid Choice ! Please Enter Valid Choice : ");
    }

}
int generateAccID(){
    int Ac_num;
    Ac_num = rand() % 900000 + 100000;
    return Ac_num;
}
int accExists( int Ac_num ){
    FILE *fp;
    struct Account temp;

    fp = fopen("Accounts.txt", "r");

    if (fp == NULL)
    {
        return 0;
    }

    while (fscanf(fp, "%d %d %f %19s %19s",
                  &temp.Ac_num,
                  &temp.userid,
                  &temp.Ac_balance,
                  temp.Ac_type,
                  temp.Ac_DOO) == 5)
    {
        if (temp.Ac_num == Ac_num)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
void createAcc(){
    struct Account acc;

    if ( currentUSERID == 0 ){
        printf("\nERROR ! Please Login first ! ");
        return;
    }

    acc.userid = currentUSERID ;
    acc.Ac_balance = 0.0f ;
    
    acc.Ac_num = generateAccID();
    
    while ( accExists( acc.Ac_num )){
        acc.Ac_num = generateAccID();
    }
    
    int accChoice;
    
    printf("\n================================");
    printf("\n       SELECT ACCOUNT TYPE");
    printf("\n================================");
    printf("\n1. Savings Account");
    printf("\n2. Current Account");
    printf("\nEnter your choice: ");
    
    while(1){
        scanf("%d", &accChoice);

        if ( accChoice == 1 || accChoice == 2 ){
            break;
        }
        printf("Invalid Choice ! Please Enter Valid Choice : ");
    }

    if (accChoice == 1){
        strcpy(acc.Ac_type, "Savings");
    }
    else{
        strcpy(acc.Ac_type, "Current");
    }
    printf("\nAccount Type: %s\n", acc.Ac_type);

       
    printf("\nEnter Account Opening Date (DD/MM/YYYY): ");
    scanf("%19s", acc.Ac_DOO);

    FILE *fp;
    fp = fopen("Accounts.txt", "a");

    if (fp == NULL){
        printf("\nERROR! Unable to open Accounts.txt!\n");
        return;
    }

    if (fprintf(fp, "%d %d %.2f %s %s\n",
                acc.Ac_num,
                acc.userid,
                acc.Ac_balance,
                acc.Ac_type,
                acc.Ac_DOO) < 0)
    {
        printf("\nERROR! Failed to save account!\n");
        fclose(fp);
        return;
    }

    if (fclose(fp) == EOF)
    {
        printf("\nERROR! Problem closing Accounts.txt!\n");
        return;
    }

    printf("\n================================");
    printf("\n      ACCOUNT CREATED");
    printf("\n================================");
    printf("\nUser ID: %d", acc.userid);
    printf("\nAccount Number: %d", acc.Ac_num);
    printf("\nAccount Type: %s", acc.Ac_type);
    printf("\nInitial Balance: %.2f", acc.Ac_balance);
    printf("\nOpening Date: %s", acc.Ac_DOO);
    printf("\n================================\n");

    banking_tracker();
}

// Expense Tracker
void expense_tracker(){
    int expenChoice;
    printf("\n======================================");
    printf("\n            Expense Tracker           ");
    printf("\n======================================");
    printf("\n     1.    Add Expense                ");
    printf("\n     2.    View Expense               ");
    printf("\n     3.    Edit Expense               ");
    printf("\n     4.    Delete Expense             ");
    printf("\n     5.    Categories                 ");
    printf("\n     6.    Back                       ");
    printf("\n======================================");
    printf("\nEnter the choice : ");

    while (1){
        scanf("%d", &expenChoice);

        if ( expenChoice == 1 ){
            addExpense();
            break;
        }
        else if ( expenChoice == 2 ){
            viewExpense();
            break;
        }
        else if ( expenChoice == 3 ){
            editExpense();
            break;
        }
        else if ( expenChoice == 4 ){
            deleteExpense();
            break;
        }
        else if ( expenChoice == 5 ){
            categories();
            break;
        }
        else if ( expenChoice == 6 ){
            main_menu();
            break;
        }
        printf("Invalid Choice ! Please Enter Valid Choice : ");
    }
}

// Reports
void reports(){
    int reportChoice;
    printf("\n====================================");
    printf("\n              REPORTS               ");
    printf("\n====================================");
    printf("\n    1.   Account Summary            ");
    printf("\n    2.   Transaction Summary        ");
    printf("\n    3.   Expense Summary            ");
    printf("\n    4.   Category-wise Spending     ");
    printf("\n    5.   Income vs Expense          ");
    printf("\n    6.   Back                       ");
    printf("\n====================================");
    printf("\n Enter the Choice :");

    while (1){
        scanf("%d", &reportChoice);

        if ( reportChoice == 1 ){
            accSummary();
            break;
        }
        else if ( reportChoice == 2 ){
            transSummary();
            break;
        }
        else if ( reportChoice == 3 ){
            expenSummary();
            break;
        }
        else if ( reportChoice == 4 ){
            cateSummary();
            break;
        }
        else if ( reportChoice == 5 ){
            IvE();
            break;
        }
        else if ( reportChoice == 6 ){
            main_menu();
            break;
        }
        printf("Invalid Choice ! Please Enter The Choice Again : ");
    }

}

// Search
void search(){
    int searchChoice;
    FILE *fp;
    struct Transaction t;
    struct Expense e;
    int uid;
    int found = 0;
    int searchId;
    char searchText[30];
    char searchDate[20];
    char catName[20];

    printf("\n===================================");
    printf("\n              SEARCH               ");
    printf("\n===================================");
    printf("\n   1.   Search by Transaction      ");
    printf("\n   2.   Search Expenses            ");
    printf("\n   3.   Search by Category         ");
    printf("\n   4.   Search by Date             ");
    printf("\n   5.   Back                       ");
    printf("\n===================================");
    printf("\n  Enter the Choice : ");

    while (1){
        scanf("%d", &searchChoice);

        if ( searchChoice == 1 ){
            printf("\nEnter the Transaction ID : ");
            scanf("%d", &searchId);

            fp = fopen("Transactions.txt", "r");

            if ( fp != NULL ){
                while ( fscanf(fp, "%d %f %19s %19s %d %29s", &t.Trans_ID, &t.amt, t.DOT, t.type, &t.Ac_num, t.Desc) == 6 ){
                    if ( t.Trans_ID == searchId && accOwned(t.Ac_num) ){
                        printf("\n--------TRANSACTION FOUND--------");
                        printf("\nTransaction ID : %d", t.Trans_ID);
                        printf("\nAmount : %.2f", t.amt);
                        printf("\nDate : %s", t.DOT);
                        printf("\nType : %s", t.type);
                        printf("\nAccount Number : %d", t.Ac_num);
                        printf("\nDescription : %s", t.Desc);
                        printf("\n---------------------------------\n");
                        found = 1;
                    }
                }
                fclose(fp);
            }

            if ( found == 0 ){
                printf("\nNo Transaction Found !\n");
            }
            search();
            break;
        }
        else if ( searchChoice == 2 ){
            printf("\nEnter the Keyword to search in Description : ");
            scanf("%29s", searchText);

            fp = fopen("Expenses.txt", "r");

            if ( fp != NULL ){
                printf("\n%-8s %-10s %-12s %-10s %-12s %s", "ID", "Amount", "Date", "Method", "Category", "Description");
                while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
                    if ( uid == currentUSERID && strstr(e.Desc, searchText) != NULL ){
                        getCategoryName(e.category_ID, catName);
                        printf("\n%-8d %-10.2f %-12s %-10s %-12s %s", e.Expen_ID, e.amt, e.DOE, e.method, catName, e.Desc);
                        found = 1;
                    }
                }
                fclose(fp);
            }

            if ( found == 0 ){
                printf("\nNo Expense Found !");
            }
            printf("\n");
            search();
            break;
        }
        else if ( searchChoice == 3 ){
            showCategories();
            printf("\nEnter the Category ID : ");
            scanf("%d", &searchId);

            fp = fopen("Expenses.txt", "r");

            if ( fp != NULL ){
                printf("\n%-8s %-10s %-12s %-10s %s", "ID", "Amount", "Date", "Method", "Description");
                while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
                    if ( uid == currentUSERID && e.category_ID == searchId ){
                        printf("\n%-8d %-10.2f %-12s %-10s %s", e.Expen_ID, e.amt, e.DOE, e.method, e.Desc);
                        found = 1;
                    }
                }
                fclose(fp);
            }

            if ( found == 0 ){
                printf("\nNo Expense Found in this Category !");
            }
            printf("\n");
            search();
            break;
        }
        else if ( searchChoice == 4 ){
            printf("\nEnter the Date (DD/MM/YYYY) : ");
            scanf("%19s", searchDate);

            printf("\n--------TRANSACTIONS ON %s--------", searchDate);
            fp = fopen("Transactions.txt", "r");

            if ( fp != NULL ){
                while ( fscanf(fp, "%d %f %19s %19s %d %29s", &t.Trans_ID, &t.amt, t.DOT, t.type, &t.Ac_num, t.Desc) == 6 ){
                    if ( strcmp(t.DOT, searchDate) == 0 && accOwned(t.Ac_num) ){
                        printf("\n%-8d %-10.2f %-14s Account : %-8d %s", t.Trans_ID, t.amt, t.type, t.Ac_num, t.Desc);
                        found = 1;
                    }
                }
                fclose(fp);
            }

            if ( found == 0 ){
                printf("\nNo Transactions Found !");
            }

            found = 0;
            printf("\n\n--------EXPENSES ON %s--------", searchDate);
            fp = fopen("Expenses.txt", "r");

            if ( fp != NULL ){
                while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
                    if ( uid == currentUSERID && strcmp(e.DOE, searchDate) == 0 ){
                        getCategoryName(e.category_ID, catName);
                        printf("\n%-8d %-10.2f %-10s %-12s %s", e.Expen_ID, e.amt, e.method, catName, e.Desc);
                        found = 1;
                    }
                }
                fclose(fp);
            }

            if ( found == 0 ){
                printf("\nNo Expenses Found !");
            }
            printf("\n");
            search();
            break;
        }
        else if ( searchChoice == 5 ){
            main_menu();
            break;
        }
        printf("Invalid Choice ! Please Enter The Valid Choice :");
    }
}

// Settings
void settings(){
    int settChoice;
    printf("\n===================================");
    printf("\n             SETTING               ");
    printf("\n===================================");
    printf("\n      1.  Profile Settings         ");
    printf("\n      2.  Change PIN               ");
    printf("\n      3.  Category Management      ");
    printf("\n      4.  Backup Data              ");
    printf("\n      5.  Back                     ");
    printf("\n===================================");
    printf("\n  Enter The Choice :  ");

    while (1){
        scanf("%d", &settChoice );

        if ( settChoice == 1 ){
            profSet();
            break;
        }
        else if ( settChoice == 2 ){
            changePIN();
            break;
        }
        else if ( settChoice == 3 ){
            categMana();
            break;
        }
        else if ( settChoice == 4 ){
            backupData();
            break;
        }
        else if ( settChoice == 5 ){
            main_menu();
            break;
        }
        printf("Invalid Choice ! Please Enter The Choice Again : ");
    }

}

// Log Out
void logout(){
    printf("Logging Out....");
    currentUSERID = 0;
    for ( int wait = 0 ; wait < 5 ; wait++ ){
        printf("\nPlease Wait....");
        printf("\n ");
    }
    start_page();
}

// In-Function

// Banking Tracker Functions
void viewAccount(){
    FILE *fp;
    struct Account acc;
    int count = 0;

    printf("\n================================================================");
    printf("\n                        YOUR ACCOUNTS                           ");
    printf("\n================================================================");

    fp = fopen("Accounts.txt", "r");

    if ( fp != NULL ){
        printf("\n%-12s %-12s %-12s %s", "Account No", "Type", "Balance", "Opening Date");
        while ( fscanf(fp, "%d %d %f %19s %19s", &acc.Ac_num, &acc.userid, &acc.Ac_balance, acc.Ac_type, acc.Ac_DOO) == 5 ){
            if ( acc.userid == currentUSERID ){
                printf("\n%-12d %-12s %-12.2f %s", acc.Ac_num, acc.Ac_type, acc.Ac_balance, acc.Ac_DOO);
                count++;
            }
        }
        fclose(fp);
    }

    if ( count == 0 ){
        printf("\nNo Accounts Found ! Please Create an Account first.");
    }
    printf("\n================================================================\n");

    banking_tracker();
}
void deposit(){
    int Ac_num;
    float amt;
    char date[20];
    char desc[30];

    printf("\n================================");
    printf("\n            DEPOSIT             ");
    printf("\n================================");
    printf("\nEnter the Account Number : ");
    scanf("%d", &Ac_num);

    if ( accOwned(Ac_num) == 0 ){
        printf("\nERROR ! Account not found !\n");
        banking_tracker();
        return;
    }

    printf("Enter the Amount to Deposit : ");
    scanf("%f", &amt);

    if ( amt <= 0 ){
        printf("\nERROR ! Amount must be greater than 0 !\n");
        banking_tracker();
        return;
    }

    printf("Enter the Date (DD/MM/YYYY) : ");
    scanf("%19s", date);

    printf("Enter the Description (one word) : ");
    scanf("%29s", desc);

    setBalance(Ac_num, getBalance(Ac_num) + amt);
    saveTransaction(amt, date, "Deposit", Ac_num, desc);

    printf("\nDeposit Successful !");
    printf("\nNew Balance : %.2f\n", getBalance(Ac_num));

    banking_tracker();
}
void withdraw(){
    int Ac_num;
    float amt;
    char date[20];
    char desc[30];

    printf("\n================================");
    printf("\n           WITHDRAWAL           ");
    printf("\n================================");
    printf("\nEnter the Account Number : ");
    scanf("%d", &Ac_num);

    if ( accOwned(Ac_num) == 0 ){
        printf("\nERROR ! Account not found !\n");
        banking_tracker();
        return;
    }

    printf("Enter the Amount to Withdraw : ");
    scanf("%f", &amt);

    if ( amt <= 0 ){
        printf("\nERROR ! Amount must be greater than 0 !\n");
        banking_tracker();
        return;
    }

    if ( amt > getBalance(Ac_num) ){
        printf("\nERROR ! Insufficient Balance !");
        printf("\nAvailable Balance : %.2f\n", getBalance(Ac_num));
        banking_tracker();
        return;
    }

    printf("Enter the Date (DD/MM/YYYY) : ");
    scanf("%19s", date);

    printf("Enter the Description (one word) : ");
    scanf("%29s", desc);

    setBalance(Ac_num, getBalance(Ac_num) - amt);
    saveTransaction(amt, date, "Withdrawal", Ac_num, desc);

    printf("\nWithdrawal Successful !");
    printf("\nNew Balance : %.2f\n", getBalance(Ac_num));

    banking_tracker();
}
void transfer(){
    int fromAc;
    int toAc;
    float amt;
    char date[20];

    printf("\n================================");
    printf("\n            TRANSFER            ");
    printf("\n================================");
    printf("\nEnter Your Account Number : ");
    scanf("%d", &fromAc);

    if ( accOwned(fromAc) == 0 ){
        printf("\nERROR ! Account not found !\n");
        banking_tracker();
        return;
    }

    printf("Enter the Receiver's Account Number : ");
    scanf("%d", &toAc);

    if ( accExists(toAc) == 0 ){
        printf("\nERROR ! Receiver Account not found !\n");
        banking_tracker();
        return;
    }

    if ( fromAc == toAc ){
        printf("\nERROR ! Cannot transfer to the same account !\n");
        banking_tracker();
        return;
    }

    printf("Enter the Amount to Transfer : ");
    scanf("%f", &amt);

    if ( amt <= 0 ){
        printf("\nERROR ! Amount must be greater than 0 !\n");
        banking_tracker();
        return;
    }

    if ( amt > getBalance(fromAc) ){
        printf("\nERROR ! Insufficient Balance !");
        printf("\nAvailable Balance : %.2f\n", getBalance(fromAc));
        banking_tracker();
        return;
    }

    printf("Enter the Date (DD/MM/YYYY) : ");
    scanf("%19s", date);

    setBalance(fromAc, getBalance(fromAc) - amt);
    setBalance(toAc, getBalance(toAc) + amt);
    saveTransaction(amt, date, "Transfer-Out", fromAc, "Transfer");
    saveTransaction(amt, date, "Transfer-In", toAc, "Transfer");

    printf("\nTransfer Successful !");
    printf("\nYour New Balance : %.2f\n", getBalance(fromAc));

    banking_tracker();
}
void transHistory(){
    FILE *fp;
    struct Transaction t;
    int count = 0;

    printf("\n================================================================");
    printf("\n                      TRANSACTION HISTORY                       ");
    printf("\n================================================================");

    fp = fopen("Transactions.txt", "r");

    if ( fp != NULL ){
        printf("\n%-8s %-10s %-12s %-14s %-10s %s", "ID", "Amount", "Date", "Type", "Account", "Description");
        while ( fscanf(fp, "%d %f %19s %19s %d %29s", &t.Trans_ID, &t.amt, t.DOT, t.type, &t.Ac_num, t.Desc) == 6 ){
            if ( accOwned(t.Ac_num) ){
                printf("\n%-8d %-10.2f %-12s %-14s %-10d %s", t.Trans_ID, t.amt, t.DOT, t.type, t.Ac_num, t.Desc);
                count++;
            }
        }
        fclose(fp);
    }

    if ( count == 0 ){
        printf("\nNo Transactions Found !");
    }
    printf("\n================================================================\n");

    banking_tracker();
}

// Expense Tracker Functions
void addExpense(){
    FILE *fp;
    struct Expense e;

    printf("\n================================");
    printf("\n          ADD EXPENSE           ");
    printf("\n================================");
    printf("\nEnter the Amount : ");
    scanf("%f", &e.amt);

    if ( e.amt <= 0 ){
        printf("\nERROR ! Amount must be greater than 0 !\n");
        expense_tracker();
        return;
    }

    printf("Enter the Date (DD/MM/YYYY) : ");
    scanf("%19s", e.DOE);

    chooseMethod(e.method);
    e.category_ID = chooseCategory();

    printf("Enter the Description (one word) : ");
    scanf("%29s", e.Desc);

    e.Expen_ID = generateExpenID();

    fp = fopen("Expenses.txt", "a");

    if ( fp == NULL ){
        printf("\nERROR! Unable to open Expenses.txt!\n");
        expense_tracker();
        return;
    }

    fprintf(fp, "%d %d %.2f %s %s %d %s\n", currentUSERID, e.Expen_ID, e.amt, e.DOE, e.method, e.category_ID, e.Desc);

    if ( fclose(fp) == EOF ){
        printf("\nERROR! Problem closing Expenses.txt!\n");
    }

    printf("\nExpense Added Successfully ! Expense ID : %d\n", e.Expen_ID);

    expense_tracker();
}
void editExpense(){
    FILE *fp;
    FILE *tp;
    struct Expense e;
    int uid;
    int editId;
    int found = 0;

    printf("\n================================");
    printf("\n         EDIT EXPENSE           ");
    printf("\n================================");
    printf("\nEnter the Expense ID to Edit : ");
    scanf("%d", &editId);

    fp = fopen("Expenses.txt", "r");

    if ( fp == NULL ){
        printf("\nNo Expenses Found !\n");
        expense_tracker();
        return;
    }

    tp = fopen("Temp.txt", "w");

    if ( tp == NULL ){
        printf("\nERROR! Unable to edit the Expense !\n");
        fclose(fp);
        expense_tracker();
        return;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
        if ( uid == currentUSERID && e.Expen_ID == editId ){
            found = 1;

            printf("\nEnter the New Amount : ");
            scanf("%f", &e.amt);

            printf("Enter the New Date (DD/MM/YYYY) : ");
            scanf("%19s", e.DOE);

            chooseMethod(e.method);
            e.category_ID = chooseCategory();

            printf("Enter the New Description (one word) : ");
            scanf("%29s", e.Desc);
        }
        fprintf(tp, "%d %d %.2f %s %s %d %s\n", uid, e.Expen_ID, e.amt, e.DOE, e.method, e.category_ID, e.Desc);
    }

    fclose(fp);
    fclose(tp);
    remove("Expenses.txt");
    rename("Temp.txt", "Expenses.txt");

    if ( found ){
        printf("\nExpense Edited Successfully !\n");
    }
    else{
        printf("\nExpense ID not found !\n");
    }

    expense_tracker();
}
void viewExpense(){
    FILE *fp;
    struct Expense e;
    int uid;
    int count = 0;
    float total = 0;
    char catName[20];

    printf("\n================================================================");
    printf("\n                        YOUR EXPENSES                           ");
    printf("\n================================================================");

    fp = fopen("Expenses.txt", "r");

    if ( fp != NULL ){
        printf("\n%-8s %-10s %-12s %-10s %-12s %s", "ID", "Amount", "Date", "Method", "Category", "Description");
        while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
            if ( uid == currentUSERID ){
                getCategoryName(e.category_ID, catName);
                printf("\n%-8d %-10.2f %-12s %-10s %-12s %s", e.Expen_ID, e.amt, e.DOE, e.method, catName, e.Desc);
                total = total + e.amt;
                count++;
            }
        }
        fclose(fp);
    }

    if ( count == 0 ){
        printf("\nNo Expenses Found !");
    }
    else{
        printf("\n----------------------------------------------------------------");
        printf("\nTotal Expenses : %.2f", total);
    }
    printf("\n================================================================\n");

    expense_tracker();
}
void deleteExpense(){
    FILE *fp;
    FILE *tp;
    struct Expense e;
    int uid;
    int deleteId;
    int found = 0;

    printf("\n================================");
    printf("\n        DELETE EXPENSE          ");
    printf("\n================================");
    printf("\nEnter the Expense ID to Delete : ");
    scanf("%d", &deleteId);

    fp = fopen("Expenses.txt", "r");

    if ( fp == NULL ){
        printf("\nNo Expenses Found !\n");
        expense_tracker();
        return;
    }

    tp = fopen("Temp.txt", "w");

    if ( tp == NULL ){
        printf("\nERROR! Unable to delete the Expense !\n");
        fclose(fp);
        expense_tracker();
        return;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
        if ( uid == currentUSERID && e.Expen_ID == deleteId ){
            found = 1;
        }
        else{
            fprintf(tp, "%d %d %.2f %s %s %d %s\n", uid, e.Expen_ID, e.amt, e.DOE, e.method, e.category_ID, e.Desc);
        }
    }

    fclose(fp);
    fclose(tp);
    remove("Expenses.txt");
    rename("Temp.txt", "Expenses.txt");

    if ( found ){
        printf("\nExpense Deleted Successfully !\n");
    }
    else{
        printf("\nExpense ID not found !\n");
    }

    expense_tracker();
}
void categories(){
    printf("\n================================");
    printf("\n          CATEGORIES            ");
    printf("\n================================");
    showCategories();
    printf("\n================================\n");

    expense_tracker();
}

// Report Functions
void accSummary(){
    FILE *fp;
    struct Account acc;
    int count = 0;
    float total = 0;

    printf("\n================================================================");
    printf("\n                        ACCOUNT SUMMARY                         ");
    printf("\n================================================================");

    fp = fopen("Accounts.txt", "r");

    if ( fp != NULL ){
        printf("\n%-12s %-12s %-12s %s", "Account No", "Type", "Balance", "Opening Date");
        while ( fscanf(fp, "%d %d %f %19s %19s", &acc.Ac_num, &acc.userid, &acc.Ac_balance, acc.Ac_type, acc.Ac_DOO) == 5 ){
            if ( acc.userid == currentUSERID ){
                printf("\n%-12d %-12s %-12.2f %s", acc.Ac_num, acc.Ac_type, acc.Ac_balance, acc.Ac_DOO);
                total = total + acc.Ac_balance;
                count++;
            }
        }
        fclose(fp);
    }

    if ( count == 0 ){
        printf("\nNo Accounts Found !");
    }
    else{
        printf("\n----------------------------------------------------------------");
        printf("\nTotal Accounts : %d", count);
        printf("\nTotal Balance  : %.2f", total);
    }
    printf("\n================================================================\n");

    reports();
}
void transSummary(){
    FILE *fp;
    struct Transaction t;
    int count = 0;
    float deposits = 0;
    float withdrawals = 0;
    float transOut = 0;
    float transIn = 0;

    printf("\n================================================================");
    printf("\n                      TRANSACTION SUMMARY                       ");
    printf("\n================================================================");

    fp = fopen("Transactions.txt", "r");

    if ( fp != NULL ){
        while ( fscanf(fp, "%d %f %19s %19s %d %29s", &t.Trans_ID, &t.amt, t.DOT, t.type, &t.Ac_num, t.Desc) == 6 ){
            if ( accOwned(t.Ac_num) ){
                if ( strcmp(t.type, "Deposit") == 0 ){
                    deposits = deposits + t.amt;
                }
                else if ( strcmp(t.type, "Withdrawal") == 0 ){
                    withdrawals = withdrawals + t.amt;
                }
                else if ( strcmp(t.type, "Transfer-Out") == 0 ){
                    transOut = transOut + t.amt;
                }
                else if ( strcmp(t.type, "Transfer-In") == 0 ){
                    transIn = transIn + t.amt;
                }
                count++;
            }
        }
        fclose(fp);
    }

    if ( count == 0 ){
        printf("\nNo Transactions Found !");
    }
    else{
        printf("\nTotal Transactions : %d", count);
        printf("\nTotal Deposits     : %.2f", deposits);
        printf("\nTotal Withdrawals  : %.2f", withdrawals);
        printf("\nTotal Transfer Out : %.2f", transOut);
        printf("\nTotal Transfer In  : %.2f", transIn);
    }
    printf("\n================================================================\n");

    reports();
}
void expenSummary(){
    FILE *fp;
    struct Expense e;
    int uid;
    int count = 0;
    float total = 0;
    float highest = 0;

    printf("\n================================================================");
    printf("\n                       EXPENSE SUMMARY                          ");
    printf("\n================================================================");

    fp = fopen("Expenses.txt", "r");

    if ( fp != NULL ){
        while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
            if ( uid == currentUSERID ){
                total = total + e.amt;
                if ( e.amt > highest ){
                    highest = e.amt;
                }
                count++;
            }
        }
        fclose(fp);
    }

    if ( count == 0 ){
        printf("\nNo Expenses Found !");
    }
    else{
        printf("\nNumber of Expenses : %d", count);
        printf("\nTotal Expenses     : %.2f", total);
        printf("\nAverage Expense    : %.2f", total / count);
        printf("\nHighest Expense    : %.2f", highest);
    }
    printf("\n================================================================\n");

    reports();
}
void cateSummary(){
    FILE *fp;
    struct Category c;
    float total;
    float grandTotal = 0;

    printf("\n================================================================");
    printf("\n                   CATEGORY-WISE SPENDING                       ");
    printf("\n================================================================");

    fp = fopen("Categories.txt", "r");

    if ( fp != NULL ){
        printf("\n%-8s %-15s %s", "ID", "Category", "Total Spent");
        while ( fscanf(fp, "%d %19s", &c.category_ID, c.category_name) == 2 ){
            total = categoryTotal(c.category_ID);
            printf("\n%-8d %-15s %.2f", c.category_ID, c.category_name, total);
            grandTotal = grandTotal + total;
        }
        fclose(fp);
        printf("\n----------------------------------------------------------------");
        printf("\nGrand Total : %.2f", grandTotal);
    }
    else{
        printf("\nNo Categories Found !");
    }
    printf("\n================================================================\n");

    reports();
}
void IvE(){
    FILE *fp;
    struct Transaction t;
    struct Expense e;
    int uid;
    float income = 0;
    float expense = 0;

    printf("\n================================================================");
    printf("\n                     INCOME VS EXPENSE                          ");
    printf("\n================================================================");

    fp = fopen("Transactions.txt", "r");

    if ( fp != NULL ){
        while ( fscanf(fp, "%d %f %19s %19s %d %29s", &t.Trans_ID, &t.amt, t.DOT, t.type, &t.Ac_num, t.Desc) == 6 ){
            if ( accOwned(t.Ac_num) && strcmp(t.type, "Deposit") == 0 ){
                income = income + t.amt;
            }
        }
        fclose(fp);
    }

    fp = fopen("Expenses.txt", "r");

    if ( fp != NULL ){
        while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
            if ( uid == currentUSERID ){
                expense = expense + e.amt;
            }
        }
        fclose(fp);
    }

    printf("\nTotal Income (Deposits) : %.2f", income);
    printf("\nTotal Expenses          : %.2f", expense);
    printf("\n----------------------------------------------------------------");

    if ( income >= expense ){
        printf("\nSavings                 : %.2f", income - expense);
    }
    else{
        printf("\nOverspent By            : %.2f", expense - income);
    }
    printf("\n================================================================\n");

    reports();
}

// Settings Functions
void profSet(){
    FILE *fp;
    FILE *tp;
    struct User u1;
    int profChoice;
    char newValue[50];

    printf("\n===================================");
    printf("\n         PROFILE SETTINGS          ");
    printf("\n===================================");

    fp = fopen("Users.txt", "r");

    if ( fp == NULL ){
        printf("\nError Opening....\n");
        settings();
        return;
    }

    while ( fscanf(fp, "%d : %4s : %s : %s : %s ", &u1.userid, u1.pin, u1.email, u1.dob, u1.name) == 5 ){
        if ( u1.userid == currentUSERID ){
            printf("\nUser name : %s", u1.name);
            printf("\nDate of Birth : %s", u1.dob);
            printf("\nEmail ID : %s", u1.email);
            printf("\nUser ID : %d", u1.userid);
            break;
        }
    }
    fclose(fp);

    printf("\n===================================");
    printf("\n      1.  Edit Name                ");
    printf("\n      2.  Edit Email               ");
    printf("\n      3.  Back                     ");
    printf("\n===================================");
    printf("\n  Enter The Choice :  ");

    while (1){
        scanf("%d", &profChoice);

        if ( profChoice == 1 || profChoice == 2 ){
            if ( profChoice == 1 ){
                printf("Enter the New Name : ");
            }
            else{
                printf("Enter the New Email : ");
            }
            scanf(" %49s", newValue);

            fp = fopen("Users.txt", "r");
            tp = fopen("Temp.txt", "w");

            if ( fp == NULL || tp == NULL ){
                printf("\nERROR! Unable to update the profile !\n");
                settings();
                break;
            }

            while ( fscanf(fp, "%d : %4s : %s : %s : %s ", &u1.userid, u1.pin, u1.email, u1.dob, u1.name) == 5 ){
                if ( u1.userid == currentUSERID ){
                    if ( profChoice == 1 ){
                        strcpy(u1.name, newValue);
                    }
                    else{
                        strcpy(u1.email, newValue);
                    }
                }
                fprintf(tp, "%d : %s : %s : %s : %s  \n", u1.userid, u1.pin, u1.email, u1.dob, u1.name);
            }

            fclose(fp);
            fclose(tp);
            remove("Users.txt");
            rename("Temp.txt", "Users.txt");

            printf("\nProfile Updated Successfully !\n");
            settings();
            break;
        }
        else if ( profChoice == 3 ){
            settings();
            break;
        }
        printf("Invalid Choice ! Please Enter The Choice Again : ");
    }
}
void changePIN(){
    FILE *fp;
    FILE *tp;
    struct User u1;
    char oldPin[20];
    char newPin[20];
    char savedPin[5];
    int valid;

    printf("\n===================================");
    printf("\n            CHANGE PIN             ");
    printf("\n===================================");

    fp = fopen("Users.txt", "r");

    if ( fp == NULL ){
        printf("\nError Opening....\n");
        settings();
        return;
    }

    while ( fscanf(fp, "%d : %4s : %s : %s : %s ", &u1.userid, u1.pin, u1.email, u1.dob, u1.name) == 5 ){
        if ( u1.userid == currentUSERID ){
            strcpy(savedPin, u1.pin);
            break;
        }
    }
    fclose(fp);

    printf("\nEnter Your Current PIN : ");
    scanf("%19s", oldPin);

    if ( strcmp(oldPin, savedPin) != 0 ){
        printf("\nIncorrect PIN !\n");
        settings();
        return;
    }

    printf("Enter Your New PIN (4 digits) : ");

    while (1){
        scanf("%19s", newPin);
        valid = 1;

        if ( strlen(newPin) != 4 ){
            valid = 0;
        }
        else{
            for ( int i = 0; i < 4; i++ ){
                if ( newPin[i] < '0' || newPin[i] > '9' ){
                    valid = 0;
                    break;
                }
            }
        }

        if ( valid == 1 ){
            break;
        }
        printf("Invalid PIN ! Please Enter the PIN Again : ");
    }

    fp = fopen("Users.txt", "r");
    tp = fopen("Temp.txt", "w");

    if ( fp == NULL || tp == NULL ){
        printf("\nERROR! Unable to change the PIN !\n");
        settings();
        return;
    }

    while ( fscanf(fp, "%d : %4s : %s : %s : %s ", &u1.userid, u1.pin, u1.email, u1.dob, u1.name) == 5 ){
        if ( u1.userid == currentUSERID ){
            strcpy(u1.pin, newPin);
        }
        fprintf(tp, "%d : %s : %s : %s : %s  \n", u1.userid, u1.pin, u1.email, u1.dob, u1.name);
    }

    fclose(fp);
    fclose(tp);
    remove("Users.txt");
    rename("Temp.txt", "Users.txt");

    printf("\nPIN Changed Successfully !\n");

    settings();
}
void categMana(){
    FILE *fp;
    FILE *tp;
    struct Category c;
    int categChoice;
    int categId;
    int found = 0;
    char newName[20];

    printf("\n===================================");
    printf("\n        CATEGORY MANAGEMENT        ");
    printf("\n===================================");
    printf("\n      1.  Add Category             ");
    printf("\n      2.  Rename Category          ");
    printf("\n      3.  Delete Category          ");
    printf("\n      4.  View Categories          ");
    printf("\n      5.  Back                     ");
    printf("\n===================================");
    printf("\n  Enter The Choice :  ");

    while (1){
        scanf("%d", &categChoice);

        if ( categChoice == 1 ){
            printf("Enter the New Category Name (one word) : ");
            scanf("%19s", newName);

            fp = fopen("Categories.txt", "r");
            c.category_ID = 0;

            if ( fp != NULL ){
                while ( fscanf(fp, "%d %19s", &categId, c.category_name) == 2 ){
                    if ( categId > c.category_ID ){
                        c.category_ID = categId;
                    }
                }
                fclose(fp);
            }
            c.category_ID = c.category_ID + 1;

            fp = fopen("Categories.txt", "a");

            if ( fp == NULL ){
                printf("\nERROR! Unable to open Categories.txt!\n");
            }
            else{
                fprintf(fp, "%d %s\n", c.category_ID, newName);
                fclose(fp);
                printf("\nCategory Added Successfully ! Category ID : %d\n", c.category_ID);
            }
            categMana();
            break;
        }
        else if ( categChoice == 2 ){
            showCategories();
            printf("\nEnter the Category ID to Rename : ");
            scanf("%d", &categId);

            if ( categoryExists(categId) == 0 ){
                printf("\nCategory ID not found !\n");
                categMana();
                break;
            }

            printf("Enter the New Name (one word) : ");
            scanf("%19s", newName);

            fp = fopen("Categories.txt", "r");
            tp = fopen("Temp.txt", "w");

            if ( fp == NULL || tp == NULL ){
                printf("\nERROR! Unable to rename the Category !\n");
                categMana();
                break;
            }

            while ( fscanf(fp, "%d %19s", &c.category_ID, c.category_name) == 2 ){
                if ( c.category_ID == categId ){
                    strcpy(c.category_name, newName);
                }
                fprintf(tp, "%d %s\n", c.category_ID, c.category_name);
            }

            fclose(fp);
            fclose(tp);
            remove("Categories.txt");
            rename("Temp.txt", "Categories.txt");

            printf("\nCategory Renamed Successfully !\n");
            categMana();
            break;
        }
        else if ( categChoice == 3 ){
            showCategories();
            printf("\nEnter the Category ID to Delete : ");
            scanf("%d", &categId);

            if ( categoryExists(categId) == 0 ){
                printf("\nCategory ID not found !\n");
                categMana();
                break;
            }

            if ( categoryInUse(categId) ){
                printf("\nCannot Delete ! This Category is used by some Expenses.\n");
                categMana();
                break;
            }

            fp = fopen("Categories.txt", "r");
            tp = fopen("Temp.txt", "w");

            if ( fp == NULL || tp == NULL ){
                printf("\nERROR! Unable to delete the Category !\n");
                categMana();
                break;
            }

            while ( fscanf(fp, "%d %19s", &c.category_ID, c.category_name) == 2 ){
                if ( c.category_ID == categId ){
                    found = 1;
                }
                else{
                    fprintf(tp, "%d %s\n", c.category_ID, c.category_name);
                }
            }

            fclose(fp);
            fclose(tp);
            remove("Categories.txt");
            rename("Temp.txt", "Categories.txt");

            if ( found ){
                printf("\nCategory Deleted Successfully !\n");
            }
            categMana();
            break;
        }
        else if ( categChoice == 4 ){
            showCategories();
            printf("\n");
            categMana();
            break;
        }
        else if ( categChoice == 5 ){
            settings();
            break;
        }
        printf("Invalid Choice ! Please Enter The Choice Again : ");
    }
}
void backupData(){
    printf("\n===================================");
    printf("\n           BACKUP DATA             ");
    printf("\n===================================");

    copyFile("Users.txt", "Users_backup.txt");
    copyFile("Accounts.txt", "Accounts_backup.txt");
    copyFile("Transactions.txt", "Transactions_backup.txt");
    copyFile("Expenses.txt", "Expenses_backup.txt");
    copyFile("Categories.txt", "Categories_backup.txt");

    printf("\nBackup Completed Successfully !");
    printf("\n===================================\n");

    settings();
}

// Helper Functions
int accOwned( int Ac_num ){
    FILE *fp;
    struct Account temp;

    fp = fopen("Accounts.txt", "r");

    if ( fp == NULL ){
        return 0;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s", &temp.Ac_num, &temp.userid, &temp.Ac_balance, temp.Ac_type, temp.Ac_DOO) == 5 ){
        if ( temp.Ac_num == Ac_num && temp.userid == currentUSERID ){
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
float getBalance( int Ac_num ){
    FILE *fp;
    struct Account temp;

    fp = fopen("Accounts.txt", "r");

    if ( fp == NULL ){
        return -1.0f;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s", &temp.Ac_num, &temp.userid, &temp.Ac_balance, temp.Ac_type, temp.Ac_DOO) == 5 ){
        if ( temp.Ac_num == Ac_num ){
            fclose(fp);
            return temp.Ac_balance;
        }
    }

    fclose(fp);
    return -1.0f;
}
void setBalance( int Ac_num, float newBalance ){
    FILE *fp;
    FILE *tp;
    struct Account temp;

    fp = fopen("Accounts.txt", "r");
    tp = fopen("Temp.txt", "w");

    if ( fp == NULL || tp == NULL ){
        printf("\nERROR! Unable to update the balance !\n");
        return;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s", &temp.Ac_num, &temp.userid, &temp.Ac_balance, temp.Ac_type, temp.Ac_DOO) == 5 ){
        if ( temp.Ac_num == Ac_num ){
            temp.Ac_balance = newBalance;
        }
        fprintf(tp, "%d %d %.2f %s %s\n", temp.Ac_num, temp.userid, temp.Ac_balance, temp.Ac_type, temp.Ac_DOO);
    }

    fclose(fp);
    fclose(tp);
    remove("Accounts.txt");
    rename("Temp.txt", "Accounts.txt");
}
int generateTransID(){
    FILE *fp;
    struct Transaction t;
    int maxId = 0;

    fp = fopen("Transactions.txt", "r");

    if ( fp != NULL ){
        while ( fscanf(fp, "%d %f %19s %19s %d %29s", &t.Trans_ID, &t.amt, t.DOT, t.type, &t.Ac_num, t.Desc) == 6 ){
            if ( t.Trans_ID > maxId ){
                maxId = t.Trans_ID;
            }
        }
        fclose(fp);
    }

    return maxId + 1;
}
void saveTransaction( float amt, char DOT[], char type[], int Ac_num, char Desc[] ){
    FILE *fp;
    struct Transaction t;

    t.Trans_ID = generateTransID();

    fp = fopen("Transactions.txt", "a");

    if ( fp == NULL ){
        printf("\nERROR! Unable to open Transactions.txt!\n");
        return;
    }

    fprintf(fp, "%d %.2f %s %s %d %s\n", t.Trans_ID, amt, DOT, type, Ac_num, Desc);
    fclose(fp);
}
int generateExpenID(){
    FILE *fp;
    struct Expense e;
    int uid;
    int maxId = 0;

    fp = fopen("Expenses.txt", "r");

    if ( fp != NULL ){
        while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
            if ( e.Expen_ID > maxId ){
                maxId = e.Expen_ID;
            }
        }
        fclose(fp);
    }

    return maxId + 1;
}
void initCategories(){
    FILE *fp;

    fp = fopen("Categories.txt", "r");

    if ( fp == NULL ){
        fp = fopen("Categories.txt", "w");

        if ( fp == NULL ){
            return;
        }

        fprintf(fp, "1 Food\n");
        fprintf(fp, "2 Travel\n");
        fprintf(fp, "3 Bills\n");
        fprintf(fp, "4 Shopping\n");
        fprintf(fp, "5 Health\n");
        fprintf(fp, "6 Other\n");
        fclose(fp);
    }
    else{
        fclose(fp);
    }
}
void showCategories(){
    FILE *fp;
    struct Category c;

    fp = fopen("Categories.txt", "r");

    if ( fp == NULL ){
        printf("\nNo Categories Found !");
        return;
    }

    printf("\n%-8s %s", "ID", "Category");
    while ( fscanf(fp, "%d %19s", &c.category_ID, c.category_name) == 2 ){
        printf("\n%-8d %s", c.category_ID, c.category_name);
    }
    fclose(fp);
}
int categoryExists( int category_ID ){
    FILE *fp;
    struct Category c;

    fp = fopen("Categories.txt", "r");

    if ( fp == NULL ){
        return 0;
    }

    while ( fscanf(fp, "%d %19s", &c.category_ID, c.category_name) == 2 ){
        if ( c.category_ID == category_ID ){
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
int categoryInUse( int category_ID ){
    FILE *fp;
    struct Expense e;
    int uid;

    fp = fopen("Expenses.txt", "r");

    if ( fp == NULL ){
        return 0;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
        if ( e.category_ID == category_ID ){
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
void getCategoryName( int category_ID, char name[] ){
    FILE *fp;
    struct Category c;

    strcpy(name, "Unknown");

    fp = fopen("Categories.txt", "r");

    if ( fp == NULL ){
        return;
    }

    while ( fscanf(fp, "%d %19s", &c.category_ID, c.category_name) == 2 ){
        if ( c.category_ID == category_ID ){
            strcpy(name, c.category_name);
            break;
        }
    }

    fclose(fp);
}
int chooseCategory(){
    int category_ID;

    showCategories();
    printf("\nEnter the Category ID : ");

    while (1){
        scanf("%d", &category_ID);

        if ( categoryExists(category_ID) ){
            break;
        }
        printf("Invalid Category ! Please Enter the Category ID Again : ");
    }

    return category_ID;
}
void chooseMethod( char method[] ){
    int methodChoice;

    printf("\n1. Cash");
    printf("\n2. UPI");
    printf("\n3. Card");
    printf("\n4. NetBanking");
    printf("\nEnter the Payment Method : ");

    while (1){
        scanf("%d", &methodChoice);

        if ( methodChoice == 1 ){
            strcpy(method, "Cash");
            break;
        }
        else if ( methodChoice == 2 ){
            strcpy(method, "UPI");
            break;
        }
        else if ( methodChoice == 3 ){
            strcpy(method, "Card");
            break;
        }
        else if ( methodChoice == 4 ){
            strcpy(method, "NetBanking");
            break;
        }
        printf("Invalid Choice ! Please Enter Valid Choice : ");
    }
}
float categoryTotal( int category_ID ){
    FILE *fp;
    struct Expense e;
    int uid;
    float total = 0;

    fp = fopen("Expenses.txt", "r");

    if ( fp == NULL ){
        return 0;
    }

    while ( fscanf(fp, "%d %d %f %19s %19s %d %29s", &uid, &e.Expen_ID, &e.amt, e.DOE, e.method, &e.category_ID, e.Desc) == 7 ){
        if ( uid == currentUSERID && e.category_ID == category_ID ){
            total = total + e.amt;
        }
    }

    fclose(fp);
    return total;
}
void copyFile( char source[], char dest[] ){
    FILE *src;
    FILE *dst;
    int ch;

    src = fopen(source, "r");

    if ( src == NULL ){
        return;
    }

    dst = fopen(dest, "w");

    if ( dst == NULL ){
        fclose(src);
        return;
    }

    while ( ( ch = fgetc(src) ) != EOF ){
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);

    printf("Backing Up Data....");
}