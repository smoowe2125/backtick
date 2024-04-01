#pragma once

#include <stdbool.h>
#include <string.h>

#define SCAN_ERROR 1
#define PARSE_ERROR 2

int had_error = 0;

bool compare(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

// macro for reporting errors
#define REPORT_ERROR(err_type, line, ...) {\
    fprintf(stderr,  "[Line %d] ", line); \
    switch(err_type) \
    { \
        case SCAN_ERROR: \
            fprintf(stderr, "Scanning error: "); \
            break; \
        case PARSE_ERROR: \
            fprintf(stderr, "Parsing error: "); \
            break; \
    } \
    fprintf(stderr, __VA_ARGS__); had_error = 1; \
}
