#!bin/bash

RESET="\033[0m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"

BINARY1=test

rm -rf $MAIN1 $BINARY1 $RES1 valgrind.log

index=$1

clang++ -Wall -Werror -Wextra -g3 -std=c++98 $index.cpp -o $BINARY1
valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log ./$BINARY1
# rm -rf $BINARY1

