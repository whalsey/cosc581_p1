##
# makefile written by William Halsey
# whalsey@vols.utk.edu
# Monday 7 March 2016
#

all: palindrome rand_string

palindrome: 
	g++ hw7.cpp -o palindrome

rand_string:
	gcc randString.c -o randGen

clean:
	rm -f palindrome randGen
