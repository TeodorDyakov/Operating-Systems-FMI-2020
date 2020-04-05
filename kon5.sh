find / -name "*" -user $(whoami) 2>&1 | grep -v "Permission denied" | wc -l"
