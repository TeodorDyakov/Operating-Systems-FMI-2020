cnt=0
max=0
while read -n1 c; do
	if [ "$c" = "{" ]
	then
		((cnt=cnt+1))
	elif [ "$c" = "}" ]
	then
		((cnt=cnt-1))
	fi

	if [ $max -lt $cnt ]
	then
		max=$cnt
	fi
done < $1

echo $max
