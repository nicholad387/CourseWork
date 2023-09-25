#!/bin/bash
# here2.s

echo "Type a path: "
read path
if [[ $path = "help" ]]; then
    cat << EOF
The current working directory is: $(pwd)
All you need to do is to type it!
EOF
elif [[ $path = $(pwd) ]]; then
    echo "Good job!"
else
    echo "Type help next time!"
fi
