/*
 * week5_task4_struct_binary_io.c
 * Author: [Mahammad Hashimov], [231ADB124]
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

void save_student_binary(const char *filename, Student s) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
}

Student load_student_binary(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }
    Student s;
    fread(&s, sizeof(Student), 1, fp);
    fclose(fp);
    return s;
}

long get_file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) return -1;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int main(void) {
    Student s1 = {"Alice", 21, 3.75};
    Student s2;

    printf("Saving student in binary format...\n");
    save_student_binary("student.bin", s1);

    printf("Loading student from binary file...\n");
    s2 = load_student_binary("student.bin");

    printf("Loaded student: %s, %d, GPA %.2f\n", s2.name, s2.age, s2.gpa);

    long size = get_file_size("student.bin");
    if (size >= 0) {
        printf("Binary file size: %ld bytes\n", size);
    }

    return 0;
}
