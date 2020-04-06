files=$(ls)
mkdir a b c

for str in $files
do
	lines=$(wc -l $str | cut -d' ' -f1)
	if [ $lines -lt $1 ]
		then
		mv $str a
	elif [ $lines -gt $2 ]
		then
		mv $str b
	else
		mv $str c
	fi
	
done
