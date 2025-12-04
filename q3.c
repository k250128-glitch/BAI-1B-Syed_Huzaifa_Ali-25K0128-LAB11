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

int experienceYears(int joinYear) {
    return currentYear - joinYear;
}

// Function prototypes
void addEmployee(struct Employee *e, int *n);
void showAll(struct Employee *e, int n);
void searchByDepartment(struct Employee *e, int n);
void searchByDesignation(struct Employee *e, int n);
void searchByExperience(struct Employee *e, int n);
void deptSalaryStats(struct Employee *e, int n);
void annualAppraisal(struct Employee *e, int n);
void promotionEligible(struct Employee *e, int n);

int main() {
    struct Employee employees[MAX];
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
            case 1: addEmployee(employees, &n); break;
            case 2: showAll(employees, n); break;
            case 3: searchByDepartment(employees, n); break;
            case 4: searchByDesignation(employees, n); break;
            case 5: searchByExperience(employees, n); break;
            case 6: deptSalaryStats(employees, n); break;
            case 7: annualAppraisal(employees, n); break;
            case 8: promotionEligible(employees, n); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}

// Add Employee
void addEmployee(struct Employee *e, int *n) {
    struct Employee *emp = e + *n;

    printf("\nEnter Employee ID: ");
    scanf("%d", &(*emp).id);

    printf("Enter Name: ");
    scanf(" %[^\n]", (*emp).name);

    printf("Select Department:\n1. IT\n2. HR\n3. Finance\n4. Marketing\n5. Operations\n");
    int dep;
    scanf("%d", &dep);

    switch(dep) {
        case 1: strcpy((*emp).department, "IT"); break;
        case 2: strcpy((*emp).department, "HR"); break;
        case 3: strcpy((*emp).department, "Finance"); break;
        case 4: strcpy((*emp).department, "Marketing"); break;
        case 5: strcpy((*emp).department, "Operations"); break;
        default: printf("Invalid department!"); return;
    }

    printf("Select Designation:\n1. Intern\n2. Junior\n3. Senior\n4. Manager\n5. Director\n");
    int ds;
    scanf("%d", &ds);

    switch(ds) {
        case 1: strcpy((*emp).designation, "Intern"); break;
        case 2: strcpy((*emp).designation, "Junior"); break;
        case 3: strcpy((*emp).designation, "Senior"); break;
        case 4: strcpy((*emp).designation, "Manager"); break;
        case 5: strcpy((*emp).designation, "Director"); break;
        default: printf("Invalid designation!"); return;
    }

    printf("Enter Salary: ");
    scanf("%f", &(*emp).salary);

    printf("Enter Joining Year: ");
    scanf("%d", &(*emp).joinYear);

    printf("Enter Phone Number: ");
    scanf("%s", (*emp).phone);

    printf("Enter Email: ");
    scanf("%s", (*emp).email);

    (*n)++;
    printf("Employee added successfully!\n");
}

// Show All Employees
void showAll(struct Employee *e, int n) {
    if(n == 0) {
        printf("No employees found!\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        struct Employee *emp = e + i;
        printf("\n=== Employee %d ===\n", i + 1);
        printf("ID: %d\n", (*emp).id);
        printf("Name: %s\n", (*emp).name);
        printf("Department: %s\n", (*emp).department);
        printf("Designation: %s\n", (*emp).designation);
        printf("Salary: %.2f\n", (*emp).salary);
        printf("Joining Year: %d\n", (*emp).joinYear);
        printf("Experience: %d years\n", experienceYears((*emp).joinYear));
        printf("Phone: %s\n", (*emp).phone);
        printf("Email: %s\n", (*emp).email);
    }
}

// Search by Department
void searchByDepartment(struct Employee *e, int n) {
    char dep[20];
    printf("Enter Department: ");
    scanf("%s", dep);

    int found = 0;
    for(int i = 0; i < n; i++) {
        struct Employee *emp = e + i;
        if(strcmp((*emp).department, dep) == 0) {
            printf("%s (ID %d) - %.2f salary\n", (*emp).name, (*emp).id, (*emp).salary);
            found = 1;
        }
    }
    if(!found) printf("No such department found.\n");
}

// Search by Designation
void searchByDesignation(struct Employee *e, int n) {
    char des[20];
    printf("Enter Designation: ");
    scanf("%s", des);

    int found = 0;
    for(int i = 0; i < n; i++) {
        struct Employee *emp = e + i;
        if(strcmp((*emp).designation, des) == 0) {
            printf("%s (ID %d) - %.2f\n", (*emp).name, (*emp).id, (*emp).salary);
            found = 1;
        }
    }
    if(!found) printf("No such designation found.\n");
}

// Search by Experience
void searchByExperience(struct Employee *e, int n) {
    int exp;
    printf("Enter Minimum Experience (years): ");
    scanf("%d", &exp);

    int found = 0;
    for(int i = 0; i < n; i++) {
        struct Employee *emp = e + i;
        if(experienceYears((*emp).joinYear) >= exp) {
            printf("%s (ID %d) - %d years\n", (*emp).name, (*emp).id, experienceYears((*emp).joinYear));
            found = 1;
        }
    }
    if(!found) printf("No employee with that experience.\n");
}

// Department Salary Statistics
void deptSalaryStats(struct Employee *e, int n) {
    char dep[20];
    printf("Enter Department: ");
    scanf("%s", dep);

    float sum = 0, max = -1, min = 999999;
    int count = 0;

    for(int i = 0; i < n; i++) {
        struct Employee *emp = e + i;
        if(strcmp((*emp).department, dep) == 0) {
            sum += (*emp).salary;
            if((*emp).salary > max) max = (*emp).salary;
            if((*emp).salary < min) min = (*emp).salary;
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

// Annual Appraisal
void annualAppraisal(struct Employee *e, int n) {
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
        struct Employee *emp = e + i;
        if((*emp).id == id) {
            float inc = (*emp).salary * rate / 100.0;
            (*emp).salary += inc;
            printf("Salary updated! New salary: %.2f\n", (*emp).salary);
            return;
        }
    }
    printf("Employee not found!\n");
}

// Promotion Eligibility (>3 years)
void promotionEligible(struct Employee *e, int n) {
    printf("\nEmployees eligible for promotion (>3 years):\n");
    int found = 0;
    for(int i = 0; i < n; i++) {
        struct Employee *emp = e + i;
        if(experienceYears((*emp).joinYear) > 3) {
            printf("%s (%s) - %d years experience\n", 
                   (*emp).name, (*emp).designation, experienceYears((*emp).joinYear));
            found = 1;
        }
    }
    if(!found) printf("No employees eligible.\n");
}
