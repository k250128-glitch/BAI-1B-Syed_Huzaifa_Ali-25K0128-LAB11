#include <stdio.h>
#include <string.h>

#define MAX 200

struct Employee {
    int id;
    char name[50];
    char department[20];
    char designation[20];
    float salary;
    int joinYear;
    char phone[20];
    char email[50];
};

int currentYear;

void addEmployee(struct Employee e[], int *n);
void showAll(struct Employee e[], int n);
void searchByDepartment(struct Employee e[], int n);
void searchByDesignation(struct Employee e[], int n);
void searchByExperience(struct Employee e[], int n);
void deptSalaryStats(struct Employee e[], int n);
void annualAppraisal(struct Employee e[], int n);
void promotionEligible(struct Employee e[], int n);

int main() {
    struct Employee e[MAX];
    int n = 0, choice;

    printf("Enter Current Year: ");
    scanf("%d", &currentYear);

    do {
        printf("\n==== EMPLOYEE RECORD SYSTEM ====\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search by Department\n");
        printf("4. Search by Designation\n");
        printf("5. Search by Experience\n");
        printf("6. Department Salary Statistics\n");
        printf("7. Annual Appraisal (5-15%%)\n");
        printf("8. Promotion Eligibility (>3 years)\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addEmployee(e, &n); break;
            case 2: showAll(e, n); break;
            case 3: searchByDepartment(e, n); break;
            case 4: searchByDesignation(e, n); break;
            case 5: searchByExperience(e, n); break;
            case 6: deptSalaryStats(e, n); break;
            case 7: annualAppraisal(e, n); break;
            case 8: promotionEligible(e, n); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}

int experienceYears(int joinYear) {
    return currentYear - joinYear;
}

void addEmployee(struct Employee e[], int *n) {
    printf("\nEnter Employee ID: ");
    scanf("%d", &e[*n].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", e[*n].name);

    printf("Select Department:\n");
    printf("1. IT\n2. HR\n3. Finance\n4. Marketing\n5. Operations\n");
    int dep;
    scanf("%d", &dep);

    switch(dep) {
        case 1: strcpy(e[*n].department, "IT"); break;
        case 2: strcpy(e[*n].department, "HR"); break;
        case 3: strcpy(e[*n].department, "Finance"); break;
        case 4: strcpy(e[*n].department, "Marketing"); break;
        case 5: strcpy(e[*n].department, "Operations"); break;
        default: printf("Invalid department!"); return;
    }

    printf("Select Designation:\n");
    printf("1. Intern\n2. Junior\n3. Senior\n4. Manager\n5. Director\n");
    int ds;
    scanf("%d", &ds);

    switch(ds) {
        case 1: strcpy(e[*n].designation, "Intern"); break;
        case 2: strcpy(e[*n].designation, "Junior"); break;
        case 3: strcpy(e[*n].designation, "Senior"); break;
        case 4: strcpy(e[*n].designation, "Manager"); break;
        case 5: strcpy(e[*n].designation, "Director"); break;
        default: printf("Invalid designation!"); return;
    }

    printf("Enter Salary: ");
    scanf("%f", &e[*n].salary);

    printf("Enter Joining Year: ");
    scanf("%d", &e[*n].joinYear);

    printf("Enter Phone Number: ");
    scanf("%s", e[*n].phone);

    printf("Enter Email: ");
    scanf("%s", e[*n].email);

    (*n)++;
    printf("Employee added successfully!\n");
}

void showAll(struct Employee e[], int n) {
    if(n == 0) {
        printf("No employees found!\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        printf("\n=== Employee %d ===\n", i + 1);
        printf("ID: %d\n", e[i].id);
        printf("Name: %s\n", e[i].name);
        printf("Department: %s\n", e[i].department);
        printf("Designation: %s\n", e[i].designation);
        printf("Salary: %.2f\n", e[i].salary);
        printf("Joining Year: %d\n", e[i].joinYear);
        printf("Experience: %d years\n", experienceYears(e[i].joinYear));
        printf("Phone: %s\n", e[i].phone);
        printf("Email: %s\n", e[i].email);
    }
}

void searchByDepartment(struct Employee e[], int n) {
    char dep[20];
    printf("Enter Department: ");
    scanf("%s", dep);

    int f = 0;
    for(int i = 0; i < n; i++) {
        if(strcmp(e[i].department, dep) == 0) {
            printf("%s (ID %d) - %.2f salary\n", e[i].name, e[i].id, e[i].salary);
            f = 1;
        }
    }
    if(!f) printf("No such department found.\n");
}

void searchByDesignation(struct Employee e[], int n) {
    char des[20];
    printf("Enter Designation: ");
    scanf("%s", des);

    int f = 0;
    for(int i = 0; i < n; i++) {
        if(strcmp(e[i].designation, des) == 0) {
            printf("%s (ID %d) - %.2f\n", e[i].name, e[i].id, e[i].salary);
            f = 1;
        }
    }
    if(!f) printf("No such designation found.\n");
}

void searchByExperience(struct Employee e[], int n) {
    int exp;
    printf("Enter Minimum Experience (years): ");
    scanf("%d", &exp);

    int f = 0;
    for(int i = 0; i < n; i++) {
        if(experienceYears(e[i].joinYear) >= exp) {
            printf("%s (ID %d) - %d years\n", e[i].name, e[i].id, experienceYears(e[i].joinYear));
            f = 1;
        }
    }
    if(!f) printf("No employee with that experience.\n");
}

void deptSalaryStats(struct Employee e[], int n) {
    char dep[20];
    printf("Enter department: ");
    scanf("%s", dep);

    float sum = 0, max = -1, min = 999999;
    int count = 0;

    for(int i = 0; i < n; i++) {
        if(strcmp(e[i].department, dep) == 0) {
            sum += e[i].salary;
            if(e[i].salary > max) max = e[i].salary;
            if(e[i].salary < min) min = e[i].salary;
            count++;
        }
    }

    if(count == 0) {
        printf("No employees in this department!\n");
        return;
    }

    printf("\nDept: %s\n", dep);
    printf("Total Salary = %.2f\n", sum);
    printf("Average Salary = %.2f\n", sum / count);
    printf("Highest Salary = %.2f\n", max);
    printf("Lowest Salary = %.2f\n", min);
}

void annualAppraisal(struct Employee e[], int n) {
    int id, rate;
    printf("Enter Employee ID: ");
    scanf("%d", &id);

    printf("Enter performance increment percentage (5-15): ");
    scanf("%d", &rate);

    if(rate < 5 || rate > 15) {
        printf("Invalid increment.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        if(e[i].id == id) {
            float inc = e[i].salary * rate / 100.0;
            e[i].salary += inc;
            printf("Salary updated! New salary: %.2f\n", e[i].salary);
            return;
        }
    }

    printf("Employee not found!\n");
}

void promotionEligible(struct Employee e[], int n) {
    printf("\nEmployees eligible for promotion (>3 years):\n");

    int f = 0;
    for(int i = 0; i < n; i++) {
        if(experienceYears(e[i].joinYear) > 3) {
            printf("%s (%s) - %d years experience\n",
                   e[i].name, e[i].designation, experienceYears(e[i].joinYear));
            f = 1;
        }
    }
    if(!f) printf("No employees eligible.\n");
}
