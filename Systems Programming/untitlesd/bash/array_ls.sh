#!/bin/bash
# array_ls.s

# Try: allfiles=$(ls -l)
# allfiles=($(ls))
allfiles=$(ls)


for i in ${!allfiles[@]}; do
    echo "[${i}]: ${allfiles[$i]}"
done


for elem in ${allfiles[@]}; do
    echo ${elem}
done
