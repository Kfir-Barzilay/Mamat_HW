#!/bin/bash
# Part num 1: Check if the number of arguments is valid ( 1, or 2)
if [[ $# -lt 0 || $# -gt 2 ]]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi
#function for each course part 3-6
function func {
#part 3 make a folder
	course_num="${1:0:6}"
	folder_name="${course_num}_stat"
	rm -r "$folder_name"
	mkdir "$folder_name"
#part 4 making histogram
	pwd
	./hist.exe "$1" > "${folder_name}/histogram.txt"
#part 5 statistics
	mean=$(./mean.exe "$1")
	median=$(./median.exe "$1")
	min=$(./min.exe "$1")
	max=$(./max.exe "$1")
#part 6 succes rate
	n_bins=20
	hist=$(./hist.exe "$1" -n_bins 20 )
	pass=0
	all=0
	while read line1 line2
	do
    		first_num=$(echo "$line1" | cut -d'-' -f1)
    		third_num=$(echo "$line2")
		if (( $first_num >= 55 )); then
        		pass=$((pass + third_num))
    		fi
    		all=$((all + third_num))
	done < <(echo "$hist")
	rate=$((100*pass/all))
	echo -e  "$mean\t$median\t$min\t$max\t$rate%" >> "${folder_name}/statistics.txt"
}
# Part num 2: Check if a file matching the pattern exists.
count=0
for file in ./*
do
	if [[ $file =~ [0-9]{6}\.txt$ ]]; then
		func "${file:2}"
		count=$((count+1))
	fi
done
if [[ $count -eq 0 ]]; then
	echo "Course not found"
fi

