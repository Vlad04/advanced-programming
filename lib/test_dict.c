#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "dict.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

int tests_run = 0;

static char * test_init_dict() {
    unsigned int size = 4;
    int error_code;
    Dictionary * my_dict = init_dict(size, &error_code);
    mu_assert("Dictionary size must be 4", my_dict->size == size);
    mu_assert("Used elements must be 0", my_dict->used == 0);
    mu_assert("Error code must be 0", error_code == 0);
    free(my_dict);
    return 0;
}

static char * test_upsert_dict() {
    unsigned int size = 1;
    int error_code;
    Dictionary * my_dict = init_dict(size, &error_code);
    int value = 1;
    upsert_dict(my_dict, "uno", (void *) &value, &error_code);
    mu_assert("Error code must be 0", error_code == 0);
    mu_assert("my_dict->elements[0].key must contain element with key \"uno\"", strcmp(my_dict->elements[0].key, "uno") == 0);
    mu_assert("my_dict->elements[0].key must contain element with value 1", * ((int *) my_dict->elements[0].value) == value);
    free(my_dict);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_init_dict);
    mu_run_test(test_upsert_dict);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result != 0) {
      printf("-_-_-_-_-_-_-_,------,      o \n");
      printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
      printf("-_-_-_-_-_-_-~|__( X .X)  +     + \n");
      printf("_-_-_-_-_-_-_- \"\"  \"\" \n");
      printf(KRED "✗ %s \n" RESET, result);
    }
    else {
      printf("-_-_-_-_-_-_-_,------,      o \n");
      printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
      printf("-_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
      printf("_-_-_-_-_-_-_-  \"\"  \"\" \n");
      printf(KGRN " ✓ ALL TESTS PASSED \n" RESET);
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
