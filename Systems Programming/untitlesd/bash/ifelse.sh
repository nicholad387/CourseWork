#!/bin/bash
# ifelse.s

CURR_PATH=$(pwd)
if [[ $CURR_PATH = "/Users/shudonghao/392demo/bash" ]]; then
    echo "Yay!"
else
    echo "Nay!"
fi
