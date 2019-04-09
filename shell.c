#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "silly_input.h"
#include "silly_utils.h"

#define HISTORY ".silly_history"

int main(int argc, char ** argv, char ** envp) {	
	char ** words = NULL;
	char * input = NULL;
	int w_count = 0;
	bool exit = false;
	int ret = EXIT_SUCCESS;
	
	linenoiseHistoryLoad(HISTORY);

	while (!exit) {
		switch (get_input(&words, &w_count, &input)) {
		case -1: 
			fprintf(stderr, "memory allocation error has forced the process to terminate");
			ret = EXIT_FAILURE;
			exit = true;
			break;
		case 0:
			exit = true;
		default:
			exit = (strcmp(words[0], "cd") == 0) ? cd(words, w_count) & 0  : silly_execvp(words) < 0;
			linenoiseHistoryAdd(input);
			break;
		}
		
		clean_up(&words, w_count);
		free(input);
	}

	return ret;
}