#!/bin/bash

make s21_string.a
gcc -g my_test_str.c s21_string.a -o testValgrind -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./testValgrind
