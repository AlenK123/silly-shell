#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "silly_input.h"
#include "silly_utils.h"


int main(int argc, char ** argv, char ** envp) {	
	char ** words = NULL;
	int w_count = 0;
	bool exit = false;
	int ret = EXIT_SUCCESS;

	while (!exit) {
		if (get_input(&words, &w_count) == -1) {
			fprintf(stderr, "memory allocation error has forced the process to terminate");
			exit = true;
			ret = EXIT_FAILURE;
		}
		
		if (strcmp(words[0], "exit") == 0) {
			exit = true;
		}

		else if (strcmp(words[0], "cd") == 0) {
			cd(words, w_count);
		}

		else {
			silly_execvp(words);
		}

		clean_up(&words, w_count);
	}

	return ret;
}