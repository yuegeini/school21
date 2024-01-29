#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' 

cd ../

make clean
make old_test
make gcov_report


if clang-format -n *.[ch]
then printf "${GREEN}CLANG TEST DONE${NC}\n"
else printf "${RED}CLANG TEST FAILED${NC}\n"
fi

cd auto_test
if clang-format -n *.[ch]
then printf "${GREEN}CLANG TEST DONE${NC}\n"
else printf "${RED}CLANG TEST FAILED${NC}\n"
fi

cd ../s21_functions
if clang-format -n *.[ch]
then printf "${GREEN}CLANG TEST DONE${NC}\n"
else printf "${RED}CLANG TEST FAILED${NC}\n"
fi
cd ../s21_sprintf
if clang-format -n *.[ch]
then printf "${GREEN}CLANG TEST DONE${NC}\n"
else printf "${RED}CLANG TEST FAILED${NC}\n"
fi
cd ../s21_sscanf
if clang-format -n *.[ch]
then printf "${GREEN}CLANG TEST DONE${NC}\n"
else printf "${RED}CLANG TEST FAILED${NC}\n"
fi
cd ../
if clang-format -n *.[ch]
then printf "${GREEN}CLANG TEST DONE${NC}\n"
else printf "${RED}CLANG TEST FAILED${NC}\n"
fi
if valgrind --track-origins=yes -q ./old_test >log.txt
then printf "${GREEN}VALGRIND TEST DONE${NC}\n\n"
else printf "${RED}VALGRIND TEST FAILED${NC}\n"
fi
rm log.txt

if leaks -atExit -- ./old_test > log.txt
then printf "${GREEN}leaks TEST DONE${NC}\n\n"
else printf "${RED}leaks TEST FAILED${NC}\n"
fi
rm log.txt
if cppcheck *.[ch] 
then printf "${GREEN}CPPCHECK DONE${NC}\n"
else printf "${RED}CPPCHECK FAILED${NC}\n"
fi
cd s21_functions
if cppcheck *.[ch] 
then printf "${GREEN}CPPCHECK DONE${NC}\n"
else printf "${RED}CPPCHECK FAILED${NC}\n"
fi
cd ../
make clean_1 