grep -e 'a, SI' passwd.txt | cut -d':' -f1 | cut -c3-4 | sort -r | uniq -c | head -1
