#!/bin/bash

if [ $# -ne 1 -o $(id -u) -ne 0 ]; then
	exit 1
fi

users=$(ps -eo user | tail -n +2 | sort | uniq)

total_rss=0

for user in $users; do
	
	while read line; do
		echo $line
		rss=$(echo $line | awk '{print $2}') 
		total_rss=$(($total_rss + $rss))
	done< <(ps -u $user -o pid,rss | tail -n +2)
		
	if [ $total_rss -gt $1 ]; then
		max_rss_pid=$(ps -u $user -o pid,rss | tail -n +2 | sort -n -k2 | awk 			'{print $1'})
		kill -s SIGTERM $max_rss_pid
		sleep 2		
		kill -s SIGKILL $max_rss_pid		
	fi 
done
