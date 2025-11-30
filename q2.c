#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_ACC 100
#define MAX_TRANS 100

struct Transaction {
    char type[20];         // Deposit / Withdrawal
    float amount;
    char date[20];         // Transaction date
};

struct Account {
    int accNumber;
    char name[50];
    char type[20];
    float balance;
    float interestRate;
    float minBalance;
    char creationDate[20];
    char lastTransactionDate[20];

    struct Transaction history[MAX_TRANS];
    int transCount;
};

void getCurrentDate(char *buffer);
void createAccount(struct Account a[], int *n);
void showAccount(struct Account a[], int n);
void deposit(struct Account a[], int n);
void withdraw(struct Account a[], int n);
void showHistory(struct Account a[], int n);

int main() {
    struct Account a[MAX_ACC];
    int n = 0, choice;

    do {
        printf("\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Show All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Show Transaction History\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(a, &n); break;
            case 2: showAccount(a, n); break;
            case 3: deposit(a, n); break;
            case 4: withdraw(a, n); break;
            case 5: showHistory(a, n); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 0);

    return 0;
}

void getCurrentDate(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, 20, "%d-%m-%Y", tm_info);
}

void createAccount(struct Account a[], int *n) {
    printf("\nEnter Account Number: ");
    scanf("%d", &a[*n].accNumber);

    printf("Enter Name: ");
    scanf(" %[^\n]", a[*n].name);

    int t;
    printf("Select Account Type:\n");
    printf("1. Savings\n2. Current\n3. Fixed Deposit\n");
    printf("Enter: ");
    scanf("%d", &t);

    if(t == 1) {
        strcpy(a[*n].type, "Savings");
        a[*n].minBalance = 1000;
        a[*n].interestRate = 4.0;
    } 
    else if(t == 2) {
        strcpy(a[*n].type, "Current");
        a[*n].minBalance = 5000;
        a[*n].interestRate = 0.0;
    } 
    else if(t == 3) {
        strcpy(a[*n].type, "Fixed Deposit");
        a[*n].minBalance = 10000;
        a[*n].interestRate = 7.0;
    }
    else {
        printf("Invalid type! Account not created.\n");
        return;
    }

    printf("Enter Initial Deposit: ");
    scanf("%f", &a[*n].balance);

    if(a[*n].balance < a[*n].minBalance) {
        printf("Initial deposit must be at least %.2f!\n", a[*n].minBalance);
        return;
    }

    getCurrentDate(a[*n].creationDate);
    strcpy(a[*n].lastTransactionDate, a[*n].creationDate);

    a[*n].transCount = 0;

    printf("Account Created Successfully!\n");
    (*n)++;
}

void showAccount(struct Account a[], int n) {
    if(n == 0) {
        printf("No accounts found!\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        printf("\n==== Account %d ====\n", i + 1);
        printf("Account Number: %d\n", a[i].accNumber);
        printf("Name: %s\n", a[i].name);
        printf("Type: %s\n", a[i].type);
        printf("Balance: %.2f\n", a[i].balance);
        printf("Interest Rate: %.2f%%\n", a[i].interestRate);
        printf("Minimum Balance: %.2f\n", a[i].minBalance);
        printf("Created On: %s\n", a[i].creationDate);
        printf("Last Transaction: %s\n", a[i].lastTransactionDate);
    }
}

int findAccount(struct Account a[], int n, int acc) {
    for(int i = 0; i < n; i++)
        if(a[i].accNumber == acc)
            return i;
    return -1;
}

void deposit(struct Account a[], int n) {
    int acc;
    float amount;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    int index = findAccount(a, n, acc);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    a[index].balance += amount;

    // Add to history
    strcpy(a[index].history[a[index].transCount].type, "Deposit");
    a[index].history[a[index].transCount].amount = amount;
    getCurrentDate(a[index].history[a[index].transCount].date);

    strcpy(a[index].lastTransactionDate, a[index].history[a[index].transCount].date);

    a[index].transCount++;

    printf("Deposit Successful!\n");
}

void withdraw(struct Account a[], int n) {
    int acc;
    float amount;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    int index = findAccount(a, n, acc);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    if(a[index].balance - amount < a[index].minBalance) {
        printf("Cannot withdraw! Balance cannot go below minimum %.2f\n",
               a[index].minBalance);
        return;
    }

    a[index].balance -= amount;

    // Add to history
    strcpy(a[index].history[a[index].transCount].type, "Withdrawal");
    a[index].history[a[index].transCount].amount = amount;
    getCurrentDate(a[index].history[a[index].transCount].date);

    strcpy(a[index].lastTransactionDate, a[index].history[a[index].transCount].date);

    a[index].transCount++;

    printf("Withdrawal Successful!\n");
}

void showHistory(struct Account a[], int n) {
    int acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc);

    int index = findAccount(a, n, acc);
    if(index == -1) {
        printf("Account not found!\n");
        return;
    }

    printf("\n=== Transaction History for %s ===\n", a[index].name);

    for(int i = 0; i < a[index].transCount; i++) {
        printf("%s of %.2f on %s\n",
               a[index].history[i].type,
               a[index].history[i].amount,
               a[index].history[i].date);
    }

    if(a[index].transCount == 0)
        printf("No transactions yet.\n");
}
