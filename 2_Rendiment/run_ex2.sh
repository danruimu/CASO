#!/bin/bash

PROG_W=write-to-disk-plot
PROG_R=read-from-disk-plot

if [ $# -ne 3 ]
then
	echo "USAGE: `basename $0` FILE INIT_SIZE END_SIZE"
	echo "    FILE: file where to read and write"
	echo "    INIT_SIZE: size in MB of the first file writed and readed"
	echo "    END_SIZE: size in MB of the final file writed and readed"
	echo "    NOTE that increments would be of 10MB"
	exit 1
fi

FILE=$1
INIT_SIZE=$2
END_SIZE=$3

if [ ! -d plots ]
then
	mkdir plots
fi

echo "Starting executions!"
echo " "

for i in $PROG_W $PROG_R
do
	if [ -e plots/$i.out ]
	then
		rm -f plots/$i.out
	fi

	if [ ! -e $i ]
	then
		make $i
	fi
	
	N=$INIT_SIZE
	echo -n "Executing $i"
	while [ $N -le $END_SIZE ]
	do
		./$i $FILE $N >> plots/$i.out
		let N=$N+10
		echo -n "."
	done
	echo " "
done

echo " "
echo "Executions finished! Let's start to generate the plots :-)"

cd plots

gnuplot -e "set xlabel 'Size in MB'; set ylabel 'Bandwidth in MB/s'; plot 'write-to-disk-plot.out' using 1:2 with lines title 'Write'; set term png; set output 'write.png'; replot;"
gnuplot -e "set xlabel 'Size in MB'; set ylabel 'Bandwidth in MB/s'; plot 'read-from-disk-plot.out' using 1:2 with lines title 'Read'; set term png; set output 'read.png'; replot;"

cd ../

echo "Plots generated! You will find two images at plots folder :-)"
echo "Bye!"
