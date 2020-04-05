awk '/^.*(\t| )'"$1"'\// { print $1; }' < /etc/services
