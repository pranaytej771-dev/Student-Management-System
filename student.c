#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credential.txt"

struct student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[10];
char currentUser[50];

int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void staffMenu();
void guestMenu();
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    while(!loginSystem()) {
        printf("\nAccess Denied! Try again.\n");
    }

    mainMenu();
    return 0;
}

int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];

    printf("===== Login =====\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if(!fp) {
        printf("error: credential.txt not found!\n");
        return 0;
    }

    while(fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if(strcmp(username, fileUser) == 0 &&
           strcmp(password, filePass) == 0) {

            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);

            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void mainMenu() {
    if(strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if(strcmp(currentRole, "USER") == 0)
        userMenu();
    else if(strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        guestMenu();
}

void adminMenu() {
    int choice;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Logging out...\n"); return;
            default: printf("Invalid choice!\n");
        }

    } while(1);
}

void userMenu() {
    printf("\n===== USER MENU =====\n");
    displayStudents();
}

void staffMenu() {
    printf("\n===== STAFF MENU =====\n");
    displayStudents();
}

void guestMenu() {
    printf("\n===== GUEST MENU =====\n");
    printf("Guests can only view student list.\n");
    displayStudents();
}


void addStudent() {
    FILE *fp = fopen(STUDENT_FILE, "a");
    if(!fp) {
        printf("Error opening student file!\n");
        return;
    }

    struct student s;

    printf("\nEnter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);

    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUDENT_FILE, "r");
    if(!fp) {
        printf("No student records found!\n");
        return;
    }

    struct student s;

    printf("\n===== Student Records =====\n");
    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    int r;
    int found = 0;

    printf("\nEnter Roll No to search: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if(!fp) {
        printf("No student file found!\n");
        return;
    }

    struct student s;

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(s.roll == r) {
            printf("\nRecord Found:\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Student not found!\n");

    fclose(fp);
}

void updateStudent() {
    int r, found = 0;
    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    struct student s;

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(s.roll == r) {
            found = 1;
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if(found)
        printf("Record Updated Successfully!\n");
    else
        printf("Record Not Found!\n");
}

void deleteStudent() {
    int r, found = 0;
    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &r);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    struct student s;

    while(fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if(s.roll == r) {
            found = 1;
            continue; 
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if(found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Record Not Found!\n");
} 