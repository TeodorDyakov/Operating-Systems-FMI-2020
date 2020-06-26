#!/bin/bash

if [ $# -ne 1 ]; then
	exit 1
fi

users=$(ps -eo user | tail -n +2 | sort | uniq)

echo $users

for user in $users; do
	
	while read line; do
		echo $line
	done< <(ps -u $user -o pid,rss) 
done
