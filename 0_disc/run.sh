#!/bin/bash

PROG=$PWD/write200mb

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

echo -n "Executing write200mb"
for i in `seq 1 5`
do
	echo -n "."
	echo "----------- Execution $i ------------" >> $OUTPROG
	$PROG >> $OUTPROG
done
echo " "
echo "write200mb finished!"

echo -n "Executing DD1"
for i in `seq 1 5`
do
	echo -n "."
	echo "----------- Execution $i ------------" >> $OUTDD1
	dd if=/dev/zero of=file.dd1 count=3276800 bs=64 2>> $OUTDD1
done
echo " "
echo "DD1 finished!"

echo -n "Executing DD2"
for i in `seq 1 5`
do
	echo -n "."
	echo "----------- Execution $i ------------" >> $OUTDD2
	dd if=/dev/zero of=file.dd2 count=409600 bs=512 2>> $OUTDD2
done
echo " "
echo "DD2 finished!"

echo -n "Executing DD3"
for i in `seq 1 5`
do
	echo -n "."
	echo "----------- Execution $i ------------" >> $OUTDD3
	dd if=/dev/zero of=file.dd3 count=25600 bs=8192 2>> $OUTDD3
done
echo " "
echo "DD3 finished!"

rm -f file.dd1 file.dd2 file.dd3

echo "-----------------Write 200MB program-------------------" > times.txt
cat $OUTPROG >> times.txt
echo "-------------------------------------------------------" >> times.txt
echo "-----------------Write DD first case-------------------" >> times.txt
cat $OUTDD1 >> times.txt
echo "-------------------------------------------------------" >> times.txt
echo "-----------------Write DD second case------------------" >> times.txt
cat $OUTDD2 >> times.txt
echo "-------------------------------------------------------" >> times.txt
echo "-----------------Write DD third case-------------------" >> times.txt
cat $OUTDD2 >> times.txt
echo "-------------------------------------------------------" >> times.txt

rm -f $OUTPROG $OUTDD1 $OUTDD2 $OUTDD3

echo "You will find the timings at ./times.txt"
