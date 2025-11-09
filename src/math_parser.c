#include <stdio.h>
#include <ctype.h>

int index_pos = 0;

double read_expr(const char *exp);
double read_term(const char *exp);
double read_value(const char *exp);

void ignore_spaces(const char *exp) {
    while (exp[index_pos] == ' ') index_pos++;
}

double read_number(const char *exp) {
    double val = 0;
    double dec = 0;
    double frac = 0.1;
    int isDecimal = 0;

    ignore_spaces(exp);

    while (isdigit(exp[index_pos]) || exp[index_pos] == '.') {
        if (exp[index_pos] == '.') {
            isDecimal = 1;
        } else if (!isDecimal) {
            val = val * 10 + (exp[index_pos] - '0');
        } else {
            dec += (exp[index_pos] - '0') * frac;
            frac *= 0.1;
        }
        index_pos++;
    }

    return val + dec;
}

double read_value(const char *exp) {
    ignore_spaces(exp);

    if (exp[index_pos] == '(') {
        index_pos++;
        double inside = read_expr(exp);
        if (exp[index_pos] == ')') index_pos++;
        return inside;
    }

    if (exp[index_pos] == '-') {
        index_pos++;
        return -read_value(exp);
    }

    return read_number(exp);
}

double read_term(const char *exp) {
    double left = read_value(exp);
    ignore_spaces(exp);

    while (exp[index_pos] == '*' || exp[index_pos] == '/') {
        char op = exp[index_pos++];
        double right = read_value(exp);

        if (op == '*')
            left *= right;
        else
            left /= right;

        ignore_spaces(exp);
    }

    return left;
}

double read_expr(const char *exp) {
    double left = read_term(exp);
    ignore_spaces(exp);

    while (exp[index_pos] == '+' || exp[index_pos] == '-') {
        char op = exp[index_pos++];
        double right = read_term(exp);

        if (op == '+')
            left += right;
        else
            left -= right;

        ignore_spaces(exp);
    }

    return left;
}

int main() {
    char input[150];

    printf("Enter an expression: ");
    fgets(input, sizeof(input), stdin);

    index_pos = 0;
    double result = read_expr(input);

    printf("Result = %.2f\n", result);
    return 0;
}
