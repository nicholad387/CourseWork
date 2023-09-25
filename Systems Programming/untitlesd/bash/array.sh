#!/bin/bash
# array.s

# Method 1:
declare -a array
array[0]="hi"
array[1]="bye"

# Method 2
newarray=(1 2 "three" 4 "five")

# Print elements
echo ${array[0]}
echo ${array[1]}

# Print all elements
echo ${array[*]}
echo ${array[@]}

# Print the number of elements
echo ${#array[*]}

# Print a list of indices
echo ${!array[@]}
