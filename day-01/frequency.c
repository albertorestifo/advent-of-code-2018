#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE *fp = fopen("./input", "r");
	if (fp == NULL) {
		exit(EXIT_FAILURE);
	}

	int freq = 0;

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	while ((linelen = getline(&line, &linecap, fp)) > 0)
		freq += atoi(line);

	printf("%d\n", freq);
};

