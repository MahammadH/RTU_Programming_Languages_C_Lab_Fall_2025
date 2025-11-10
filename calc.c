#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>

#ifdef _WIN32
#include <direct.h> // For Windows
#else
#include <sys/stat.h> // For Linux/macOS
#endif

#define STUDENT_NAME "Ismayil"
#define STUDENT_LASTNAME "Allahverdili"
#define STUDENT_ID "231ADB126"

// Global variables for managing the text input
const char *expression_input;
long position = 0;
long expr_length = 0;
long error_pos = 0;

// Function prototypes
double evaluate_expression(void);
double evaluate_term(void);
double evaluate_factor(void);
double evaluate_number(void);
double evaluate_exponentiation(void);

// Function to ignore spaces and comments
void ignore_spaces() {
    while (position < expr_length) {
        char current_char = expression_input[position];
        if (isspace(current_char)) {
            position++;
        } else if (current_char == '#') { // Skip comments starting with '#'
            while (position < expr_length && expression_input[position] != '\n') position++;
        } else {
            break;
        }
    }
}

// Function to parse and return numbers (integers and floats)
double evaluate_number() {
    ignore_spaces();
    long start_pos = position;
    char buffer[64];
    int idx = 0;
    int dot_found = 0;

    while (position < expr_length && (isdigit(expression_input[position]) || expression_input[position] == '.')) {
        if (expression_input[position] == '.') {
            if (dot_found) { 
                error_pos = position + 1; 
                return 0; 
            }
            dot_found = 1;
        }
        if (idx < 63) buffer[idx++] = expression_input[position];
        position++;
    }

    buffer[idx] = '\0';
    if (idx == 0) {
        error_pos = start_pos + 1;
        return 0;
    }
    return atof(buffer);
}

// Function to handle the parsing of a factor
double evaluate_factor() {
    ignore_spaces();
    if (position >= expr_length) {
        error_pos = position + 1;
        return 0;
    }

    char current_char = expression_input[position];
    if (current_char == '(') {
        position++;
        double value = evaluate_expression();
        ignore_spaces();
        if (position >= expr_length || expression_input[position] != ')') {
            error_pos = position + 1;
            return value;
        }
        position++;
        return value;
    } else if (current_char == '+' || current_char == '-') {
        position++;
        double factor_value = evaluate_factor();
        return (current_char == '-') ? -factor_value : factor_value;
    } else {
        return evaluate_number();
    }
}

// Function to handle exponentiation (** operator)
double evaluate_exponentiation() {
    double base = evaluate_factor();
    ignore_spaces();

    while (position + 1 < expr_length && expression_input[position] == '*' && expression_input[position + 1] == '*') {
        position += 2;
        double exponent = evaluate_exponentiation();
        base = pow(base, exponent);
        ignore_spaces();
    }
    return base;
}

// Function to handle multiplication and division
double evaluate_term() {
    double left_value = evaluate_exponentiation();
    while (1) {
        ignore_spaces();
        if (position >= expr_length) break;

        char operator = expression_input[position];
        if (operator == '*' || operator == '/') {
            position++;
            double right_value = evaluate_exponentiation();
            if (operator == '*') left_value *= right_value;
            else {
                if (right_value == 0) { error_pos = position; return left_value; }
                left_value /= right_value;
            }
        } else break;
    }
    return left_value;
}

// Function to evaluate addition and subtraction
double evaluate_expression() {
    double left_value = evaluate_term();
    while (1) {
        ignore_spaces();
        if (position >= expr_length) break;

        char operator = expression_input[position];
        if (operator == '+' || operator == '-') {
            position++;
            double right_value = evaluate_term();
            if (operator == '+') left_value += right_value;
            else left_value -= right_value;
        } else break;
    }
    return left_value;
}

// Function to create a directory in the file system
int create_directory(const char *path) {
    if (_mkdir(path) == -1) {
        return 0; // Directory creation failed
    }
    return 1; // Success
}

// Function to check if a file is a text file based on the extension
int is_text_file(const char *filename) {
    int length = strlen(filename);
    return length > 4 && strcmp(filename + length - 4, ".txt") == 0;
}

// Function to extract the base name from a file path
char *get_basename(const char *path) {
    const char *last_slash = strrchr(path, '\\');  // Use '\\' for Windows paths
    const char *base_name = last_slash ? last_slash + 1 : path;
    char *dot_position = strrchr(base_name, '.');
    ptrdiff_t length = dot_position ? (dot_position - base_name) : (ptrdiff_t)strlen(base_name);
    char *result = malloc(length + 1);
    strncpy(result, base_name, length);
    result[length] = '\0';
    return result;
}

// Function to process a single input file
void process_input_file(const char *input_file, const char *output_directory) {
    FILE *file = fopen(input_file, "r");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    expr_length = ftell(file);
    rewind(file);

    char *buffer = malloc(expr_length + 1);
    fread(buffer, 1, expr_length, file);
    fclose(file);
    buffer[expr_length] = '\0';

    expression_input = buffer;
    position = 0;
    error_pos = 0;

    double result = evaluate_expression();
    ignore_spaces();
    if (position < expr_length && error_pos == 0) error_pos = position + 1;

    char *base_filename = get_basename(input_file);
    char output_file[512];
    sprintf(output_file, "%s\\%s_%s_%s_%s.txt", output_directory, base_filename, STUDENT_NAME, STUDENT_LASTNAME, STUDENT_ID);

    FILE *output = fopen(output_file, "w");
    if (output) {
        if (error_pos) fprintf(output, "ERROR:%ld\n", error_pos);
        else fprintf(output, "%.15g\n", result);
        fclose(output);
    }

    free(base_filename);
    free(buffer);
}

// Function to process all files in a directory
void process_directory_files(const char *input_directory, const char *output_directory) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(input_directory, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        return;
    }
    do {
        if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (strcmp(findFileData.cFileName, ".") == 0 || strcmp(findFileData.cFileName, "..") == 0) continue;
            continue; // Skip directories
        }
        char path[512];
        sprintf(path, "%s\\%s", input_directory, findFileData.cFileName);
        process_input_file(path, output_directory);
    } while (FindNextFile(hFind, &findFileData) != 0);
    FindClose(hFind);
}

int main(int argc, char *argv[]) {
    const char *input_directory = NULL;
    const char *output_directory = NULL;
    const char *input_file = NULL;

    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dir") == 0) && i + 1 < argc)
            input_directory = argv[++i];
        else if ((strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output-dir") == 0) && i + 1 < argc)
            output_directory = argv[++i];
        else
            input_file = argv[i];
    }

    if (!input_file) {
        printf("Usage: ./calc input.txt [-d dir] [-o outdir]\n");
        return 1;
    }

    char output_folder[512];
    if (output_directory) strcpy(output_folder, output_directory);
    else {
        char *base_filename = get_basename(input_file);
        sprintf(output_folder, "%s_%s_%s_%s", base_filename, STUDENT_NAME, STUDENT_LASTNAME, STUDENT_ID);
        free(base_filename);
    }

    create_directory(output_folder);

    if (input_directory) process_directory_files(input_directory, output_folder);
    else process_input_file(input_file, output_folder);

    return 0;
}
