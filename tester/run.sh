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
MAIN2=test2.cpp
BINARY1=test1
BINARY2=test2
RES1=res1.txt
RES2=res2.txt

rm -rf $MAIN1 $MAIN2 $BINARY1 $BINARY2 $RES1 $RES2 valgrind.log

if (($1))
then
	sed "s/STL/1/g" $1.cpp > $MAIN1
	sed "s/STL/0/g" $1.cpp > $MAIN2
	clang++ -Wall -Werror -Wextra -std=c++98 $MAIN1  -o $BINARY1
	clang++ -Wall -Werror -Wextra -fstandalone-debug -g3 -std=c++98 $MAIN2 -o $BINARY2
	if [ -e $BINARY2 ]
	then
		./$BINARY1 > $RES1
		valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log ./$BINARY2 > $RES2
		if diff -y $RES1 $RES2
		then
			printf "$BOLDGREEN Check $1 : [success]$RESET\n"
		else
			printf "$BOLDRED Check $1 : [error]$RESET\n"
		fi
	fi
else
	NB_TEST=9
	index=1
	while ((index < NB_TEST))
	do
		sed "s/STL/1/g" $index.cpp > $MAIN1
		sed "s/STL/0/g" $index.cpp > $MAIN2
		clang++ -Wall -Werror -Wextra -std=c++98 $MAIN1  -o $BINARY1
		clang++ -Wall -Werror -Wextra -g3 -std=c++98 $MAIN2 -o $BINARY2
		./$BINARY1 > $RES1
		valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log ./$BINARY2 > $RES2
		if diff $RES1 $RES2
		then
			printf "$BOLDGREEN Check $index : [success]$RESET\n"
		else
			printf "$BOLDRED Check $index : [error]$RESET\n"
		fi
		rm -rf $MAIN1 $MAIN2 $BINARY1 $BINARY2 $RES1 $RES2
		((index+=1))
	done
fi





