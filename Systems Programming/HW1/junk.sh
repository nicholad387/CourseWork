#!/bin/bash
#
#I pledge my honor that i have abided by the honor pledge

h=0
l=0
p=0

readonly Junk_dir=~/.junk

FILENAME=$(basename $0)

interface() { #heredoc
	cat << EQF
Usage: $FILENAME [-hlp] [list of files]
   -h: Display help.
   -l: List junked files.
   -p: Purge all files.
   [list of files] with no other arguments to junk those files.
EQF
}

while getopts ":hlp" option; do
	case ${option} in
		h)
			h=1;;
		l)
			l=1;;
		p)
			p=1;;
		*)
			echo "Error: Unknown option '-${OPTARG}'.">&2
			interface 
			exit 1
		esac
done

total=$(( h + l + p ))
			if [[ $total -gt 1 ]]; then
				echo "Error: Too many options enabled.">&2
				interface
				exit 1
			elif [[ $# -gt 1 ]] && [[ $(( $# - total )) -ne $# ]]; then
				echo "Error: Too many options enabled.">&2
				interface
				exit 1
			elif [[ $# -eq 0 || $h -eq 1 ]]; then
				interface
				exit 0
			fi
#make junk file 
				mkdir -p "$Junk_dir"
				
#do the l command stuff
			if [[ $l -eq 1 ]]; then
				ls -lAF $Junk_dir
				exit 0
			fi
#do purge stuff
			if [[ $p -eq 1 ]]; then
				rm -r $Junk_dir/* 2>/dev/null
				rm -r $Junk_dir/.* 2>/dev/null
			fi
			
shift "$((OPTIND-1))"
#check if files given exist
			for file in "$@" #check if files exisst
			do
				if [[ -e ${file} ]]; then
					mv $file $Junk_dir
				else
					echo "Warning: '""$file"" not found." >&2
					exit 0
				fi
			done

exit 0
