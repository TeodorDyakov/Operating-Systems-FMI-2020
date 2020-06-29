tr -d "[:punct:]" < alice | tr " " "\n" | sort | uniq -c | sort -n
egrep -o '\b\w+\b' alice_in_wonderland.txt | sort | uniq -c | sort -t' ' -k1 -n
