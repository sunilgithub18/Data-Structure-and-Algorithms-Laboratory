/*
AIM:
A Dictionary stores keywords & its meanings.
Use Binary Search Tree for implementation.
Provide facility to:
i. Insert new Keyword
ii.Delete keyword
iii.Update keyword or meaning
iv.Display whole data sorted in ascending/ Descending order.
v. Search keyword & find how many maximum comparisons may require for finding any keyword. 

INPUT: Keyword - meaning
OUTPUT: BST with keywords as the data

Author: Dr. Sunil Damodar Rathod.
Date: 22.04.2023
*/

#include<iostream>
#include<cstring>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits


using namespace std;
typedef struct keyword{
	char key[20];
	char meaning[100];
}WORD;
typedef struct node
{
   struct node *LC;
   WORD data;
   struct node *RC;
}NODE;

class Stack
{
	private:
		int top;
		NODE *data[30];
	public:
	Stack()
    {
		top=-1;
    }
	int isEmpty()
    {
		if(top == -1)
			return 1;
		else
			return 0;
    }
	void push(NODE* p)
    {
		data[++top]=p;
    }
   
	NODE* pop()
    {
		return(data[top--]);
    }
};
 
class BST
{
	NODE *root;
	int count;
	public:
	BST()
	{
		root=NULL;
		count=0;
	}
	NODE* getroot()
	{
		return root;
	}
	
	//INORDER Traversal of tree
	void displayIN(NODE *T)
	{
		if(T)
		{
			displayIN(T->LC);
			cout<<T->data.key<<":"<<T->data.meaning<<endl;
			displayIN(T->RC);
		}
	}
	
	void displayDesending(NODE* root)
	{
		WORD words[100];
		Stack s;
		NODE *p;
		p=root;
		int i=0,n=0;
		while(p!=NULL)
		{
			s.push(p);
			p=p->LC;
		}
		while(!s.isEmpty())
		{
			p=s.pop();
			strcpy(words[n].key,p->data.key);
			strcpy(words[n].meaning,p->data.meaning);
			n++;
			p=p->RC;
			while(p!=NULL)
			{
				s.push(p);
				p=p->LC;
			}
		}
		cout<<"\n";
		for(i=n-1;i>=0;i--)
			cout<<words[i].key<<":"<<words[i].meaning<<endl;
	}
	
	//i. Insert new node
	void addNode(WORD w)
	{
		NODE *p,*q,*cur;
		p=new NODE;
		p->data=w;
		p->LC=p->RC=NULL;
		if(root==NULL)
			root=p;
		else
		{
			cur=root;

			while(cur)
			{
				q=cur;
				if(strcmp(cur->data.key,w.key)==0)
				{
					cout<<"\nDuplicate Node!";
					return ;
				}
				if(strcmp(cur->data.key,w.key)>0)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
			if(strcmp(q->data.key,w.key)>0)
				q->LC=p;
			else
				q->RC=p;
			
		}
		return;
	}
	
	//ii. Delete Node
	void deleteNode(char key[])
	{
		NODE *parent,*cur,*p,*q,*t;
		bool found=false;
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;

			while(cur)
			{
				//if key found then see its position before you delete
				if(strcmp(cur->data.key,key) == 0)
				{
					cout<<cur->data.key<<" : "<<cur->data.meaning<<" will be deleted!";
					found=true;
					//Node to be deleted (cur) is root node
					if(cur == root)
					{
						cout<<"\nNode "<<cur->data.key<<" is root node!";
						//Root is only node having no child
						if(cur->LC ==NULL && cur->RC == NULL)
						{
							root=NULL;
							delete cur;
						}
						else
						//Root left subtree but no right child
						if(cur->LC !=NULL && cur->RC == NULL)
						{
							root=root->LC;//left child of root becomes root itself
							delete cur;
						}
						else
						//Root has right subtree then find it's inorder successor
						if(cur->RC != NULL)
						{
							if((cur->RC)->LC == NULL)//right child of cur itself is inorder successor
							{
								p=cur->RC;//set pointer 'p' to right child of cur
								cur->data=p->data;//copy right child data to cur
								cur->RC=p->RC;//set right child of 'p' as right child of cur
								delete p;
							}
							else//Find the inorder successor of cur
							{
								p=t=cur->RC;
								while(t)
								{
								q=p;//pointer 'q' follows 'p'
								p=t;//pointer 'p' follows 't'
								t=t->LC;
								}
								cur->data=p->data;
								q->LC=NULL;
								delete p;
							}
						}
					}
					else
					//Node to be deleted (cur) does not have any child-it's leaf node 
					if(cur->LC == NULL && cur->RC == NULL)
					{
						cout<<"\nLeaf Node of "<<parent->data.key;
						if(strcmp((parent->LC)->data.key,key)==0)//the leaf node is left child of it's parent
						{
							cout<<"\nLeft Child!!";
							parent->LC=NULL;
						}
						else	//the leaf node is right child of it's parent
						{
							cout<<"\nRight Child!!";
							parent->RC=NULL;
						}
						delete cur;
					}
					else
					//cur is left child of parent but not leaf node
					if(strcmp((parent->LC)->data.key,key)==0)
					{
						cout<<"\nLeft child Node of "<<parent->data.key;
						if(cur->LC != NULL && cur->RC == NULL)//Node to be deleted has left subtree but no right subtree
							parent->LC=cur->LC;//left child of cur becomes left child of parent
						else if(cur->LC == NULL && cur->RC != NULL)//Node to be deleted has right subtree but no left subtree
							parent->LC=cur->RC;//right child of cur becomes left child of parent
						
						delete cur;
					}
					else
					//cur is right child  of parent but not leaf node
					if(strcmp((parent->RC)->data.key,key)==0)//cur Node is right child of parent
					{
						cout<<"\nRight child Node of "<<parent->data.key;
						if(cur->LC != NULL && cur->RC == NULL)//Node to be deleted has left subtree but no right subtree
							parent->RC=cur->LC;//left child of cur becomes right child of parent
						else if(cur->LC == NULL && cur->RC != NULL)//cur Node to be deleted has right subtree but no left subtree
							parent->RC=cur->RC;//right child of cur becomes right child of parent
						
						delete cur;
					}
					else
					//Node to be deleted (cur) is either left of right child of parents  
					if(cur->LC != NULL && cur->RC != NULL)//But has both left and right subtree
					{
						cout<<"\nNode "<<cur->data.key<<" has both left & right child!";
						//Find inorder successor or cur and replace cur with its value
						if((cur->RC)->LC ==NULL)//right child of cur itself is inorder successor
						{
							p=cur->RC;//set pointer 'p' to right child of cur
							cur->data=p->data;//copy right child data to cur
							cur->RC=p->RC;//set right child of 'p' as right child of cur
							delete p;
						}
						else//Find the inorder successor of cur
						{
							p=t=cur->RC;
							while(t)
							{
								q=p;//pointer 'q' follows 'p'
								p=t;//pointer 'p' follows 't'
								t=t->LC;
							}
							cur->data=p->data;
							q->LC=NULL;
							delete p;
						}
					}
					
					return;
				}
				if(strcmp(cur->data.key,key)>0)
				{
					parent=cur;//Remember Parent
					cur=cur->LC;//Traverse to left
				}
				else
				{
					parent=cur;//Remember Parent
					cur=cur->RC;;//Traverse to right
				}
			}
			cout<<"\nNode with "<<key<<" not found!!";
		}
		
	}

