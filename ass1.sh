#!/bin/bash

#Initialize variables
name=""
city=""
code=""
mobno=""
fname=""
n=0
ch=0

# Display menu until user chooses 7
while [ "$ch" -ne 7 ]
do
   echo -e "\n\tAddress Database"
   echo -e "\t------------------"
   echo "1. Create Database"
   echo "2. View Database"
   echo "3. Insert a record"
   echo "4. Delete a record"
   echo "5. Search a record"
   echo "6. Modify a record"
   echo "7. Exit"

   echo "Enter your Choice: "
   read -r ch

   case $ch in 

   1)
      # Create Database
      echo  "Enter the filename : "
      read -r fname
      touch "$fname"
      echo "Enter the number of records: "
      read n
      i=$n
      while [ $i -gt 0 ]
      do
         echo "Enter name:"
         read name
         echo "Enter city:"
         read city
         echo "Enter zipcode:"
         read code
         echo "Enter Mobile no: "
         read mobno
         echo "$name $city $code $mobno" >> $fname
         echo "Your data is stored in the file"
         i=$((i -1))
      done
      ;; 
    2)
        echo -e "\nName\tCity\tZipcode\tMobile_Number"
        cat $fname
        ;;

    3)
        echo "Enter name:"
        read name
        echo "Enter City:"
        read city
        echo "Enter Zipcode:"
        read code
        echo "Enter Mobile no.:"
        read mobno
        echo "$name $city $code $mobno" >> $fname
        ;;

    4)
        echo "Enter the name of the record to be deleted:"
        read name
        grep -v "$name" $fname > temp
        mv temp $fname
        ;;

    5)
        echo "Enter the name of the record to be searched:"
        read name
        grep "$name" $fname
        ;;

    6)
        echo "Enter the name of the record to be modified:"
        read name
        grep -v "$name" $fname > temp
        echo "Enter new name:"
        read name
        echo "Enter new City:"
        read city
        echo "Enter new Zipcode:"
        read code
        echo "Enter new Mobile no.:"
        read mobno
        echo "$name $city $code $mobno" >> temp
        mv temp $fname
        ;;

    7)
        echo "Exiting the program. Goodbye!"
        ;;

    *)
        echo "Invalid choice. Please enter a number between 1 and 7."
        ;;
    esac
done   


        

