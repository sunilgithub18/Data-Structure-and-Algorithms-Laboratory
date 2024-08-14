/* 
AIM: 
Company maintains employee information as employee ID, name, designation and salary.
Allow user to add, delete information of employee.
Display information of particular employee.
If employee does not exist an appropriate message is displayed.
If it is, then the system displays the employee details.
Use index sequential file to maintain the data.

INPUT: Information of EMPLOYEE
OUTPUT: List of EMPLOYEE details

Author: Dr. Sunil Damodar Rathod.
Date: 27.05.2023
*/

#include<iostream>
#include<fstream>
#include<cstring>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

using namespace std;

//Employee Structure
typedef struct EMPLOYEE
{
	int emp_id;//Employee ID
	char name[20];//Employee name
	char designation[20];//Employee designation
	int salary;//Employee Salary
}Rec;

//Index File
typedef struct INDEX
{
	int emp_id;//Primary key is Employee ID
	int position;// Index position of Employee record in the actual data file
}Ind_Rec;

class Employee
{
	private:
		Rec Records;
		Ind_Rec Ind_Records;
	public:
		Employee();
		void Create();
		void Display();
		void Update();
		void Delete();
		void Append();
		void Search();
};
//All functions are defined outside the class
Employee::Employee()//constructor 
{
	Records.emp_id=-1;
	strcpy(Records.name,"");
	strcpy(	Records.designation,"");
	Records.salary=0;
}

//Function to create files
void Employee::Create()
{
	int i,j;
	char ch='y';
	fstream seqfile;
	fstream indexfile;
	i=0;
	//Index file which has emp_id and it's index in file
	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
	
	//Actual Employee records are stored in sequential EMP.txt file
	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
	do
	{
		cout<<"\n Enter Emp_ID: ";
		cin>>Records.emp_id;
		cout<<"\n Enter Name: ";
		cin>>Records.name;
		cout<<"\n Enter Designation: ";
		cin>>Records.designation;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
		cout<<"\n Enter Salary: ";
		cin>>Records.salary;
		seqfile.write((char*)&Records,sizeof(Records))<<flush;
		Ind_Records.emp_id=Records.emp_id;
		Ind_Records.position=i;
		indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
		i++;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
		cout<<"\nDo you want to add more records?";
		cin>>ch;
	}while(ch=='y');
	
	//close all the files
	seqfile.close();
	indexfile.close();
}

void Employee::Display()
{
	fstream seqfile;
	fstream indexfile;
	int n,i,j;
	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
	indexfile.seekg(0,ios::beg);
	seqfile.seekg(0,ios::beg);
	cout<<"\n The Contents of file are ..."<<endl;
	i=0;
	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
	{
		i=Ind_Records.position*sizeof(Rec);//getting pos from index file
		seqfile.seekg(i,ios::beg);//seeking record of that pos from seq.file

		seqfile.read((char *)&Records,sizeof(Records));//reading record

		if(Records.emp_id!=-1)//if rec. is not deleted logically
		{   				//then display it
			cout<<"\nEmp_ID: "<<Records.emp_id;
			cout<<"\nName: "<<Records.name<<flush;
			cout<<"\nDesination: "<<Records.designation;
			cout<<"\nSalary: "<<Records.salary;
			cout<<"\n";
		}
	}
	seqfile.close();
	indexfile.close();
}

//Function to update the Employee record
void Employee::Update()
{
	int pos,id;
	int New_emp_id;
	char New_name[10];
	char New_desig[20];
	int New_salary;
	cout<<"\n For updation,";
	cout<<"\n Enter the Emp_ID for for searching ";
	cin>>id;
	fstream seqfile;
	fstream indexfile;
	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
	//Set read pointer to the first offset(Address in file)
	indexfile.seekg(0,ios::beg);

	pos=-1;//initilize position
	//reading index file for getting the index
	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
	{
		if(id==Ind_Records.emp_id)//the desired record is found
		{
			pos=Ind_Records.position;//get the position to locate the employee in actual data file
			break;
		}
	}
	
	//If position is invalid then record is not present
	if(pos==-1)
	{
		cout<<"\n The record is not present in the file";
		return;
	}
	else
	{
		cout<<"\n Enter the values for updation...";
		cout<<"\n Name: ";cin>>New_name;
		cout<<"\n Designation: ";cin>>New_desig;
		cout<<"\n Salary: ";cin>>New_salary;
		
		//calculating the position of record in seq. file using the pos of ind. file
		int offset=pos*sizeof(Rec);
		//set the write pointer to the desired offset 
		seqfile.seekp(offset);//seeking the desired record for modification
		Records.emp_id=id;//It's unique key,so can't be changed
		strcpy(Records.name,New_name);//can be updated
		strcpy(Records.designation,New_desig);//can be updated
		Records.salary=New_salary;//can be updated
		seqfile.write((char*)&Records,sizeof(Records))<<flush;
		cout<<"\n The record is updated!!!";
	}
	seqfile.close();
	indexfile.close();
}

