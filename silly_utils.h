#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#define HOME getenv("HOME")

void clean_up(char *** words, int w_count);

ssize_t cd(char ** words, int w_count);

ssize_t silly_execvp(char ** words, ...);

ssize_t silly_getcwd(char * _dst, size_t size);

ssize_t silly_parse(char * cmd, ssize_t size);