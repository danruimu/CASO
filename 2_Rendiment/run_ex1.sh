#!/bin/bash

PROG=(sleep_2 sbrk sbrk-incdec sched_yield getpid fork_waitpid)

for i in ${PROG[*]}
do
	if [ ! -e $i ]
	then
		make $i
	fi
	if [ -e $i.out ]
	then
		rm -f $i.out
	fi

	echo -n "Executing $i"
	for j in `seq 1 10`
	do
		echo "----------Execution $j----------" >> $i.out
		$PWD/$i >> $i.out
		echo "--------------------------------" >> $i.out
		echo -n "."
	done

	echo " "

	if [ ! -d $PWD/timing ]
	then
		mkdir $PWD/timing
	fi
	mv $i.out $PWD/timing/
done

make clean
