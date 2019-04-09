#include "silly_input.h"

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

	return *argc;
}

/* TODO: change the function to get the string to output or make it a constant */

ssize_t get_input(char *** args, int *  argc, char **_input) {
	char * msg = silly_get_msg();

	if ((*_input = linenoise(msg)) == NULL) {
		return 0;
	}

	free(msg);

	silly_parse(_input, strlen(*_input));
	
	return split(*_input, args, argc, " ");
}