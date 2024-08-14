/*
AIM:
Beginning with an empty binary search tree,
Construct binary search tree by inserting the values in the order given. 
After constructing a binary tree -
i. Insert new node 
ii. Find number of nodes in longest path from root
iii.Minimum data value found in the tree
iv. Change a tree so that the roles of the left and right pointers are swapped at every node
v. Search a value 

INPUT: The set of values
OUTPUT: Various operations result.

Author: Dr. Sunil Damodar Rathod.
Date: 17.02.2023

*/

#include<iostream>
#pragma warn -inl

using namespace std;
typedef struct node
{
   struct node *LC;
   int data;
   struct node *RC;
}NODE;

class BST
{
	NODE *root;//root node address
	int count;//no. of comparisions
	int lh,rh;//left height and right height
	public:
	//Constructor to initialize the attributes of class
	BST()
	{
		root=NULL;
		count=0;
		lh=rh=0;
	}
	
	//Function to return root address
	NODE* getroot()
	{
		return root;
	}

	
	//i. Insert new node
	void addNode(int v)
	{
		NODE *p,*q,*cur;
		p=new NODE;
		p->data=v;
		p->LC=p->RC=NULL;
		if(root==NULL)// If root is NULL then add the value as root node of tree
			root=p;
		else //Otherwise traverse the tree to add node at proper place
		{
			cur=root;//Current pointer to search a proper node 

			while(cur)//traverse till proper node found
			{
				q=cur;//'q' follows 'cur' pointer
				if(cur->data == v)//data of current node and the 'v' are same
				{ 
					cout<<"\nDuplicate Node!";
					return ;
				}
				if(v<cur->data)//if new value 'v' is smaller than current node data
					cur=cur->LC;// traverse to the left to get correct node
				else
					cur=cur->RC;//else traverse tp the right
			}
			//the proper node is pointed by pointer 'q' where insertion is possible
			if(v<q->data)//if v is smaller than data of 'q'
				q->LC=p;//insert new node as left child of 'q'
			else
				q->RC=p;//insert new node as right child of 'q'
		}
		return;
	}
	
	//INORDER Traversal of tree
	void displayIN(NODE *T)
	{
		if(T)
		{
			displayIN(T->LC);
			cout<<" "<<T->data;
			displayIN(T->RC);
		}
	}
	
	//ii. Find number of nodes in longest path from root
	int height(NODE *T)
	{

		if(T==NULL)
			return 0;
		if(T->LC ==NULL && T->RC==NULL)//if leaf node then retrun height '0'
			return 0;
		lh=height(T->LC);//travel left recursively
		rh=height(T->RC);//travel right recursively
		if(lh>rh)//For every node see left height is greater than right 
			return lh+1;//return left height 
		else
			return rh+1;//return left height
	}
	
	//iii.Minimum data value found in the tree
	void minimumDataValue(NODE *T)
	{
		NODE *q,*t;
		int top=-1;
		t=T;
		if (t==NULL)
			cout<<"\nTree Empty";
		else
		{
			while(t)//Traversal of tree to left till last node
			{
				q=t;//'q' follows 't'
				t=t->LC;//Goto left
			}
			cout<<"Minimum data value found is:: "<<q->data;
		}
	}
	
	//iv.Change a tree so that the roles of the left and right pointers are swapped at every node
	void Mirror(NODE *t)
	{
		//This algorithm prints the mirror image of the BST.
		//The pointer ‘t’ points to the ‘root’ node of a BST.
		//The algorithm is recursive and terminates when t reaches to NULL link of leaf node.
		NODE *q;// temporary pointer for exchanging the address of left child and right child link
		if(t) // call recursively till pointer ‘t’ points to NULL
		{
			q=t->LC; // hold the address of left child
			t->LC=t->RC; // replace left child address with right child address
			t->RC=q; // replace right child address with left child address
			Mirror(t->LC); // call recursive for left subtree of the BST
			Mirror(t->RC); // call recursive for right subtree of the BST
		}
	}
	
	//v. Search a value, Logic is same as insert node in BST
	
	void searchNode(int v)
	{
		NODE *q,*cur;
		count=0;//initialize count to zero for every new search
		if(root==NULL)
			cout<<"\nTree Empty!!";
		else
		{
			cur=root;
			while(cur)
			{
				count++;
				
				if(cur->data == v)
				{
					cout<<"\nNode Found after "<<count<<" comparisions";;
					return ;
				}
				if(v<cur->data)
					cur=cur->LC;
				else
					cur=cur->RC;
			}
		}
		cout<<"\nNode with "<<v<<" value not found after "<<count<<" comparisions";
		return;
	}
	
};


int main(void)
{
   BST B;
   int val,cho,n;
   cho=0;
   while(cho != 7)
   {
     
     cout<<"\n1-ADD NODE";
     cout<<"\n2-DISPLAY NODE INORDER";
	 cout<<"\n3-NO. OF NODES IN THE LONGEST PATH FROM ROOT";
	 cout<<"\n4-MINIMUM DATA VALUE IN THE TREE";
	 cout<<"\n5-MIRROR IMAGE";
     cout<<"\n6-SEARCH NODE IN NODE";
     cout<<"\n7-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
     switch(cho)
     {
       case 1:
		cout<<"\nEnte any value to added in tree:";
		cin>>val;
		B.addNode(val);
		break;
       case 2:
		B.displayIN(B.getroot());
		break;
       case 3:
		n=B.height(B.getroot());
		cout<<"\nNo. of nodes in the longest path are:"<<n+1;
		break;
       case 4:
		B.minimumDataValue(B.getroot());
		break;
       case 5:
		cout<<"\nThe mirror image of tree"<<endl;
		B.Mirror(B.getroot());
		break;
	   case 6:
	    cout<<"\nEnte any value to be searched in tree:";
		cin>>val;
		B.searchNode(val);
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