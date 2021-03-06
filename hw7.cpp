/*
 * hw7.cpp written by William Halsey
 * whalsey@vols.utk.edu
 *
 * Wednesday 2 March 2016
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <ctime>

#define usage "\nUSAGE: ./{Executable} {Input Filename}.txt\n"
#define VERBOSE false

using namespace std;

string readInText (char *);
bool testString (string);
int max (int, int);
void printarr(int, int**);

int main (int argc, char *argv[]) {
	// check cla
	if (argc != 2) {
		cerr << usage;
		exit(1);
	}

	string text = readInText(argv[1]);
	if (VERBOSE) cerr << "\nmain: The input string is - " << text << "\n";

	// strip special characters from string
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
	
	// convert to all lowercase
	transform(text.begin(), text.end(), text.begin(), ::tolower);	
	
	if (VERBOSE) cerr << "\nmain: The string sans spaces is - " << text << "\n";

	// === BEGIN TIMING === //
	clock_t time = clock();

	// Test to see if the input string is already a Palindrome
	bool test = testString(text);
	if (test) {
		cerr << "\nmain: The longest palindrome is - " << text << " - with size " << text.size() << "\n";
		return 0;
	}

	// FIND THE LONGEST PALINDROMIC SUBSTRING
	int size = text.size();
	int **palindrome = new int *[size];
	for (int i=0; i<size; i++) {
		palindrome[i] = new int[size];
	}
	
	if (VERBOSE) cerr << "\nmain: palindrome[size/2][size/2] is " << palindrome[size/2][size/2]	<< "\n";

	for (int sub=0; sub<size; sub++) {
	if (VERBOSE) cerr << "\nmain: for: sub is " << sub << "\n";

		for (int i=0; i<size-sub; i++) {
			// for subsequence of length 1
			if (sub == 0) {
				palindrome[i][i] = 1;
				continue;
			}

			// for subsequence of length 2
			if (text[i] == text[i+sub] && sub == 1) {
				palindrome[i][i+sub] = 2;
				continue;
			}
			
			// otherwise
			if (text[i] == text[i+sub]) {
				if (VERBOSE) cerr << "\nmain: for: if: found a match " << text[i] << " at indices " << i << " and " << i+sub << "\n";
				palindrome[i][i+sub] = 2 + palindrome[i+1][i+sub-1];
			} else {
				palindrome[i][i+sub] = max(palindrome[i][i+sub-1], palindrome[i+1][i+sub]);
			}
		}
	}

	// === END TIMING === //
	time = clock() - time;
	cout << (float)time/CLOCKS_PER_SEC << ", ";

	cerr << "\nmain: The longest palindrome is length " << palindrome[0][size-1] << "\n";

	if (VERBOSE) printarr(size, palindrome);

	// reconstruct string
	string pal = text;
	for (int i=0; i<size; i++) {
		pal[i] = '\0';
	}
	int row = 0;
	int col = size-1;
	int n = 0;

	for (int i=0; i<size; i++) {
		// check for base case
		if (palindrome[row][col] == 1) {
			pal[n] = ' ';
			pal[n+1] = text[row];
			pal[n+2] = ' ';
			break;
		}

		// check for two neighbors
		if (palindrome[row][col] == 2) {
			pal[n] = text[row];
			pal[n+1] = ' ';
			pal[size-n-1] = text[row];
			break;
		}

		// check to see that current is bigger than children
		if (palindrome[row][col] > max(palindrome[row][col-1], palindrome[row+1][col])) {
			pal[n] = text[row];
			pal[size-n-1] = text[row];
			n++;
			row++;
			col--;
		} else {
			if (max(palindrome[row][col-1], palindrome[row+1][col]) == palindrome[row][col-1]){
				col--;
			} else {
				row++;
			}
		}
		if (VERBOSE) cerr << "\nmain: for: Pal is " << pal << "\n";
	}

	pal.erase(remove(pal.begin(), pal.end(), '\0'), pal.end());
	cerr << "\nmain: The palindromic subsequence is\n" << pal << "\n";

	// cleanup
	for (int i=0; i<size; i++) {
		delete palindrome[i];
	}
	delete palindrome;

	return 0;
}

string readInText (char *Fname) {
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

bool testString (string text) {
	int size = text.size();
	for (int i=0; i<size/2; i++) {
		if (text[i] != text[size-1-i])
			return false;
	}

	return true;
}

int max (int a, int b) {
	return (a > b) ? a : b;
}

void printarr (int size, int** a) {
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			cout << a[i][j] << "\t";
		}
		cout << "\n";
	}
	return;
}
