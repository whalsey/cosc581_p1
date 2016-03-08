#!/bin/bash
#
# test.sh written by William Halsey
# whalsey@vols.utk.edu
#
# Tuesday 8 March 2016
#

numbers="10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000"

for num in $numbers; do
	printf $num
	printf ", "
	for i in 1 2 3; do
		./randGen $num > random.txt
		./palindrome random.txt
	done
	echo ""
done
