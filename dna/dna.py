from sys import argv, exit
import csv


def main():

    #check command-line arguments
    if len(argv) != 3:
        print("missing command-line argument(s)")
        exit(1)

    #read csv into a nested list
    str_list = []
    with open(argv[1]) as csvfile:
        strs = csv.reader(csvfile)
        for row in strs:
            str_list.append(row)

    #create a string with just the strs
    strs = []
    for x in range(1, len(str_list[0])):
        strs.append(str_list[0][x])
            
    #read text into memory
    with open(argv[2]) as f:
        dna = f.read()
    
    #initialize list/dict
    count_list = []
    str_count = {}
   
   #loops through each STR
    for i in range(len(strs)):
        count = 0
        length = len(strs[i])
        internal_count = []
        
        #loops through each position in the dna sequence
        for j in range(len(dna)):
            
            #checks if str appears in string of size length of str at each position j
            if strs[i] in dna[(len(dna)-1-j):(len(dna)-1-j+length)]:
                count=0
                
                #counts the continuous occurences of the STRs at each position j
                for k in range(j):
                    if strs[i] in dna[(len(dna)-1-j+k*length):(len(dna)-1-j+(k+1)*length)]:
                        count += 1
                        internal_count.append(count)
                        
                    else:
                        break
                    
        #adds only the highest continuos count to the list         
        highest_count = max(internal_count)               
        str_count.update( { strs[i] : highest_count } )
        count_list.append(highest_count)
    
        
    #Iterate through csv list to check for dna match
    for l in range(1, len(str_list)):
        check_list =[]
        
        for m in range(1, len(str_list[0])):
            
            check_list.append(int(str_list[l][m]))
            
       
        if check_list == count_list:
            print(str_list[l][0])
            exit(0)
            
    print("No match")


main()  