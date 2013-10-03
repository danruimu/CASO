#!/bin/bash

PROG=$PWD/write200mb
DD1="dd if=/dev/zero of=file.dd1 count=3276800 bs=64"
DD2="dd if=/dev/zero of=file.dd2 count=409600 bs=512"
DD3="dd if=/dev/zero of=file.dd3 count=25600 bs=8192"

if [ ! -e $PROG ]
then
	make
fi

OUTPROG=out.prog.txt
OUTDD1=out.dd1.txt
OUTDD2=out.dd2.txt
OUTDD3=out.dd3.txt

for i in $OUTPROG $OUTDD1 $OUTDD2 $OUTDD3
do
	if [ -e $i ]
	then
		rm -f $i
	fi
done

for i in `seq 1 5`
do
	echo "----------- Execution $i ------------" >> $OUTPROG
	$PROG >> $OUTPROG
done

for i in `seq 1 5`
do
	echo "----------- Execution $i ------------" >> $OUTDD1
	/usr/bin/time -o $OUTDD1 -a $DD1
done

for i in `seq 1 5`
do
	echo "----------- Execution $i ------------" >> $OUTDD2
	/usr/bin/time -o $OUTDD2 -a $DD2
done

for i in `seq 1 5`
do
	echo "----------- Execution $i ------------" >> $OUTDD3
	/usr/bin/time -o $OUTDD3 -a $DD3
done
