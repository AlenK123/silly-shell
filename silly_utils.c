#include "silly_utils.h"


void clean_up(char *** words, int w_count) {
	for (size_t i = 0; i <= w_count; i++) {
		free((*words)[i]);
		(*words)[i] = NULL;
	}

	free(*words);
	*words = NULL;
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

ssize_t silly_execvp(char ** words, ...) {
    
    if (strcmp(words[0], "exit") == 0) {
        return -1;
    }

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

ssize_t silly_getcwd(char * _dst, size_t size) {
    /* replacing the $HOME with '~' token for clean output */
    char * new_cwd = NULL;

    getcwd(_dst, size);
    new_cwd = (char*)calloc(size, sizeof(char));
    new_cwd[0] = '~';
    strcpy(new_cwd + 1, _dst + strlen(HOME));
    strcpy(_dst, new_cwd);
    free(new_cwd);
    return 0;
}

ssize_t silly_parse(char * cmd, ssize_t size) {
    /* first we need to convert the '~' token to $HOME */
    char * loc = NULL;

    if ((loc = strstr(cmd, "~")) != NULL) {
        char * new_cmd = (char*)calloc(size, sizeof(char));
        char * _start = strndup(cmd, (size_t)(loc - cmd));
        sprintf(new_cmd, "%s%s%s", _start, HOME, loc + 1);
        strcpy(cmd, new_cmd);
        free(_start);
        free(new_cmd);
    }

    return 0;
}