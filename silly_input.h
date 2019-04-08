#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include "silly_utils.h"

#define KIBIBYTE (size_t)1024

ssize_t split(const char * arg, char *** args, int * argc, char * delim);

ssize_t get_input(char *** args, int *  argc);