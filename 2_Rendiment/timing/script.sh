#!/bin/bash

for i in `ls`
do
	echo `cat $i | grep -v \-`
done
