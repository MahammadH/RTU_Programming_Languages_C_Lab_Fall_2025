/*
 * week5_task1_file_io.c
 * Author: [Mahammad Hashimov], [231ADB124]
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char buffer[256];

    printf("Writing lines to data.txt...\n");
    fp = fopen("data.txt", "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");
    fprintf(fp, "File handling is powerful!\n");
    fclose(fp);

    printf("Reading contents:\n");
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
    return 0;
}
