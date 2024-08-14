'''
AIM:
To create ADT that implement the "set" concept. 
a. Add (new Element) -Place a value into the set 
b. Remove (element) Remove the value 
c. Contains (element) Return true if element is in collection 
d. Size () Return number of values in collection 
Iterator () Return an iterator used to loop over collection 
e. Intersection of two sets 
f. Union of two sets 
g. Difference between two sets 
h. Subset


INPUT: Two Sets with interger values
OUTPUT: Various operations result.

Author: Dr. Sunil Damodar Rathod.
Date: 16.02.2023

'''

class SetOperations:
    def __init__(self):
        self.setA=[] #First Set A
        self.setB=[] #Second Set B
        self.setC=[] #Result Set C
        self.setSize=0 #Size of Set
        self.iterator=0  #iterator for Set
    
    #Function to add element in a Set A
    def add_element_setA(self, element):
        self.setA.append(element)
    
    #Function to add element in a Set B
    def add_element_setB(self, element):
        self.setB.append(element)
    
    #Function to remove element from Set A
    def remove_element_setA(self, element):
        if element in self.setA:
            self.setA.remove(element)
    
    #Function to remove element from Set B
    def remove_element_setB(self, element):
        if element in self.setB:
            self.setB.remove(element)
    
    #Function to seach an element in Set A
    def containts_setA(self, element):
        found=False
        for val in self.setA:
            if val == element:
                print(element," found")
                found=True
                break
        
        if not found:
            print(element,"  not found in set")
    
    #Function to seach an element in Set B
    def containts_setB(self, element):
        found=False
        for val in self.setB:
            if val == element:
                print(element," found")
                found=True
                break
        
        if not found:
            print(element,"  not found in set")
    
    #Function to fing size of Set A
    def size_setA(self):
        return len(self.setA)
    
    #Function to fing size of Set B
    def size_setB(self):
        return len(self.setB)
    
    #Display the contents of SetA
    def display_setA(self):
        print("{",end=" ")
        for val in self.setA:
            print(val,end=",")
        print("}")
    
    #Display the contents of SetA
    def display_setB(self):
        print("{",end=" ")
        for val in self.setB:
            print(val,end=",")
        print("}")

    #Find the intersection of two Sets
    def set_intersection(self):
        self.setC.clear()
        print("\nIntersection of two sets is:")
        for val in self.setA:
            if val in self.setB:
                self.setC.append(val)
        
        print("{",end=" ")
        for val in self.setC:
            print(val,end=",")
        print("}")
    
    #Find the Union of two Sets
    def set_union(self):
        self.setC.clear()
        print("\nUnion of two sets is:")
        for val in self.setA:
            self.setC.append(val)
        
        for val in self.setB:
            if val not in self.setA:
                self.setC.append(val)
        
        print("{",end=" ")
        for val in self.setC:
            print(val,end=",")
        print("}")
    
    #Find the set difference A-B
    def set_difference(self):
        self.setC.clear()
        print("\nThe set difference A-B:")
        
        for val in self.setA:
            if val not in self.setB:
                self.setC.append(val)
        
        print("{",end=" ")
        for val in self.setC:
            print(val,end=",")
        print("}")
    

#Driver Code
c1=SetOperations()

choice1=0
while (choice1 !=9):
    print("\n*******SET OPERATIONS*******")
    print("\n1. Add New Element in a Set")
    print("\n2. Remove Element from a Set")
    print("\n3. Check a Set Contains an element")
    print("\n4. Check the Size of a Set ")
    print("\n5. Display Set Elements ")
    print("\n6. Set Intersection")
    print("\n7. Set Union")
    print("\n8. Set Difference")
    print("\n9. Exit Application")
    choice1=int(input("Enter Your Choice:"))
    if choice1==1:
        
        choice2=0
        while choice2 !=4:
            print("\n****************************")
            print("\n1. Add an Element to Set A")
            print("\n2. Add an Element to Set B")
            print("\n3. Display Set Elements")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            
            if choice2 ==1:
                num= int(input("Enter any number:"))
                c1.add_element_setA(num)
                c1.display_setA()
            
            elif choice2 == 2:
                num= int(input("Enter any number:"))
                c1.add_element_setB(num)
                c1.display_setB()
            
            elif choice2==3:
                c1.display_setA()
                c1.display_setB()
                
            elif choice2 == 4:
                break
                
    elif choice1 ==2:
        choice2=0
        while choice2 !=4:
            print("\n****************************")
            print("\n1. Remove an Element to Set A")
            print("\n2. Remove an Element to Set B")
            print("\n3. Display Set Elements")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            
            if choice2 ==1:
                num= int(input("Enter an element to be removed:"))
                c1.remove_element_setA(num)
                c1.display_setA()
            
            elif choice2 == 2:
                num= int(input("Enter an element to be removed:"))
                c1.remove_element_setB(num)
                c1.display_setB()
            
            elif choice2==3:
                c1.display_setA()
                c1.display_setB()
                
            elif choice2 == 4:
                break
    elif choice1 ==3:
        choice2=0
        while choice2 !=4:
            print("\n****************************")
            print("\n1. Check an Element in Set A")
            print("\n2. Check an Element in Set B")
            print("\n3. Display Set Elements")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            
            if choice2 ==1:
                num= int(input("Enter an element to be found:"))
                c1.containts_setA(num)
            
            elif choice2 == 2:
                num= int(input("Enter an element to be found:"))
                c1.containts_setB(num)
            
            elif choice2==3:
                c1.display_setA()
                c1.display_setB()
                
            elif choice2 == 4:
                break
    
    elif choice1 ==4:
        choice2=0
        while choice2 !=4:
            print("\n****************************")
            print("\n1. Check size of Set A")
            print("\n2. Check size of  Set B")
            print("\n3. Display Set Elements")
            print("\n4. Back to Main")
            choice2=int(input("Enter Your Choice:"))
            
            if choice2 ==1:
                print("The Set A has ",c1.size_setA(), " elements")

            elif choice2 == 2:
                print("The Set A has ",c1.size_setB(), " elements")
            
            elif choice2==3:
                c1.display_setA()
                c1.display_setB()
                
            elif choice2 == 4:
                break
    elif choice1 ==5:
        c1.display_setA()
        c1.display_setB()
        
    elif choice1 ==6:
        c1.display_setA()
        c1.display_setB()
        c1.set_intersection()
        
    elif choice1 ==7:
        c1.display_setA()
        c1.display_setB()
        c1.set_union()
        
    elif choice1 ==8:
        c1.display_setA()
        c1.display_setB()
        c1.set_difference()
        
    elif choice1 ==9:
        break