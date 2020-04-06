cat testZad2 | cut -d' ' -f4- | awk '{ print NR ". "$s }' | sort -t'"' -k2
