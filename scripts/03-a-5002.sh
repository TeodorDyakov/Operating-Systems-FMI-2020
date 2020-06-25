cut -d: -f5 passwd.txt | cut -d':' -f2 | tr -d , | grep -o -w '\w\{7,\}'
