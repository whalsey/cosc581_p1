/*
 * hw7.cpp written by William Halsey
 * whalsey@vols.utk.edu
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <streambuf>

#define usage 	"\nUsage: ./<executable> <filename.txt>\n"
#define VERBOSE true

using namespace std;

string readInText(char *);

int main (int argc, char *argv[]) {
	if (argc != 2) {
		cout << usage;
		exit(1);
	}

	string text = readInText(argv[1]);

	return 0;
}

string readInText(char *Fname) {
	if (VERBOSE) cout << "\nreadInText: Entered function\n";
	
	ifstream t(Fname);
	string text;
	t.seekg(0, ios::end);
	text.reserve(t.tellg());
	t.seekg(0, ios::beg);
	
	FILE *f;

	int size;

	f = fopen(Fname, "r");

	fseek(f, (long)0, SEEK_END);
	size = (int)ftell(f);
	fseek(f, (long)0, SEEK_SET);

	if (VERBOSE) cerr << "\nreadInText: The size of the file is " << size << " bytes\n";

	return text;
}
