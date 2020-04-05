ls -l | grep -v '^d' | sort -n -k2 -r | head -n6 | tail -n5 | awk '{print $9}'
