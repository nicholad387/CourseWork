#!/bin/bash
# array_loop.s


array=(1 2 "three" 4 "five")

for i in ${!array[@]}; do
    echo "[${i}]: ${array[$i]}"
done

for elem in ${array[@]}; do
    echo ${elem}
done

for i in {1..10}; do
    echo "[${i}]: ${array[$i]}"
done
