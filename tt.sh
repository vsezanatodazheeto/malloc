#!/bin/sh

clear

make
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
		./$SUBDIR/$i &> /dev/null | tee "$RESDIR/$i.txt"
		# ./$SUBDIR/$i
	done
}

D1="test_1"
D2="test_2"
D3="test_3"
D=($D1 $D2 $D3 $D4 $D5 $D6 $D7 $D8 $D9 $D10 $D11 $D12 $D13 $D14 $D15 $D16 \
   $D17 $D18 $D19 $D20)

func_compile "${D[@]}"

rm -rf $RESDIR && mkdir -p $RESDIR

func_run "${D[@]}"
