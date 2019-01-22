#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>


#define KIBIBYTE (size_t)1024


ssize_t split(const char * arg, char *** args, int * argc, char * delim);
ssize_t get_input(char *** args, int *  argc);

int main(void) {	
	char ** words = NULL;
	char * cmd = NULL;
	char ** args = NULL;
	int argc = 0;
	bool exit = false;
	int status = 0;
	int c_ret = 0;
	pid_t pid = 0;
	int ret = 0;
	
	printf("silly");
	while (!exit) {
		//printf("silly > ");
		if (get_input(&words, &argc) == -1) {
			fprintf(stderr, "memory allocation error has forced the process \
					to terminate");
			exit = true;
			ret = -1;
		}
		
		if (strcmp(words[0], "exit") == 0) {
			exit = true;
		}
		else {
			pid = fork();
	
			if (pid == 0) {
				execvp(words[0], words);	
			}
			c_ret = waitpid(pid, &status, 0); 

			if (c_ret == -1) fprintf(stderr, "cannot run %s with the given arguments\n" , words[0]);
			if (c_ret == pid) printf("%s", !status ? "" : "command have returned an error code\n");

			for (size_t i = 0; i <= argc; i++) {
				free(words[i]);
				words[i] = NULL;
			}

			free(words);
			words = NULL;
		}
	}
	return ret;
}
ssize_t split(const char * arg, char *** args, int * argc, char * delim) {
	char * delim_occ = NULL;
	size_t w_count = 1;
	size_t w_used = 0;
	char ** words = (char**)calloc(w_count, sizeof(char*));
	char * s = NULL;

	if (words == NULL) return -1;

	if ((s = strdup(arg)) == NULL) return -1;

	while ((delim_occ = strsep(&s, delim)) != NULL) { 
		if (w_count == w_used) {
			w_count *= 2;
			words = realloc(words, w_count * sizeof(char*));
			if (words == NULL) return -1;
		}
		words[w_used++] = strdup(delim_occ);
	}

	if (w_used == 0) free(words);
	else  words = realloc(words, w_used * sizeof(char*));

	*argc = w_used;
	*args = words;
	free(s);

	return 0;
}

ssize_t get_input(char *** args, int *  argc) {
	char input[KIBIBYTE] = { 0 };
 	
	printf("silly > ");

	if (read(0, input, KIBIBYTE) < 0) return -1;
	input[strlen(input) - 1] = '\0';

	return split(input, args, argc, " ");
}
