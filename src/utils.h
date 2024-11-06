/*
    MIT License

    Copyright (c) 2024 Souchet Ferdinand

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


#ifndef UTILS_H
#define UTILS_H


#include <stdlib.h>
#include <stdio.h>


// Some CSI formatting
#define RED "\x1b[38;2;255;0;0m"
#define GREEN "\x1b[38;2;0;255;0m"
#define BLUE "\x1b[38;2;0;0;255m"
#define YELLOW "\x1b[38;2;255;255;0m"
#define CYAN "\x1b[38;2;0;255;255m"
#define MAGENTA "\x1b[38;2;255;0;255m"

#define BOLD "\x1b[1m"
#define FAINT "\x1b[2m"
#define ITALICS "\x1b[3m"
#define UNDERLINE "\x1b[4m"

#define CLEAR "\x1b[m"
#define RESET_INTENSITY "\x1b[22m"


// Constants
#define PI 3.141592654

// To print tables
#define PRINT_TAB(type, tab, size) printf("["); \
for (int i = 0; i < size; i++) {                \
    printf(type, tab[i]);                       \
    if (i + 1 < size) printf(", ");             \
}                                               \
printf("]\r\n")


// To print booleans
#define BOOL(x) (x)? "true" : "false"


// A macro to write tests
#define VERIFY(x, prefix, str...)                       \
if (x)                                                  \
    printf("%s%s%s ", GREEN, prefix, CLEAR);            \
else                                                    \
    printf("%s%s%s ", RED, prefix, CLEAR);              \
printf(str);                                            \
printf("\r\n")


// Prints a section title
#define TITLE(title...) printf("\r\n%s ===== ", BOLD); printf(title); printf(" ===== %s\r\n\r\n", CLEAR)


// Assert a fatal error
#define FATAL_ERROR(cond, error...)                                         \
if (cond) {                                                                 \
    printf("%s[Fatal Error %s:%i]%s ", RED, __FILE__, __LINE__, CLEAR);     \
    printf(error);                                                          \
    printf("\r\n");                                                         \
    exit(EXIT_FAILURE);                                                     \
}


// Assert warning
#define WARNING(cond, exec, error...)                                       \
if (cond) {                                                                 \
    printf("%s[Warning %s:%i]%s ", YELLOW, __FILE__, __LINE__, CLEAR);      \
    printf(error);                                                          \
    printf("\r\n");                                                         \
    exec                                                                    \
}


#endif //#ifndef UTILS_H