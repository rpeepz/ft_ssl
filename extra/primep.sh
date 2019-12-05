#!/bin/bash
if [ -z $1 ]
then
	echo "Usage: ./primep.sh (begin) { end }"
	echo "checks for primality"
	exit
fi
for i in $(seq $1 $2); do
	./ft_ssl primep $i
done
