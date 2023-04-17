#!/bin/bash

./s21_grep -oi 'A.C' reg.txt  >> file1.txt
grep -oi 'A.C' reg.txt  >> file2.txt
vimdiff file1.txt file2.txt
rm file1.txt
rm file2.txt
