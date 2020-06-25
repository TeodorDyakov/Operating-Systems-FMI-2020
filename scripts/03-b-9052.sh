cat population.csv | grep 'Bulgaria' | sort -r -n -t',' -k4 | head -n 1 | cut -d',' -f3
