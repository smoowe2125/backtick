#pragma once

#include <stdlib.h>

// macro for reporting errors during scanning / tokenization
#define SCANNING_ERROR(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
