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

	return 0;
}

ssize_t get_input(char *** args, int *  argc) {
	char input[KIBIBYTE] = { 0 };
	char cwd[KIBIBYTE] = "";

	getcwd(cwd, KIBIBYTE);
	printf("silly <%s> ", cwd);

	fgets(input, KIBIBYTE, stdin);
	input[strlen(input) - 1] = '\0';

	return split(input, args, argc, " ");
}