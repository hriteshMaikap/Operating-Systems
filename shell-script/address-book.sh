#!/bin/bash

create_database() {
    echo -n "Enter the name of your database: "
    read db_filename

    # Check if file already exists
    if [ -f "$db_filename" ]; then
        echo "Database file '$db_filename' already exists!"
    else
        touch "$db_filename"
        echo "Database file '$db_filename' created successfully!"
    fi
}

insert_record() {
    echo -n "Enter the name of the database to insert record: "
    read db_filename

    # Check if the db exists
    if [ ! -f "$db_filename" ]; then
        echo "Database file '$db_filename' does not exist. Create one before!"
        return
    fi

    # Read data
    echo "Enter details of the user:"
    read -p "Name: " name
    read -p "Email: " email
    read -p "Mobile: " mobile
    read -p "Address: " address

    # Formatting the input without extra spaces
    record="${name},${email},${mobile},${address}"

    echo "$record" >> "$db_filename"
    echo "Record inserted successfully!"
}

search_record() {
    echo -n "Enter the name of the database to search record (with extension): "
    read db_filename

    if [ ! -f "$db_filename" ]; then
        echo "Database file '$db_filename' does not exist."
        return
    fi

    echo -n "Enter the name to search in the address book: "
    read search_id

    found=0
    while IFS=, read -r name email mobile address; do
        if [[ "$name" == "$search_id" ]]; then
            echo "Record found! Details are as follows:"
            echo "Name: $name"
            echo "Email: $email"
            echo "Mobile Number: $mobile"
            echo "Address: $address"
            found=1
            break
        fi
    done < "$db_filename"

    if [ $found -eq 0 ]; then
        echo "No record with name: $search_id!!"
    fi
}

modify_record() {
    local db_filename search_id temp_file mod

    echo -n "Enter the name of the database to modify record (with file extension): "
    read db_filename

    if [ ! -f "$db_filename" ]; then
        echo "Database with filename '$db_filename' does not exist"
        return
    fi

    echo -n "Enter the User Name to modify: "
    read search_id
    temp_file=$(mktemp)
    mod=0

    # Read and modify the record
    while IFS=, read -r name email mobile address; do
        name=$(echo "$name" | xargs) # Trim spaces
        email=$(echo "$email" | xargs)
        mobile=$(echo "$mobile" | xargs)
        address=$(echo "$address" | xargs)

        if [[ "$name" == "$search_id" ]]; then
            echo "Record found with following details:"
            echo "Name: $name"
            echo "Email: $email"
            echo "Mobile Number: $mobile"
            echo "Address: $address"

            echo "Enter new modified details (leave unmodified details blank)"
            read -p "Name [$name]: " new_name
            read -p "Email [$email]: " new_email
            read -p "Mobile Number [$mobile]: " new_mobile
            read -p "Address [$address]: " new_address

            new_name=${new_name:-$name}
            new_email=${new_email:-$email}
            new_mobile=${new_mobile:-$mobile}
            new_address=${new_address:-$address}

            echo "$new_name,$new_email,$new_mobile,$new_address" >> "$temp_file"
            mod=1
        else
            echo "$name,$email,$mobile,$address" >> "$temp_file"
        fi
    done < "$db_filename"

    if [ $mod -eq 1 ]; then
        mv "$temp_file" "$db_filename"
        echo "Record updated successfully!"
    else
        rm "$temp_file"
        echo "No matching record with name: $search_id"
    fi
}

show_menu() {
    echo "+------------------+"
    echo "|     Main Menu    |"
    echo "+------------------+"
    echo "|1. Create Database|"
    echo "|2. Insert         |"
    echo "|3. Search         |"
    echo "|4. Modify Records |"
    echo "|5. Exit           |"
    echo "+------------------+"
}

handle_choice() {
    case $1 in
    1) create_database
    ;;

    2) insert_record
    ;;

    3) search_record
    ;;

    4) modify_record
    ;;

    5) echo "Exit"
    exit 0
    ;;

    *) echo "Invalid Choice. Try again!"
    ;;
    esac
}

while true; do
    show_menu
    read -p "Enter your choice: " ch
    handle_choice $ch
    echo ""
done
