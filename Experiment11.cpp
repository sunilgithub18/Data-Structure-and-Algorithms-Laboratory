/* 
AIM: 
Department maintains a Student information.
The file contains roll number, name, division and address.
Allow user to add, delete information of Student.
Display information of particular Student.
If record of Student does not exist an appropriate message is displayed.
If it is, then the system displays the Student details.
Use sequential file to main the data.

INPUT: Information of Student
OUTPUT: List of Students details

Author: Dr. Sunil Damodar Rathod.
Date: 27.05.2023
*/

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<iomanip>

using namespace std;

class Student
{
	private:
		string name,div,address;
		int roll;
	public:
		void getdata();
		void displayAll();
		void insert_record();
		void delete_record();
		void search_record();
};

//Function to read student details
void Student::getdata()
{
 cout<<"\nEnter Roll No, Division, Name and Address of Student= ";
 cin>>roll>>div>>name>>address;
 
} 

//Function to insert student details in a sequential file
void Student::insert_record()
{
	fstream out;
	Student *s1;
	s1=new Student;
	out.open("StudRecord.txt",ios::app|ios::binary);
	
	s1->getdata();
	out.write((char *)&s1,sizeof(s1));
	
	out.close();
}

//Function to display student details in a sequential file
void Student::displayAll()
{
	fstream out;
	Student *s2;
	s2=new Student;
	out.open("StudRecord.txt",ios::in|ios::binary);
	
	cout<<"\nThe Contents of file are.......\n\n";
	cout<<"\nROLL"<<setw(15)<<"Division"<<setw(15)<<"NAME"<<setw(15)<<"MARKS\n";
	
	while(out.read((char*)&s2,sizeof(s2)))
	{
		cout<<"\n"<<s2->roll<<setw(15)<<s2->div<<setw(15)<<s2->name<<setw(15)<<s2->address;
	}
	cout<<"\n";
	out.close();
}

//Function to delete student details from a sequential file
void Student::delete_record()
{
	fstream out,temp;
	Student *s2;
	int item;
	s2=new Student;
	out.open("StudRecord.txt",ios::in|ios::binary);
	temp.open("temp.txt",ios::out|ios::binary);
	cout<<"\nEnter Roll_No :";
	cin>>item;
	//Copy all the records from StudRecord.txt to temp.txt except one to be deleted
	while(out.read((char*)&s2,sizeof(s2)))
	{
		    if(s2->roll!=item)
			{
				temp.write((char *)&s2,sizeof(s2));
			}
			
	}
	//Close the opened files
	out.close();
	temp.close();
	
	//remove StudRecord which is old now
	remove("StudRecord.txt");
	//rename temp.txt to StudRecord,txt
	rename("temp.txt","StudRecord.txt");
	
}

//Function to search student details in a sequential file
void Student::search_record()
{
	int item;
	Student *s2;
	fstream out;
	out.open("StudRecord.txt",ios::in|ios::binary);
	s2=new Student;
	cout<<"\nEnter Roll_No :";
	cin>>item;
	
	while(out.read((char*)&s2,sizeof(s2)))
	{
			if(s2->roll==item)
			{
				cout<<"\n Record is Present in the File....\n ";
				cout<<"\n"<<s2->roll<<"\t"<<s2->div<<"\t"<<s2->name<<"\t"<<s2->address;
				break;
			}
	}
	out.close();
}

int main()
{
	Student t1;
	int ch=0;
	fstream out;
	out.open("StudRecord.txt",ios::out);
	out.close();
	
	while(ch!=5)
	{
		cout<<"\n*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** \n\n";
		cout<<"\n1.INSERT RECORD\n2.DISPLAY All Records \n3.SEARCH\n4.Delete\n5.EXIT.";
		cout<<"\nEnter UR Choice : ";
		cin >> ch;
		switch(ch)
		{
		case 1:
 			t1.insert_record();
			cout<<"\n\nRecord is Inserted..\n\n";
			break;
		case 2:
			t1.displayAll();
			break;
		case 3:
			t1.search_record();
			break;
		case 4:
			t1.delete_record();
			break;
		case 5:
			exit(0);
		}
	}
	return 0;
}
  
/************************* OUTPUT *******************************
$ g++ .cpp
$ ./a.out

*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 1

Enter Roll No, Division, Name and Address of Student= 63 SE-A Ashwini Satara


Record is Inserted..


*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 1

Enter Roll No, Division, Name and Address of Student= 51 SE-A Swapnil Pune


Record is Inserted..


*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 1

Enter Roll No, Division, Name and Address of Student= 70 SE-A Pandey UP


Record is Inserted..


*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 1

Enter Roll No, Division, Name and Address of Student= 05 SE-A Sayali Daund


Record is Inserted..


*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 1

Enter Roll No, Division, Name and Address of Student= 03 SE-A Shiva Pune


Record is Inserted..


*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 2

The Contents of file are.......


ROLL       Division           NAME         MARKS

63           SE-A        Ashwini         Satara
51           SE-A        Swapnil           Pune
70           SE-A         Pandey             UP
5           SE-A         Sayali          Daund
3           SE-A          Shiva           Pune

*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 3

Enter Roll_No :5

 Record is Present in the File....
 
5	SE-A	Sayali	Daund
*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 4

Enter Roll_No :70

*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 2

The Contents of file are.......


ROLL       Division           NAME         MARKS

63           SE-A        Ashwini         Satara
51           SE-A        Swapnil           Pune
5           SE-A         Sayali          Daund
3           SE-A          Shiva           Pune

*******  SEQUENTIAL ACCESS FILE PROGRAM USING C++ ********** 


1.INSERT RECORD
2.DISPLAY All Records 
3.SEARCH
4.Delete
5.EXIT.
Enter UR Choice : 5
$ 
*/
    

