find . -printf "%f %n \n" |  sort -k2 -n | cut -d' ' -f 2
