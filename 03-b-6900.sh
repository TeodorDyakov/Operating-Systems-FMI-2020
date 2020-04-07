find ~ -type f -printf '%T@ %f\n' | sort -n -r | head -n 10 | cut -d' ' -f2
