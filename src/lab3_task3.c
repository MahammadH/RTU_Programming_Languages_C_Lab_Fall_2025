/*
 * Lab 3, Task 3
 * Student Name, Student ID
 *Mahammad Hashimov
 * Implement basic string handling functions.
 * Write your own versions of:
 *   - my_strlen (finds string length)
 *   - my_strcpy (copies string from src to dest)
 *
 * Rules:
 *   - Do not use <string.h> functions for strlen/strcpy.
 *   - Use loops and manual pointer/array access.
 *
 * Example:
 *   char s[] = "hello";
 *   int len = my_strlen(s);   // should return 5
 *
 *   char buffer[100];
 *   my_strcpy(buffer, s);     // buffer now contains "hello"
 */

#include <stdio.h>

int my_strlen(const char *str);
void my_strcpy(char *dest, const char *src);

int main(void) {
    char text[] = "hello";
    int len = my_strlen(text);
    printf("Length: %d\n", len);  // 5

    char buffer[100];
    my_strcpy(buffer, text);
    printf("Copied string: %s\n", buffer); // hello

    return 0;
}

int my_strlen(const char *str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

// String'i kopyala
void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0'; 
}