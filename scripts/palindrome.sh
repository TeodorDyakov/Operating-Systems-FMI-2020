#!/bin/bash
#find palidromes of length from 3 to 7
egrep '\b(\w?)(\w?)(\w)\w\3\2\1\b' -rohI $1

