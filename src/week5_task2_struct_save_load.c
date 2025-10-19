/*
 * week5_task2_struct_save_load.c
 * Author: [Mahammad Hashimov], [231ADB124]
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

void save_student(const char *filename, Student s) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }
    fprintf(fp, "%s %d %.2f\n", s.name, s.age, s.gpa);
    fclose(fp);
}

Student load_student(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }
    Student s;
    if (fscanf(fp, "%49s %d %f", s.name, &s.age, &s.gpa) != 3) {
        fprintf(stderr, "Error reading student data from file.\n");
        fclose(fp);
        exit(1);
    }
    fclose(fp);
    return s;
}

int main(void) {
    Student s1 = {"Alice", 21, 3.75};
    Student s2;

    printf("Saving student to file...\n");
    save_student("student.txt", s1);

    printf("Loading student from file...\n");
    s2 = load_student("student.txt");

    printf("Loaded student: %s, %d, GPA %.2f\n", s2.name, s2.age, s2.gpa);
    return 0;
}
