/*
 * randString.c written by William Halsey
 * whalsey@vols.utk.edu
 *
 * Monday 7 March 2016
 */

#include <stdio.h>
#include <stdlib.h>

#define usage "USAGE: ./{Executable} {Number of characters in random string} > {output file}.txt\n"

int main (int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, usage);
		exit(-1);
	}

	int num = atoi(argv[1]);

	for (int i=0; i<num; i++) {
		fprintf(stdout, "%c", (char)(rand()%26+97));
	}
	fprintf(stdout, "\n");

	return 0;
}
