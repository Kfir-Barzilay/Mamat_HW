#!/bin/bash
#initiate final file
touch results.csv
#our site url
site="https://ynetnews.com/category/3082"
#getting the site content and extracting links
data=$(wget --no-check-certificate -O - $site 2>/dev/null)
links=$(echo "$data"|grep -o "https://www.ynetnews.com/article/[a-zA-Z0-9]*")
links=$(echo "$links" | sort  | uniq -i)
#count the number of sites
count=$(echo "$links" | wc -l)
#counting the occurences of the names for each article
echo "$count">>results.csv
while read -r link; do
article=$(wget --no-check-certificate -O - $link 2>/dev/null)
	c_N=$(echo "$article" | grep -o "Netanyahu" | wc -l)
	c_G=$(echo "$article" | grep -o "Gantz" | wc -l)
	c_B=$(echo "$article" | grep -o "Bennett" | wc -l)
	c_P=$(echo "$article" | grep -o "Peretz" | wc -l)
	if [ "$c_N" -eq 0 ] && [ "$c_G" -eq 0 ] &&\
		[ "$c_B" -eq 0 ] && [ "$c_P" -eq 0 ]; then
	echo "$link, -">>results.csv
	else
		echo "$link, Netanyahu, $c_N, Gantz,"\
		"$c_G, Bennett, $c_B, Peretz, $c_P">>results.csv
	fi
done <<< "$links"