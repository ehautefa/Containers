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

MAIN1=test1.cpp
BINARY1=test1

index=$1
sed "s/STL/1/g" $index.cpp > $MAIN1
clang++ -Wall -Werror -Wextra -std=c++98 $MAIN1  -o $BINARY1
./$BINARY1 

rm -rf $MAIN1 $BINARY1




