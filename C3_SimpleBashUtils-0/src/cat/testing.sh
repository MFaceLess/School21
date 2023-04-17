#!/bin/bash

./s21_cat -bnte compare.txt  >> file1.txt
cat -bnte compare.txt  >> file2.txt
vimdiff file1.txt file2.txt
rm file1.txt
rm file2.txt
