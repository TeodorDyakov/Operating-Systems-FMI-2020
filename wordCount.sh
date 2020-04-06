tr -d "[:punct:]" < alice | tr " " "\n" | sort | uniq -c | sort -n
