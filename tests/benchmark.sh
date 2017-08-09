#!/bin/bash
temp=$(mktemp)
make > /dev/null

echo "Instances: "
for i in {1000..40000..400}
do
	error=1
	while [ $error -gt 0 ]
	do
		./gen -var 3 -dep 4 -ivar 2 -idep 2 -instances $i > $temp 2> /dev/null
		error=$?
	done
	printf "$i "
	./test < $temp
done


echo "Vars: "
for i in {1..100..1}
do
	error=1
	while [ $error -gt 0 ]
	do
		./gen -var $i -dep 3 -ivar 2 -idep 2 -instances 4000 > $temp 2> /dev/null
		error=$?
	done
	printf "$i "
	./test < $temp
done


echo "Independent Vars: "
for i in {1..100..1}
do
	error=1
	while [ $error -gt 0 ]
	do
		./gen -var 2 -dep 3 -ivar $i -idep 2 -instances 4000 > $temp 2> /dev/null
		error=$?
	done
	printf "$i "
	./test < $temp
done

echo "Dependencies: "
for i in {1..120..1}
do
	error=1
	while [ $error -gt 0 ]
	do
		./gen -var 3 -dep $i -ivar 2 -idep 2 -instances 4000 > $temp 2> /dev/null
		error=$?
	done
	printf "$i "
	./test < $temp
done

echo "Dependencies of Independent Vars: "
for i in {1..120..1}
do
	error=1
	while [ $error -gt 0 ]
	do
		./gen -var 3 -dep 2 -ivar 2 -idep $i -instances 4000 > $temp 2> /dev/null
		error=$?
	done
	printf "$i "
	./test < $temp
done

rm $temp