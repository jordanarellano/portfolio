from cs50 import SQL
from sys import argv, exit

# Checks command line arguments
if len(argv) != 2:
    print("Please specify a hogwarts house")
    exit(1)
    
# Assigns house input
house = argv[1]

# Open SQL abilities
db = SQL("sqlite:///students.db")

# Query from database, based on house input
query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

# Prints data extracted from database
for row in query:
    
    # Ignores Middle name if NULL
    if row["middle"] == None:
        print(row["first"], " ", row["last"], ", born ", row["birth"], sep ="")
        
    # Prints data as specified, inserting spaces manually for formatting
    else:
        print (row["first"], " ", row["middle"], " ", row["last"], ", born ", row["birth"], sep = "")