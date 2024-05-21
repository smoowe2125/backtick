#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SCAN_ERROR 1
#define PARSE_ERROR 2

bool had_error = 0;

bool
compare (char *str1, char *str2) {
    return strcmp (str1, str2) == 0;
}

void *
reallocate (void *ptr, size_t old, size_t newsize) {
    if (newsize == 0) {
        free (ptr);
        return NULL;
    }

    void *result = realloc(ptr, newsize);

    return result;
}

// macro for reporting errors
#define REPORT_ERROR(line, ...) {\
    fprintf (stderr,  "[Line %d] ", line); \
    fprintf (stderr, __VA_ARGS__); had_error = true; \
}
