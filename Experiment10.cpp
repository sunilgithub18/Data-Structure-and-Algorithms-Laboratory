/*
AIM:
Consider a scenario for Hospital to cater services 
to different kinds of patients as 
a)Serious (top priority)
b) non-serious (medium priority)
c) General Checkup (Least priority).
Implement the priority queue to cater services to the patients

INPUT: Patient with the severity of desease 
OUTPUT: A priority queue 

Author: Dr. Sunil Damodar Rathod.
Date: 26.05.2023
*/

#include<iostream>
#include<cstring>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

using namespace std;
typedef struct patient{
	int patientID;//ID
	int severity;// 2-Top, 1-Medium,0-Least
}PATIENT;

class priorityQ
{
	private:
		int nop;//Number Of Patient
		PATIENT P[50]; //Patient details
		const char priority[3][10]={"Least","Medium","Top"};
	public:
	//Constructor to initialize the data members
	priorityQ()
    {
		for (int i=0;i<50;i++)
		{
			P[i].patientID=0;
			P[i].severity=0;
		}
		nop=0;
    }
	
	//Display Patient Queue
	void displayQueue()
	{
		for (int i=1;i<=nop;i++)
			cout<<"\n"<<P[i].patientID<<"  "<<priority[P[i].severity];
	}
	
	//Add new patient in priority queue
	void addPatient(PATIENT p)
	{
		int i;
		PATIENT t;
		i=nop;//no. of patients in the queue
		if(i==0)// Heap P does not have any element     
		{
			//then store new record into P as first element of heap P
			P[++i]=p;
			nop=i;// copy the current count to nop
		}
		else// if there are more elements in heap then insert the element at last and Up-Adjust it with its parent
		{
			P[++i]=p;
			nop=i;// copy the current count 'i' to nop
			while(i>1 && P[i].severity > P[i/2].severity) // till the new inserted element is larger than its parent
			{
				t=P[i]; //copy P to t
				P[i]=P[i/2];// shift child to its parent location
				P[i/2]=t;// copy parent to position of child
				i=i/2;// update i to new parent location
			}
		}
	}
	
	void deletePatient()
	{		
		PATIENT t;
		int i,j;
		//delete the first queue item by exhanging it with last element
		t=P[1];
		P[1]= P[nop];
		P[nop]=t;
		nop--;//new count will not be one less than the previous
		i=1;
		
		//Do now the down adjustment
		while(2*i<=nop)   //current parent 'i' is not a leaf node
		{
			j=2*i;           // find the left child of i
			if(j+1<=nop && P[j+1].severity>P[j].severity)//j points larger of Left & Right child of current parent
				j++;

			if(P[i].severity<P[j].severity)//check heap property
			{
				t=P[i];
				P[i]=P[j];
				P[j]=t;
				i=j;//set i to new parent 
			}
			else
				break;
		}
	}
};


int main(void)
{
   priorityQ B;
   int cho,n,cho1;
   PATIENT p;
   char key[30];
   cho=0;
   while(cho != 4)
   {
     cout<<"\n************PATIENT QUEUE*************";
     cout<<"\n1-ADD PATIENT TO QUEUE";
     cout<<"\n2-DISPLAY QUEUE";
	 cout<<"\n3-DELETE PATIENT FROM QUEUE";
     cout<<"\n4-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
	 cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
     switch(cho)
     {
       case 1:
		cout<<"\nEnter patient ID:";
		cin>>p.patientID;//getline function to read multiword string
		cout<<"\nEnter severity\n\t2. Top \n\t1. Medium \n\t0. Least\n\t::";
		cin>>n;
		p.severity=n;	
		B.addPatient(p);
		break;
       case 2:
		B.displayQueue();
		break;
	   case 3:
		B.deletePatient();
		break;
	   case 4:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
    
   }
   
   return 0;
}
/*

D:\ICEM\AY-2022-23\SE\DSAL_Lab>a

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:1

Enter patient ID:1

Enter severity
        2. Top
        1. Medium
        0. Least
        ::0

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:1

Enter patient ID:2

Enter severity
        2. Top
        1. Medium
        0. Least
        ::1

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

2  Medium
1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:1

Enter patient ID:3

Enter severity
        2. Top
        1. Medium
        0. Least
        ::0

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

2  Medium
1  Least
3  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:1

Enter patient ID:4

Enter severity
        2. Top
        1. Medium
        0. Least
        ::2

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

4  Top
2  Medium
3  Least
1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:3

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

2  Medium
1  Least
3  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:3

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

3  Least
1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:1

Enter patient ID:5

Enter severity
        2. Top
        1. Medium
        0. Least
        ::2

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

5  Top
1  Least
3  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:1

Enter patient ID:6

Enter severity
        2. Top
        1. Medium
        0. Least
        ::1

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

5  Top
6  Medium
3  Least
1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:3

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

6  Medium
1  Least
3  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:3

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

3  Least
1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:3

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

1  Least
************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:3

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:2

************PATIENT QUEUE*************
1-ADD PATIENT TO QUEUE
2-DISPLAY QUEUE
3-DELETE PATIENT FROM QUEUE
4-EXIT
Enter ur choice:
*/