CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
FLAG_COV = --coverage
LIBS = -lcheck
TEST_LIBS = -lcheck -lm -lpthread

all: gcov_report

s21_string.a:
	$(CC) $(FLAGS) -c s21_insert.c s21_memchr.c s21_atoi.c s21_memcmp.c s21_memcpy.c s21_memmove.c s21_memset.c s21_sprintf.c s21_sscanf.c s21_strcat.c s21_strchr.c s21_strcmp.c s21_strcpy.c s21_strcspn.c s21_strerror.c s21_strlen.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c s21_to_lower.c s21_to_upper.c s21_trim.c
	ar rc s21_string.a *.o
	ranlib s21_string.a

test: s21_string.a
	$(CC) $(FLAGS) -c my_test_str.c -o my_test_str.o
	$(CC) my_test_str.o s21_string.a $(TEST_LIBS) -o s21_string
	./s21_string

gcov_report: test
	$(CC) $(FLAGS) --coverage my_test_str.c s21_insert.c s21_memchr.c s21_memcmp.c s21_memcpy.c s21_memmove.c s21_memset.c s21_sprintf.c s21_sscanf.c s21_strcat.c s21_strchr.c s21_strcmp.c s21_strcpy.c s21_strcspn.c s21_strerror.c s21_strlen.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_strpbrk.c s21_strrchr.c s21_strspn.c s21_strstr.c s21_strtok.c s21_to_lower.c s21_to_upper.c s21_trim.c s21_string.a $(TEST_LIBS) -o gcov_test
	chmod +x *
	./gcov_test
	gcov s21_*.gcda
	gcovr -b
	gcovr
	gcovr --html-details -o report.html
	open report.html

clean:
	rm -rf s21_string
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -rf test
	rm -rf gcov_test

rebuild: clean all
