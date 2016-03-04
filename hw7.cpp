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
#include <algorithm>

#define usage 	"\nUsage: ./<executable> <filename.txt>\n"
#define VERBOSE true

using namespace std;

string readInText(char *);
bool testString(string);
void eliminateExtraCharacters(string);

int main (int argc, char *argv[]) {
	if (argc != 2) {
		cout << usage;
		exit(1);
	}

	string text = readInText(argv[1]);
	if (VERBOSE) cerr << "\nmain: The input string is - " << text << "\n";

	text.erase(remove(text.begin(), text.end(), ' '), text.end());
	text.erase(remove(text.begin(), text.end(), '\t'), text.end());
	text.erase(remove(text.begin(), text.end(), '\n'), text.end());
	text.erase(remove(text.begin(), text.end(), ','), text.end());
	text.erase(remove(text.begin(), text.end(), '.'), text.end());
	text.erase(remove(text.begin(), text.end(), ';'), text.end());
	text.erase(remove(text.begin(), text.end(), '!'), text.end());
	text.erase(remove(text.begin(), text.end(), '?'), text.end());
	text.erase(remove(text.begin(), text.end(), '"'), text.end());
	text.erase(remove(text.begin(), text.end(), '\''), text.end());
	text.erase(remove(text.begin(), text.end(), '-'), text.end());
	text.erase(remove(text.begin(), text.end(), '0'), text.end());
	text.erase(remove(text.begin(), text.end(), '1'), text.end());
	text.erase(remove(text.begin(), text.end(), '2'), text.end());
	text.erase(remove(text.begin(), text.end(), '3'), text.end());
	text.erase(remove(text.begin(), text.end(), '4'), text.end());
	text.erase(remove(text.begin(), text.end(), '5'), text.end());
	text.erase(remove(text.begin(), text.end(), '6'), text.end());
	text.erase(remove(text.begin(), text.end(), '7'), text.end());
	text.erase(remove(text.begin(), text.end(), '8'), text.end());
	text.erase(remove(text.begin(), text.end(), '9'), text.end());
	if (VERBOSE) cerr << "\nmain: The string sans spaces is - " << text << "\n";
	
	bool test = testString(text);
	if (test) {
		cout << "\nmain: The longest palindrome is - " << text << " - with size " << text.size() << "\n";
	}

	return 0;
}

string readInText(char *Fname) {
	if (VERBOSE) cout << "\nreadInText: Entered function\n";
	
	int size;
	string text;
	
	ifstream t(Fname);
	t.seekg(0, ios::end);
	size = t.tellg();
	t.seekg(0, ios::beg);

	text.reserve(size);

	text.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	if (VERBOSE) cerr << "\nreadInText: The size of the file is " << size << " bytes\n";

	return text;
}

bool testString(string text) {
	int size = text.size();
	for (int i=0; i<size/2; i++) {
		if (text[i] != text[size-1-i])
			return false;
	}

	return true;
}

void eliminateExtraCharacters(string) {

}


