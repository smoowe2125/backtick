#pragma once

#include <stdlib.h>

#define SCAN_ERROR 1
#define PARSE_ERROR 2

int had_error = 0;

// macro for reporting errors
#define REPORT_ERROR(err_type, ...) {\
    fprintf(stderr,  "[Line %d] ", current_line); \
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