	//iii. Update a keyword or meaning 
	void updateNode(char key[])
	{
		NODE *q,*cur;
		char meaning[100];
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;

			while(cur)
			{
				q=cur;
				if(strcmp(cur->data.key,key) == 0)
				{
					cout<<cur->data.key<<" : "<<cur->data.meaning;
					cout<<"\nEnter new meaning of "<<cur->data.key<<" ::";
					cin.clear();//to clear the std in stream
					fflush(stdin);// to flush the input buffer
					cin.getline(meaning,100);//getline function to read multiword string
					strcpy(cur->data.meaning,meaning);
					cout<<"Dictionary word updated!!";
					return ;
				}
				if(strcmp(cur->data.key,key)>0)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
		}
		cout<<"\nNode with "<<key<<" not found!!";
		return;
	}	
	
	//iv. Search a value 
	void searchNode(char key[])
	{
		NODE *q,*cur;
		
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;
			count=0;
			while(cur)
			{
				count++;
				q=cur;
				if(strcmp(cur->data.key,key) == 0)
				{
					cout<<cur->data.key<<" : "<<cur->data.meaning;
					cout<<"\nFound after "<<count<<" no. of comparisons";
					return ;
				}
				if(strcmp(cur->data.key,key)>0)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
		}
		cout<<"\nNode with word "<<key<<" not found "<<" after "<<count<<" comparisons";
		return;
	}
};


int main(void)
{
   BST B;
   int val,cho,n,cho1;
   WORD w;
   char key[30];
   cho=0;
   while(cho != 7)
   {
     cout<<"\n********DICTIONARY STORAGE*********";
     cout<<"\n1-ADD WORD";
     cout<<"\n2-DISPLAY WORD";
	 cout<<"\n3-DELETE WORD FROM DICTIONARY";
	 cout<<"\n4-UPDATE WORD OF DICTIONARY";
	 cout<<"\n5-DISPLAY DICTIONARY WORDS ASCENDING OR DECENDING ORDER";
	 cout<<"\n6-SEARCH WORD IN DICTIONARY";
     cout<<"\n7-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
	 cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer before taking new
     switch(cho)
     {
       case 1:
		cout<<"\nEnter keyword:";
		cin.clear();//to clear the std in stream
		fflush(stdin);// to flush the input buffer
		cin.getline(w.key,20);//getline function to read multiword string
		cout<<"\nEnter meaning of the word:";
		cin.clear();
		fflush(stdin);
		cin.getline(w.meaning,100);
		B.addNode(w);
		break;
       case 2:
		B.displayIN(B.getroot());
		break;
       
	   case 3:
		cout<<"\nEnter keyword to be deleted:";
		cin.clear();//to clear the std in stream
		fflush(stdin);// to flush the input buffer
		cin.getline(key,30);//getline function to read multiword string
		B.deleteNode(key);
		break;
	   case 4:
		cout<<"\nEnter keyword to be Updated:";
		cin.clear();//to clear the std in stream
		fflush(stdin);// to flush the input buffer
		cin.getline(key,30);//getline function to read multiword string
		B.updateNode(key);
		break;
	   case 5:
		cout<<"\n1. Ascending Order";
		cout<<"\n2. Descending Order";
		cout<<"\nEnter your choice::";
		cin>>cho1;
		if (cho1==1)
			B.displayIN(B.getroot());
		else
			B.displayDesending(B.getroot());
		break;
	   case 6:
		cout<<"\nEnter keyword to be searched:";
		cin.clear();//to clear the std in stream
		fflush(stdin);// to flush the input buffer
		cin.getline(key,30);//getline function to read multiword string
		B.searchNode(key);
		break;
	   case 7:
		cout<<"\nProgram Exits!!";
		break;
       default:
		cout<<"\nWrong choice!";
     }
    
   }
   
   return 0;
}
