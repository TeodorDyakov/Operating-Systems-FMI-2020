read num
grep -v "^#" /etc/services | grep "\s$num/" | awk '{print $1}'