//Function to delete the Employee record
void Employee::Delete()
{
	int id,pos;
	cout<<"\n For deletion,";
	cout<<"\n Enter the Emp_ID for for searching ";
	cin>>id;
	fstream seqfile;
	fstream indexfile;
	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
	seqfile.seekg(0,ios::beg);
	indexfile.seekg(0,ios::beg);
	pos=-1;
	//reading index file for getting the index
	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
	{
		if(id==Ind_Records.emp_id) //desired record is found
		{
			pos=Ind_Records.position;
			Ind_Records.emp_id=-1;
			break;
		}
	}
	if(pos==-1)
	{
		cout<<"\n The record is not present in the file";
		return;
	}

	//calculating the position of record in seq. file using the pos of ind. file
	int offset=pos*sizeof(Rec);
	seqfile.seekp(offset);//seeking the desired record for deletion
	strcpy(Records.name,"");//Logical deletion
	strcpy(Records.designation,"");//Logical deletion
	Records.emp_id=-1; //logical deletion
	Records.salary=-1; //logical deletion
	seqfile.write((char*)&Records,sizeof(Records))<<flush;//writing deleted status 
    //From index file also the desired record gets deleted as follows

	offset=pos*sizeof(Ind_Rec);//getting position in index file
	indexfile.seekp(offset); //seeking that record
	Ind_Records.emp_id=-1; //logical deletion of emp_id
	Ind_Records.position=pos;//position remain unchanged
	indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
	seqfile.seekg(0);
	indexfile.close();
	seqfile.close();
	cout<<"\n The record is Deleted!!!";
}

//Function to append the Employee record
void Employee::Append()
{
	fstream seqfile;
	fstream indexfile;
	int pos;
	indexfile.open("IND.txt",ios::in|ios::binary);
	indexfile.seekg(0,ios::end);
	pos=indexfile.tellg()/sizeof(Ind_Records);
	indexfile.close();

	indexfile.open("IND.txt",ios::app|ios::binary);
	seqfile.open("EMP.txt",ios::app|ios::binary);

	cout<<"\n Enter the record for appending";
	cout<<"\nEmp_ID: ";cin>>Records.emp_id;
	cout<<"\nName: ";cin>>Records.name;
	cout<<"\nDesination: ";cin>>Records.designation;
	cout<<"\nSalary: ";cin>>Records.salary;
	seqfile.write((char*)&Records,sizeof(Records));//inserting rec at end in seq. file
	Ind_Records.emp_id=Records.emp_id; //inserting rec at end in ind. file
	Ind_Records.position=pos;      	//at calculated pos
	indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
	seqfile.close();
	indexfile.close();
	cout<<"\n The record is Appended!!!";
}

void Employee::Search()
{
	fstream seqfile;
	fstream indexfile;
	int id,pos,offset;
	cout<<"\n Enter the Emp_ID for searching the record ";
	cin>>id;
	indexfile.open("IND.txt",ios::in|ios::binary);
	pos=-1;
	//reading index file to obtain the index of desired record
	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
	{
		if(id==Ind_Records.emp_id)//desired record found
		{
			pos=Ind_Records.position;//seeking the position
			break;
		}
	}
	if(pos==-1)
	{
		cout<<"\n Record is not present in the file";
		return;
	}
	//calculate offset using position obtained from ind. file
	offset=pos*sizeof(Records);
	seqfile.open("EMP.txt",ios::in|ios::binary);
	//seeking the record from seq. file using calculated offset
	seqfile.seekg(offset,ios::beg);//seeking for reading purpose
	seqfile.read((char *)&Records,sizeof(Records));
	if(Records.emp_id==-1)
	{
		cout<<"\n Record is not present in the file";
		return;
	}
	else //emp_id=desired record’s id
	{
		cout<<"\n The Record is present in the file and it is...";
		cout<<"\n Emp_ID: "<<Records.emp_id;
		cout<<"\n Name: "<<Records.name;
		cout<<"\n Designation: "<<Records.designation;
		cout<<"\n Salary: "<<Records.salary;
	}
	seqfile.close();
	indexfile.close();
}

int main()
{
	Employee List;
	char ans='y';
	int choice,key;
	fstream out;
	out.open("EMP.txt",ios::out);
	out.close();
	
	out.open("IND.txt",ios::out);
	out.close();
	choice=0;
	while(choice !=7)
	{
		cout<<"\n***************Index Sequential File**************"<<endl;
		cout<<"\n 1.Create File";
		cout<<"\n 2.Display All Employee Records";
		cout<<"\n 3.Update an Employee Information";
		cout<<"\n 4.Delete a Record";
		cout<<"\n 5.Append a Record";
		cout<<"\n 6.Search an Employee";
		cout<<"\n 7.Exit";
		cout<<"\n Enter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				List.Create();
				break;
			case 2:
				List.Display();
				break;
			case 3:
				List.Update();
				break;
			case 4:
				List.Delete();
				break;
			case 5:
				List.Append();
				break;
			case 6:
				List.Search();
				break;
			case 7:
				break;
			default:
				cout<<"Wrong Choice!!";
		}
	}
	
	return 0;
}

