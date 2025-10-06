#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main() {
    struct Student student1, student2;

    strcpy(student1.name, "Mahammad Hashimov");
    student1.id = 1001;
    student1.grade = 9.1;

    strcpy(student2.name, "Lele Ortalix");
    student2.id = 1002;
    student2.grade = 8.7;

    printf("Student 1: %s, ID: %d, Grade: %.1f\n", student1.name, student1.id, student1.grade);
    printf("Student 2: %s, ID: %d, Grade: %.1f\n", student2.name, student2.id, student2.grade);

    return 0;
}
