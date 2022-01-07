#include <stdio.h>

#include "error.h"

/**
 * Prints: "Sanity check failed in <function name>.\n"
 *
 * @param function_name name of the function where the sanity check failed
 */
void sanity_check(char *function_name) {
    printf("Sanity check failed in %s.\n", function_name);
}

/**
 * Prints: "Malloc failed in <function name>.\n"
 *
 * @param function_name name of the function where the malloc failed
 */
void malloc_fail(char *function_name) {
    printf("Malloc failed in %s.\n", function_name);
}