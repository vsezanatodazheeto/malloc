#!/bin/bash

clear

make > /dev/null
if [ $? -ne 0 ];then
	exit
fi

SUBDIR="tests"
RESDIR="tests_result"

function func_compile() {
	for i in $@; do
		gcc "$SUBDIR/$i.c" -lft_malloc -L. -Iinclude -o "$SUBDIR/$i"
	done
}

function func_run() {
	for i in $@; do
		# ./$SUBDIR/$i &> /dev/null | tee "$RESDIR/$i.txt"
		./$SUBDIR/$i &> "$RESDIR/$i.txt"
	done
}

D1="test_1"
D2="test_2"
D3="test_3"
D=($D1 $D2 $D3)

func_compile "${D[@]}"

rm -rf $RESDIR && mkdir -p $RESDIR

func_run "${D[@]}"
