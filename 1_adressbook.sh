#!/bin/bash

createaddressbook(){
	echo "Enter the filename:"
	read fname
	if [ -e "$fname" ]; then
		echo "File Already Exists!!"
	else
		touch "$fname"
		echo "File $fname Created!!"
	fi	
}

insertrecord(){
	echo "Enter the name of Address book:"
	read name
	while true; do
		echo "To add a record, enter in format: lastname,firstname,email,mobile_no"
		echo "To quit, press 'q'"
		read newrecord
		if [ "$newrecord" == "q" ]; then
			break
		fi
		echo "$newrecord" >> "$name"
		echo "Record inserted successfully."
	done
}

viewrecords(){
	echo "Enter the name of Address book:"
	read name
	if [ -e "$name" ]; then
		cat "$name"
	else
		echo "File does not exist!"
	fi
}

modifyrecord(){
	echo "Enter the name of Address book:"
	read name
	if [ ! -e "$name" ]; then
		echo "File does not exist!"
		return
	fi
	echo "Enter Last name to modify record or press 'q' to exit:"
	read lname
	if [ "$lname" == 'q' ]; then
		return
	fi
	
	# Search for matching records and list them with line numbers
	grep -n "^$lname" "$name"
	if [ $? -ne 0 ]; then
		echo "No record found!"
		return
	fi
	
	echo "Enter the line number you would like to edit:"
	read linenumber
	echo "What would you like to change it to? Use the format: lastname,firstname,email,mobile_no"
	read erecord
	
	# Replace the specific line with new record
	sed -i "${linenumber}s/.*/$erecord/" "$name"
	echo "Address book updated successfully."
}

deleterecord(){
	echo "Enter the name of Address book:"
	read name
	if [ ! -e "$name" ]; then
		echo "File does not exist!"
		return
	fi
	while true; do
		echo "Enter Last name to delete record or press 'q' to exit:"
		read lname
		if [ "$lname" == 'q' ]; then
			break
		fi
		grep -q "^$lname" "$name"
		if [ $? -eq 0 ]; then
			grep -v "^$lname" "$name" > temp && mv temp "$name"
			echo "Record deleted successfully!"
		else
			echo "Record not found!"
		fi
	done
}

searchrecord(){
	echo "Enter the name of Address book:"
	read name
	if [ ! -e "$name" ]; then
		echo "File does not exist!"
		return
	fi
	while true; do
		echo "Enter last name to search or press 'q' to exit:"
		read lname
		if [ "$lname" == 'q' ]; then
			break
		fi
		grep -i "^$lname" "$name"
		if [ $? -eq 0 ]; then
			echo "Record Found!"
		else
			echo "Record Not Found!!"
		fi
	done
}

# Main menu
while true; do
	echo "1) Create address book"
	echo "2) Insert record"
	echo "3) View records"
	echo "4) Modify record"
	echo "5) Delete record"
	echo "6) Search record"
	echo "7) Exit"
	
	echo "Enter your choice:"
	read ch
	case $ch in
		1) createaddressbook ;;
		2) insertrecord ;;
		3) viewrecords ;;
		4) modifyrecord ;;
		5) deleterecord ;;
		6) searchrecord ;;
		7) exit ;;
		*) echo "Invalid choice! Please enter a number from 1 to 7." ;;
	esac
done
