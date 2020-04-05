$file
if [ $(wc -l $1 | cut -d' ' -f1) -gt $(wc -l $2 | cut -d' ' -f1) ]
	then
		file=$1
	else
		file=$2 
fi
 
cat $file | cut -d' ' -f4- | sort > $file.songs 
