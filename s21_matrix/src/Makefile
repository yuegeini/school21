CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV = --coverage
OS = $(shell uname)
NAME = s21_matrix

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck 
endif

TEST_COMPILE = $(CC) $(CFLAGS) tests/*.c $(CHECK_FLAGS) $(NAME).a

all: clean test

leaks: clean $(NAME).a
	$(TEST_COMPILE)
	valgrind --leak-check=full --tool=memcheck --show-leak-kinds=all --track-origins=yes --verbose -q ./a.out

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

style:
	clang-format -i *.c *.h tests/*.c tests/*.h

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug *.txt ./tests/make* ./report/* gcov_report

test: clean $(NAME).a
	$(TEST_COMPILE)
	-./a.out

gcov_report: clean
	${CC} -c $(CFLAGS) ${GCOV} ${NAME}.c
	ar rc $(NAME).a $(NAME).o
	ranlib $(NAME).a
	${CC} -o $@ ${GCOV} tests/*.c ${NAME}.a ${CHECK_FLAGS}
	-./$@
	lcov -t ${NAME} -o ${NAME}.info -c -d .
	genhtml -o report ${NAME}.info;

$(NAME).a: $(NAME).o
	ar rcs $@ $^
	ranlib $@

$(NAME).o:
	$(CC) $(CFLAGS) -c $(NAME).c

