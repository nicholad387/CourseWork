#!/bin/bash

h=0
l=0
p=0

while getopts ":hlp" option; do
	case ${option} in
		h)
			h=1;;
		e)
			l=1;;
		p)
			p=1;;
		*)
			echo "ILLEGAL;" >&2
			exit 1
		esac
done

			if [[ $h -eq 1 ]]; then
				echo "Flag h is on"
			fi
			
			if [[ $l -eq 1 ]]; then
				echo "Flag L is on"
			fi
			
			if [[ $p -eq 1 ]]; then
				echo "Flag p is on"
			fi
exit 0