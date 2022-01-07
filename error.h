#ifndef __ERROR_H__
#define __ERROR_H__

/**
 * Prints: "Sanity check failed in <function name>.\n"
 *
 * @param function_name name of the function where the sanity check failed
 */
void sanity_check(char *function_name);

/**
 * Prints: "Malloc failed in <function name>.\n"
 *
 * @param function_name name of the function where the malloc failed
 */
void malloc_fail(char *function_name);

#endif