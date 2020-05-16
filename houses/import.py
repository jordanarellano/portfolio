from cs50 import SQL
from sys import argv, exit
import csv

#Command line arguments
if len(argv) != 2:
    print ("Missing CSV File")
    exit(1)
    
#Create Database
open("students.db", "w").close()
db = SQL("sqlite:///students.db")

#Create Table
db.execute("CREATE TABLE students(first TEXT, middle TEXT, last TEXT, house TEXT,birth NUMERIC)")

#Open CSV file
with open(argv[1], "r") as students:
    
    #Create Dict Reader
    reader = csv.DictReader(students)
    
    #Iterate over csv file
    for row in reader:
        
        #Splits name into 3 strings, inserts NULL value if no middle name
        name = row["name"].split(" ")
        if len(name) == 2:
            name.insert(1, None)
        
        db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?,?,?,?,?)", name[0] , name[1], name[2], row["house"], row["birth"])
        
        