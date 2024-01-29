########## сокращения ##########
CC =gcc
CFLAGS = -Wall -Werror -Wextra
ARM = s21_arithmetic.c
COMP = s21_comparison.c
CONVPAR = s21_convert.c
ANTR = s21_another_dec.c
TEST = auto_tests/21_decimal_test.c

RM = rm -rf
CH = checkmk clean_mode=1 
###############################


################ определение ОС ####################
 UNAME  := $(shell uname -s)
 ifeq ($(UNAME), Linux)
 	TFLAGS = -lpthread -pthread -lrt -lm -lsubunit
 endif
ifeq ($(UNAME), Darwin)
	TFLAGS = -lcheck
endif
####################################################


 all: clean s21_decimal.a


####### тестирование с библеотекой CHECK #######

check.c: s21_decimal.a
	$(CH) auto_test/s21_decimal_test.check > $@
	clang-format -i check.c
	

test: 
	$(CC) $(TFLAGS)  check.c  -o test
	 ./test
	 $(RM) test
################################################


### тестирование с помощью файла .с ###
old_test: s21_decimal.a 
	$(CC) $(CFLAGS) $(TEST) $<  -o $@
	./old_test
#######################################


#### компиляция статической библиотеки ####
s21_decimal.a: s21_arithmetic.o s21_comparison.o s21_convert.o s21_another_dec.o
	ar rcs $@ $< s21_comparison.o s21_convert_pars.o s21_another_dec.o
	ranlib $@
	rm $< s21_comparison.o s21_convert.o s21_another_dec.o

s21_arithmetic.o: $(ARM)
	$(CC) -c $(ARM) -o $@
s21_comparison.o: $(COMP)
	$(CC) -c $(COMP) -o $@
s21_convert.o: $(CONVPAR)
	$(CC) -c $(CONVPAR) -o $@
s21_another_dec.o: $(ANTR)
	$(CC) -c $(ANTR) -o $@
	
###########################################


##################################GCOV_REPORT#####################################
gcov_report: s21_decimal.a check.c
	$(CC) $(CFLAGS) --coverage $(ARM) $(COMP) $(CONVPAR) $(ANV)  check.c  $(TFLAGS) -lm -o gcov_test 
	

	./gcov_test
	lcov -t "test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	rm -rf *.o *.a  *.gch *.gcno test  gcov_test
##################################################################################


############## полная очистка ################ 
clean:
	$(RM) old_test test s21_decimal.a  *.gcda  *.gch *.gcno report test_report.info ret.txt 

clean_1:
	$(RM) old_test  test s21_decimal.a *.gcda ret.txt 
##############################################


############# ШПОРА ПО СОКРАЩЕНИЯМ ###################
# $@ - имя цели(целевого файла)                      #
# $< - имя первой зависимости(после двоеточия)       #
# $^ - имена всех зависимостей в цели (через пробел) #
######################################################
