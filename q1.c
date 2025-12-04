#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    char name[50];
    int roll;
    float marks[3];
    float percentage;
    char grade[3];
};

void inputStudents(struct Student s[], int *n);
void calculate(struct Student *s);
void showAll(struct Student s[], int n);
void findByGrade(struct Student s[], int n);
void findByRoll(struct Student s[], int n);
void findByName(struct Student s[], int n);
void classAverage(struct Student s[], int n);
void rankStudents(struct Student s[], int n);
void sortByPercentage(struct Student s[], int n);

int main() {
    struct Student s[MAX];
    int n = 0, choice;

    do {
        printf("\n===== STUDENT RECORD SYSTEM =====\n");
        printf("1. Input Student Records\n");
        printf("2. Display All Students\n");
        printf("3. Search by Grade\n");
        printf("4. Search by Roll Number\n");
        printf("5. Search by Name\n");
        printf("6. Class Average (Above/Below Avg)\n");
        printf("7. Display Rank List\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: inputStudents(s, &n); break;
            case 2: showAll(s, n); break;
            case 3: findByGrade(s, n); break;
            case 4: findByRoll(s, n); break;
            case 5: findByName(s, n); break;
            case 6: classAverage(s, n); break;
            case 7: rankStudents(s, n); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}

void inputStudents(struct Student s[], int *n) {
    int count;
    printf("How many students you want to enter? ");
    scanf("%d", &count);

    for(int i = *n; i < *n + count; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        printf("Enter Name: ");
        scanf(" %[^\n]", s[i].name);
        printf("Enter Roll Number: ");
        scanf("%d", &s[i].roll);

        for(int j = 0; j < 3; j++) {
            do {
                printf("Enter Marks in Subject %d (0-100): ", j + 1);
                scanf("%f", &s[i].marks[j]);
                if(s[i].marks[j] < 0 || s[i].marks[j] > 100)
                    printf("Invalid! Enter again.\n");
            } while(s[i].marks[j] < 0 || s[i].marks[j] > 100);
        }

        calculate(&s[i]);
    }
    *n += count;
}

void calculate(struct Student *s) {
    float total = (*s).marks[0] + (*s).marks[1] + (*s).marks[2];
    (*s).percentage = total / 3;

    if((*s).percentage >= 90) strcpy((*s).grade, "A+");
    else if((*s).percentage >= 80) strcpy((*s).grade, "A");
    else if((*s).percentage >= 70) strcpy((*s).grade, "B+");
    else if((*s).percentage >= 60) strcpy((*s).grade, "B");
    else if((*s).percentage >= 50) strcpy((*s).grade, "C");
    else strcpy((*s).grade, "F");
}

void showAll(struct Student s[], int n) {
    if(n == 0) { printf("No data!\n"); return; }

    printf("\n%-20s %-10s %-10s %-10s %-10s %-10s %-10s\n", 
           "Name", "Roll", "M1", "M2", "M3", "Per%", "Grade");
    printf("-----------------------------------------------------------------------\n");

    for(int i = 0; i < n; i++) {
        printf("%-20s %-10d %-10.1f %-10.1f %-10.1f %-10.1f %-10s\n",
            s[i].name, s[i].roll,
            s[i].marks[0], s[i].marks[1], s[i].marks[2],
            s[i].percentage, s[i].grade);
    }
}

void findByGrade(struct Student s[], int n) {
    char g[3];
    printf("Enter Grade to search (A+, A, B+, B, C, F): ");
    scanf("%s", g);

    int found = 0;
    for(int i = 0; i < n; i++) {
        if(strcmp(s[i].grade, g) == 0) {
            printf("%s (Roll %d) - %.2f%%\n", s[i].name, s[i].roll, s[i].percentage);
            found = 1;
        }
    }
    if(!found) printf("No student with grade %s found.\n", g);
}

void findByRoll(struct Student s[], int n) {
    int r;
    printf("Enter Roll Number: ");
    scanf("%d", &r);

    for(int i = 0; i < n; i++) {
        if(s[i].roll == r) {
            printf("Found: %s - %.2f%% Grade: %s\n", s[i].name, s[i].percentage, s[i].grade);
            return;
        }
    }
    printf("No student found with roll %d\n", r);
}

void findByName(struct Student s[], int n) {
    char name[50];
    printf("Enter Name: ");
    scanf(" %[^\n]", name);

    for(int i = 0; i < n; i++) {
        if(strcasecmp(s[i].name, name) == 0) {
            printf("Found: %s (Roll %d) - %.2f%% Grade: %s\n", 
                   s[i].name, s[i].roll, s[i].percentage, s[i].grade);
            return;
        }
    }
    printf("No student found with name %s\n", name);
}

void classAverage(struct Student s[], int n) {
    if(n == 0) { printf("No data!\n"); return; }

    float sum = 0;
    for(int i = 0; i < n; i++) sum += s[i].percentage;
    float avg = sum / n;

    printf("\nClass Average = %.2f%%\n\n", avg);

    printf("---- Students Above Average ----\n");
    for(int i = 0; i < n; i++)
        if(s[i].percentage > avg)
            printf("%s (%.2f%%)\n", s[i].name, s[i].percentage);

    printf("\n---- Students Below Average ----\n");
    for(int i = 0; i < n; i++)
        if(s[i].percentage < avg)
            printf("%s (%.2f%%)\n", s[i].name, s[i].percentage);
}

void sortByPercentage(struct Student s[], int n) {
    struct Student temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(s[i].percentage < s[j].percentage) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

void rankStudents(struct Student s[], int n) {
    if(n == 0) { printf("No data!\n"); return; }

    sortByPercentage(s, n);

    printf("\n===== RANK LIST =====\n");
    for(int i = 0; i < n; i++) {
        printf("Rank %d: %s (%.2f%%)\n", i + 1, s[i].name, s[i].percentage);
    }
}
