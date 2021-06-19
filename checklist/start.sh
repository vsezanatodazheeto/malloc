#!/bin/sh

SUBDIR="."
RESDIR="results"

function func_run() {
	for i in $@; do
		gcc "$i.c"
		# /usr/bin/time -l ./test0 0.00
		echo "$i"
		DYLD_LIBRARY_PATH=.. DYLD_INSERT_LIBRARIES=../libft_malloc.so ./a.out
	done
}

D1="test0"
D2="test1"
D3="test2"
D4="test3"
D5="test4"
D6="test5"
# D7="test6"
# D8="test7.c"
D=($D1 $D2 $D3 $D4 $D5 $D6)

# rm -rf $RESDIR && mkdir -p $RESDIR

func_run "${D[@]}"

make -sC . clean