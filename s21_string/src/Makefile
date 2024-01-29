########## сокращения ##########
CC =gcc
CFLAGS = -Wall -Werror -Wextra
LIB = s21_functions/s21_string.c 
TEST = auto_test/s21_string_test.c
LIBEX = s21_functions/s21_string_ex.c
SCAN = s21_sscanf/s21_sscanf.c
PRINT = s21_sprintf/s21_sprintf.c


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


 all: clean s21_string.a


####### тестирование с библеотекой CHECK #######

check.c: s21_string.a
	$(CH) auto_test/s21_string_test.check > $@
	clang-format -i check.c
	

test: 
	$(CC) $(TFLAGS) $(LIB) $(LIBEX) $(SCAN) $(PRINT) check.c  -o test
	 ./test
	 $(RM) test
################################################


### тестирование с помощью файла .с ###
old_test: s21_string.a 
	$(CC) $(CFLAGS) $(TEST) $<  -o $@
	./old_test
#######################################


#### компиляция статической библиотеки ####
s21_string.a: s21_string.o s21_string_ex.o s21_sscanf.o s21_sprintf.o
	ar rcs $@ $< s21_string_ex.o s21_sscanf.o s21_sprintf.o
	ranlib $@
	rm $< s21_string_ex.o s21_sscanf.o s21_sprintf.o

s21_string.o: $(LIB)
	$(CC) -c $(LIB) -o $@
s21_string_ex.o: $(LIBEX)
	$(CC) -c $(LIBEX) -o $@
s21_sscanf.o: $(SCAN)
	$(CC) -c $(SCAN) -o $@
s21_sprintf.o: $(PRINT)
	$(CC) -c $(PRINT) -o $@
	
###########################################


##################################GCOV_REPORT#####################################
gcov_report: s21_string.a check.c
	$(CC) $(CFLAGS) --coverage $(LIB) $(LIBEX) $(SCAN) $(PRINT)  check.c  $(TFLAGS) -lm -o gcov_test 
	

	./gcov_test
	lcov -t "test" -o test_report.info -c -d .
	genhtml -o report test_report.info
	rm -rf *.o *.a  *.gch *.gcno test  gcov_test
##################################################################################


############## полная очистка ################ 
clean:
	$(RM) old_test test s21_string.a  *.gcda  *.gch *.gcno report test_report.info ret.txt 

clean_1:
	$(RM) old_test  test s21_string.a *.gcda ret.txt 
##############################################


############# ШПОРА ПО СОКРАЩЕНИЯМ ###################
# $@ - имя цели(целевого файла)                      #
# $< - имя первой зависимости(после двоеточия)       #
# $^ - имена всех зависимостей в цели (через пробел) #
######################################################
