#! /bin/bash

#enter the packets into variable
packets=$(cat | tr -d ' ')

while read line
do
	#part 1: organizing the rules. 
	# Remove commas and spaces in the rule line
	# Remove the comments in the rule line
	rule_line=$(echo "$line" | tr -d ',' | tr -d ' ')
	rule_no_comments=$(echo "$rule_line" | sed -e 's/#.*//')
	rule_1=$(echo "$rule_no_comments" | sed -e 's/dst-ip/*dst-ip/g')
	rule_2=$(echo "$rule_1" | sed -e 's/src-port/*src-port/g')
	splited_rule=$(echo "$rule_2" | sed -e 's/dst-port/*dst-port/g')

	#part 2: spliting "splited_rule" to separate variables and execute them.
	if [[ "$splited_rule" != "" ]]; then
		IFS='*' read -r source_ip destination_ip \
		source_port destination_port <<< "$splited_rule"
    	
		#piping the output
		filtered_packets+=$(echo "$packets" |
		./firewall.exe "$source_ip" |
		./firewall.exe "$destination_ip" |
		./firewall.exe "$source_port" |
		./firewall.exe "$destination_port")
		filtered_packets+="\n"
	fi

done < "$1"

#part 3: add line breaks before, remove empty lines, sort, remove duplicates.
echo -e "$filtered_packets" | sed "s/src-ip/\n&/g" | sed '/^$/d' | sort -u
