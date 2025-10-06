#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int id;
    float grade;
};

int main() {
    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Student *students = malloc(n * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for student %d: ", i + 1);
        scanf("%s %d %f", students[i].name, &students[i].id, &students[i].grade);
    }

    printf("\nID     Name        Grade\n");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-10s %.1f\n", students[i].id, students[i].name, students[i].grade);
    }

    free(students);
    return 0;
}
