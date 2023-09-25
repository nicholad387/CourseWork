#!/bin/bash
# function.s

height=3

# $(( integer arithmetic expression ))
# You cannot do floating point arithmetic directly in bash
# Use bc and pipe to do that.

function volume {
    vol=$(( $height * $1 * $2 ))
    echo $vol
}

volume 10 20
result=$(volume 10 20)
echo "Result: $result"
