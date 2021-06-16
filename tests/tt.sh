#!/bin/bash

if [ $? -ne 0 ];then
	exit
fi

SUBDIR="."
RESDIR="results"

# function func_compile() {
# 	for i in $@; do
# 		gcc "$SUBDIR/$i.c" -lft_malloc -L.. -I../include -I../libft_printf/include -o "$SUBDIR/$i"
# 	done
# }

function func_run() {
	for i in $@; do
		DYLD_LIBRARY_PATH=../ ./$SUBDIR/$i &> "$RESDIR/$i.txt"
		# ./$SUBDIR/$i &> /dev/null | tee "$RESDIR/$i.txt"
		# ./$SUBDIR/$i &> "$RESDIR/$i.txt"
	done
}

D1="test_1"
D2="test_2"
D3="test_3"
D=($D1 $D2 $D3)

make -sC .
rm -rf $RESDIR && mkdir -p $RESDIR

func_run "${D[@]}"

make -sC . clean