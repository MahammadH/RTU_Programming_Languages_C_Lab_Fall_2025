/*
 * week5_task3_student_management_system.c
 * Author: [Mahammad Hashimov], [231ADB124]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.txt"

typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;

int load_students(Student students[], int max) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return 0; // no file yet

    int count = 0;
    while (count < max && fscanf(fp, "%49s %d %f", students[count].name, &students[count].id, &students[count].gpa) == 3) {
        count++;
    }
    fclose(fp);
    return count;
}

void save_students(Student students[], int count) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        perror("Error opening file for saving");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s %d %.2f\n", students[i].name, students[i].id, students[i].gpa);
    }
    fclose(fp);
    printf("Data saved. Goodbye!\n");
}

void add_student(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }
    Student s;
    printf("Enter name: ");
    scanf("%49s", s.name);
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);
    students[*count] = s;
    (*count)++;
    printf("Student added successfully!\n");
}

void list_students(Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }
    printf("=== Student List ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s (ID: %d, GPA: %.2f)\n", i + 1, students[i].name, students[i].id, students[i].gpa);
    }
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);
    int choice;

    while (1) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1: list_students(students, count); break;
            case 2: add_student(students, &count); break;
            case 3: save_students(students, count); return 0;
            default: printf("Invalid option.\n");
        }
    }
    return 0;
}
