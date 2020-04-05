
grep -v "^#" /etc/services | awk '{$2 ~ "69/udp" print $1 }'
