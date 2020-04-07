cat population.csv | grep ',2008,' | cut -d',' -f4 | awk '{s+=$1} END {printf "%.0f", s}'
