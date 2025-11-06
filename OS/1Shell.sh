#!/bin/bash   

fileName="addressbook.txt"

while true
do 
echo -e "\n1. Create Address Book"
echo "2. View Records"
echo "3. Insert New Record"
echo "4. Delete a Record"
echo "5. Modify a Record"
echo "6. Exit"
echo

read -p "Enter your choice: " opt 

case $opt in 

1)
    echo "Creating address book..."
    printf "NAME\tNUMBER\tADDRESS\n" > "$fileName"
    printf "===============================================\n" >> "$fileName"

    while true
    do
        read -p "Enter Name: " name
        read -p "Enter Phone Number of $name: " number
        read -p "Enter Address of $name: " address

        printf "%s\t%s\t%s\n" "$name" "$number" "$address" >> "$fileName"

        read -p "Enter 0 to Stop, 1 to Continue: " cont
        [ "$cont" -eq 0 ] && break
        # break
    done
    ;;

2)
    if [ ! -f "$fileName" ]; then
        echo "No address book found!"
    else
        cat "$fileName"
    fi
    ;;

3)
    read -p "Enter Name: " name
    read -p "Enter Phone Number of $name: " number
    read -p "Enter Address of $name: " address
    printf "%s\t%s\t%s\n" "$name" "$number" "$address" >> "$fileName"
    ;;

4)
    if [ ! -f "$fileName" ]; then
        echo "Address book not found!"
    else
        read -p "Enter Name/Phone to Delete: " pattern

        if grep -q "$pattern" "$fileName"; then
            grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"
            echo "Record deleted."
        else
            echo "Record not found!"
        fi
    fi
    ;;

5)
    if [ ! -f "$fileName" ]; then
        echo "Address book not found!"
    else
        read -p "Enter Name/Phone to Modify: " pattern

        if grep -q "$pattern" "$fileName"; then
            grep -v "$pattern" "$fileName" > temp && mv temp "$fileName"

            read -p "Enter New Name: " name
            read -p "Enter New Phone Number: " number
            read -p "Enter New Address: " address

            printf "%s\t%s\t%s\n" "$name" "$number" "$address" >> "$fileName"
            echo "Record modified."
        else
            echo "Record not found!"
        fi
    fi
    ;;

6)
    echo "Exiting program..."
    exit 0
    ;;

*)
    echo "Invalid option!"
    ;;
esac
done
