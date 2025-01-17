'''
AIM:
Consider telephone book database of N clients. Make use of a hash table implementation to quickly look up client‘s 
telephone number.
Make use of two collision handling techniques and 
Compare them using number of comparisons required to find a set of telephone numbers.

INPUT: The key to be inserted/added in Hash Table.
OUTPUT: The key inserted/added at its location in hash table if empty slot found.

Author: Dr. Sunil Damodar Rathod.
Date: 09.02.2023

'''

class CollusionHandling:
    def __init__(self):
        self.linearHash=[] #Hash Table for Linear Probing Technique
        self.quadraticHash=[] #Hash Table for Quadratic Probing Technique
        self.linearCount=0 #No. of comparisions in Linear Probing
        self.quadraticCount=0  #No. of comparisions in Quadratic Probing
        self.bucketSize=0  #Size of the bucket
    
    #Function to create Empty Hash Table
    def create_bucket(self, bsize):
        self.bucketSize=bsize #Set a size of bucket
        
        #Create Hash Tables of size equall to bucketSize
        self.linearHash=list(None for i in range(self.bucketSize))
        self.quadraticHash=list(None for i in range(self.bucketSize))
    
    #Function to get hash value for given key
    def has_key(self, key):
        return key % self.bucketSize
    
    #function for inserting a record using linear probe without replacement
    def linear_Probing(self,name,phoneNo):
        index=0
        pos=self.has_key(phoneNo)
        print("Pos is:",pos)
        if self.linearHash[pos] == None:
            self.linearHash[pos]={name:phoneNo}
            
        else: #Slot is not empty
            index=(pos+1)%self.bucketSize
            while index != pos:
                #print("Index:",index)
                if self.linearHash[index]==None:
                    self.linearHash[index]={name:phoneNo}
                    return index
                index =  (index+1)%self.bucketSize
        #Table overflow, return invalid index
            return -1
    
    #Function to search a phone number using linear probe
    def search_key_Linear_prob(self,phoneNo):
        index=0
        self.linearCount=0
        pos=self.has_key(phoneNo)
        recFound=False
        phone=0
        
        if self.linearHash[pos] != None:
            self.linearCount += 1
            for phone in self.linearHash[pos].values():
                if phone==phoneNo:
                    print("Phone number is in Table at position ",pos)
                    recFound=True
                else:
                    
                    #Search the complete table for a given key
                    index=(pos+1)%self.bucketSize
                    while index != pos:
                        self.linearCount += 1 
                        if self.linearHash[index] != None: 
                            for phone in self.linearHash[index].values():
                            #print("\nCurrent Search of number::",phone)
                                if phone==phoneNo:
                                    print("Phone number is in Table at position ",index)
                                    recFound=True
                            #break
                        index =  (index+1)%self.bucketSize
        
        #Table search exausted
        if not recFound:
            print("Phone number not found!!")
        
        print("Number of records searched in table to find a key is :",self.linearCount)
    
    #Function to display Hash Table contents
    def display_Linear_Hash_Table(self):
        name=None
        for i in range(self.bucketSize):
            if self.linearHash[i]==None:
                print (i," ",None)
            else:
                print(i, self.linearHash[i])
    
    ###############QUADRATIC PROBING################
    #function for inserting a record using Quadratic probing without replacement
    def quadratic_Probing(self,name,phoneNo):
        index=0
        pos=self.has_key(phoneNo)
        print("Pos is:",pos)
        if self.quadraticHash[pos] == None:
            self.quadraticHash[pos]={name:phoneNo}
            
        else: #Slot is not empty
            i=1
            index=pos+i*i
            while index != pos:
                print("Index:",index)
                if self.quadraticHash[index]==None:
                    self.quadraticHash[index]={name:phoneNo}
                    return index
                i+=1
                index =  (pos+i*i)%self.bucketSize
        #Table overflow, return invalid index
            return -1
    
    #Function to search a phone number using quadratic probe
    def search_key_quadratic_prob(self,phoneNo):
        index=0
        self.quadraticCount=0
        pos=self.has_key(phoneNo)
        recFound=False
        phone=0
        
        if self.quadraticHash[pos] != None:
            self.quadraticCount +=1
            for phone in self.quadraticHash[pos].values():
                if phone==phoneNo:
                    print("Phone number is in Table at position ",pos)
                    recFound=True
                else:
                    i=1
                    index=(pos+i*i)%self.bucketSize
                    while index != pos:
                        self.quadraticCount += 1 
                        if self.quadraticHash[index] != None:
                            
                            for phone in self.quadraticHash[index].values():
                                if phone==phoneNo:
                                    print("Phone number is in Table at position ",index)
                                    recFound=True
                        i+=1
                        index =  (pos+i*i)%self.bucketSize
        
        #Table search exausted
        if not recFound:
            print("Phone number not found!!")
        
        print("Number of records searched in table to find a key is :",self.quadraticCount)
    
    #Function to display Hash Table contents
    def display_quadratic_Hash_Table(self):
        name=None
        for i in range(self.bucketSize):
            if self.quadraticHash[i]==None:
                print (i," ",None)
            else:
                print(i, self.quadraticHash[i])
     

#Driver Code
c1=CollusionHandling()

bsize=int(input("Enter the Size of hash table:"))
c1.create_bucket(bsize)

choice1=0
while (choice1 !=3):
    print("\n*******Collusion Handling Techniques*******")
    print("\n1. Linear Probing")
    print("\n2. Quadratic Probing")
    print("\n3. Exit Application")
    choice1=int(input("Enter Your Choice:"))
    if choice1==1:
        
        choice2=0
        while choice2 !=4:
            print("\n*******Linear Probing Techniques*******")
            print("\n1. Add Record in Table")
            print("\n2. Display Table Contents")
            print("\n3. Search Telephone in Table")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            
            if choice2 ==1:
                name=input("Enter the name of a person:")
                phoneNo = int(input("Enter phone number:"))
                result=c1.linear_Probing(name,phoneNo)
                
                if result == -1:
                    print("\nTable is Full!")
            
            elif choice2 == 2:
                c1.display_Linear_Hash_Table()
            
            elif choice2==3:
                phoneNo=int(input("Enter the phone number to be searched::"))
                c1.search_key_Linear_prob(phoneNo)
                
            elif choice2 == 4:
                break
    elif choice1 ==2:
        choice2=0
        while choice2 !=4:
            print("\n*******Quadratic Probing Techniques*******")
            print("\n1. Add Record in Table")
            print("\n2. Display Table Contents")
            print("\n3. Search Telephone in Table")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            if choice2 ==1:
                name=input("Enter the name of a person:")
                phoneNo = int(input("Enter phone number:"))
                result=c1.quadratic_Probing(name,phoneNo)
                
                if result == -1:
                    print("\nTable is Full!")
            
            elif choice2 == 2:
                c1.display_quadratic_Hash_Table()
            
            elif choice2==3:
                phoneNo=int(input("Enter the phone number to be searched::"))
                c1.search_key_quadratic_prob(phoneNo)
                
            elif choice2 == 4:
                break
    elif choice1 ==3:
        break

