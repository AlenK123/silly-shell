#include "silly_utils.h"

ssize_t silly_execvp(char ** words, ...) {
    pid_t pid = 0;
    int status = 0;
	int c_ret = 0;
    
    pid = fork();

    if (pid == 0) { 
        execvp(words[0], words);
    }

    c_ret = waitpid(pid, &status, 0); 

    if (c_ret == -1) { 
        fprintf(stderr, "cannot run %s with the given arguments\n" , words[0]);
    }

    if (c_ret == pid) {
        printf("%s", !status ? "" : "command have returned an error code\n");
    }

    return c_ret;
}

ssize_t cd(char ** words, int w_count) {
	if (w_count > 1) {
		for (int i = 1; i < w_count; i++) {
			if (chdir(words[i]) < 0) {
				perror(words[i]);
				return -1;
			}
		}
	}
	else {
        return chdir(HOME);
    }

    return 0;
}

void clean_up(char *** words, int w_count) {
	for (size_t i = 0; i <= w_count; i++) {
		free((*words)[i]);
		(*words)[i] = NULL;
	}

	free(*words);
	*words = NULL;
}