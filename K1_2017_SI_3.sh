cat passwd.txt | cut -d':' -f5 | cut -d' ' -f1 | egrep 'a$' | sort | uniq -c | sort -n | tail -n1
