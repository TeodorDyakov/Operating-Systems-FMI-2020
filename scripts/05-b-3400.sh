echo enter filename:
read filename
if [ ! -f "$filename" ];
then
	echo invalid filename!
	exit 1
fi

echo enter string:
IFS= read string
fgrep "$string" "$filename" > /dev/null
echo $?
