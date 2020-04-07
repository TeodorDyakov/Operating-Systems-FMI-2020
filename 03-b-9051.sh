cat population.csv | grep ',2008,' | grep '[0-9]*$' -o | awk '{s+=$1} END {printf "%.0f", s}'
