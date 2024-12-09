#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    float cgpa;
} Student;

void addStudent(Student **students, int *n);
void viewStudent(Student *students, int n);
void updateStudent(Student *students, int n);
void deleteStudent(Student **students, int *n);
void displayAllStudents(Student *students, int n);
void saveToFile(Student *students, int n);
void loadFromFile(Student **students, int *n);
void menu();

int main() {
    Student *students = NULL;
    int n = 0;

    loadFromFile(&students, &n);

    int choice;

    while (1) {
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character left by scanf

        switch (choice) {
            case 1:
                addStudent(&students, &n);
                break;
            case 2:
                viewStudent(students, n);
                break;
            case 3:
                updateStudent(students, n);
                break;
            case 4:
                deleteStudent(&students, &n);
                break;
            case 5:
                displayAllStudents(students, n);
                break;
            case 6:
                saveToFile(students, n);
                printf("Data saved successfully.\n");
                break;
            case 7:
                loadFromFile(&students, &n);
                printf("Data loaded successfully.\n");
                break;
            case 0:
                saveToFile(students, n);
                free(students);
                printf("Exiting the system...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void menu() {
    printf("\nStudent Management System\n");
    printf("1. Add Student\n");
    printf("2. View Student\n");
    printf("3. Update Student\n");
    printf("4. Delete Student\n");
    printf("5. Display All Students\n");
    printf("6. Save Data to File\n");
    printf("7. Load Data from File\n");
    printf("0. Exit\n");
}

void addStudent(Student **students, int *n) {
    *students = realloc(*students, (*n + 1) * sizeof(Student));

    if (*students == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter student ID: ");
    scanf("%d", &(*students)[*n].id);
    getchar();  // To consume the newline character left by scanf

    printf("Enter student name: ");
    fgets((*students)[*n].name, 50, stdin);
    (*students)[*n].name[strcspn((*students)[*n].name, "\n")] = 0;  // Remove newline character

    printf("Enter student CGPA: ");
    scanf("%f", &(*students)[*n].cgpa);

    (*n)++;
    printf("Student added successfully!\n");
}

void viewStudent(Student *students, int n) {
    int id;
    printf("Enter student ID to view: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("Student ID: %d\n", students[i].id);
            printf("Student Name: %s\n", students[i].name);
            printf("Student CGPA: %.2f\n", students[i].cgpa);
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
}

void updateStudent(Student *students, int n) {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("Enter new name: ");
            getchar();  // To consume the newline character left by scanf
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;  // Remove newline character

            printf("Enter new CGPA: ");
            scanf("%f", &students[i].cgpa);
            printf("Student updated successfully!\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
}

void deleteStudent(Student **students, int *n) {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if ((*students)[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                (*students)[j] = (*students)[j + 1];
            }

            *students = realloc(*students, (*n - 1) * sizeof(Student));
            (*n)--;
            printf("Student with ID %d deleted successfully!\n", id);
            return;
        }
    }

    printf("Student with ID %d not found.\n", id);
}

void displayAllStudents(Student *students, int n) {
    if (n == 0) {
        printf("No students available.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Student Name: %s\n", students[i].name);
        printf("Student CGPA: %.2f\n\n", students[i].cgpa);
    }
}

void saveToFile(Student *students, int n) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Unable to open file for saving!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", students[i].id);
        fprintf(file, "%s\n", students[i].name);
        fprintf(file, "%.2f\n", students[i].cgpa);
    }

    fclose(file);
}

void loadFromFile(Student **students, int *n) {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    while (!feof(file)) {
        *students = realloc(*students, (*n + 1) * sizeof(Student));

        if (*students == NULL) {
            printf("Memory allocation failed!\n");
            fclose(file);
            exit(1);
        }

        fscanf(file, "%d", &(*students)[*n].id);
        fgetc(file);  // To consume the newline character
        fgets((*students)[*n].name, 50, file);
        (*students)[*n].name[strcspn((*students)[*n].name, "\n")] = 0;  // Remove newline character
        fscanf(file, "%f", &(*students)[*n].cgpa);
        fgetc(file);  // To consume the newline character

        (*n)++;
    }

    fclose(file);
}
