/*
AIM:
 Represent a given graph using adjacency matrix/list.
 i. Perform DFS on adjacency matrix/list  
 ii. Use adjacency list to perform BFS.
 Use the map of the area around the college as the graph.
 Identify the prominent land marks as nodes and perform DFS and BFS on that. 

INPUT: Nodes of graph as Landmarks of college campus
OUTPUT: DFS on Adjacency Matrix and BFS on Adjacency List

Author: Dr. Sunil Damodar Rathod.
Date: 17.04.2023
*/
#include <iostream>
#include <cstdlib>
#include <cstdio>     
#include <cstring>
using namespace std;
typedef struct Node
{
	int data;
	struct Node *next;
}NODE;

//Class for Stack used in non recursive DFS traversal
class stack
 {
		int data[30];
		int top;
	public:
		stack()
	    {
	      top=-1;
	    }
		//Function to check whether Stack is empty or not
		int empty()
	    {
			if(top==-1)
				return 1;
			
			return 0;
	    }

		//Function to add item in stack
		void push(int x)
	    {
			data[++top]=x;
	    }
		
		//Function to remove item from stack
		int pop()
	    {
			return(data[top--]);
	    }
 };

//Class to implement Queue for BFS traversal
class Queue
{
	private:
		int r,f;
		int data[30];
	public:

		Queue()
		{
			r=f=-1;
		}
	
		//Function to initialise the front and rear pointer of Queue
		void init()
		{
			r=f=-1;
		}

		//Function to check whether Queue is empty or not
		int empty()
		{
			if(r==-1)
				return 1;
    
			return 0;
		}
 
		//Function to add item in Queue
		void insert(int x)
		{
			if(r==-1)
			{
				r=f=0;
				data[r]=x;
			}
			else
			{
				r=r+1;
				data[r]=x;
			}
		}
		
		//Function to remove item from Queue
		int delet()
		{
			int x=data[f];
			if(r==f)
				f=r=-1;
			else	
				f=f+1;

			return(x);
		}

};

//Class for implementaion of Graph traversal, DFS/BFS
class Graph
{
	int G[10][10]; //Graph as Adjacency Matrix
	NODE Header[10];//Graph Header for Adjacency List
	int visited[10];//Visited Array
	int mNodes; //No. of nodes in Adjacency Matrix Graph
	int lNodes; //No. of nodes in Adjacency List Graph
	const char landmark[5][30]={"Comp","Admin","Library","Canteen","Garden"};
	public:
	Graph()
	{
		//initialization of Graph Adjacency Matrix
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
			
		//Initialization of List Header
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
		}
		
		//initialization of visited array to zero
		for (int i=0;i<10;i++)
			visited[i]=0;
		
		mNodes=0;
		lNodes=0;
	}
	
	//Function for initialization of Graph Adjacency Matrix
	void initAM()
	{
		
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
	}
	
	//Function for Initialization of List Header
	void initAL()
	{
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
		}	
		lNodes=0;
	}
	
	void initVisited()
	{
		//initialization of visited array to zero
		for (int i=0;i<10;i++)
			visited[i]=0;
	}
	
	void printHeader()
	{
		for (int i=0;i<10;i++)
		{
			cout<<"\n["<<landmark[Header[i].data-1]<<"|"<<Header[i].next<<"]->NULL";
		}	
	}
	
	//Function for reading graph as Adjacency Matrix
	void readGAM()
	{
		int i,j;
		int flag=1;
		mNodes=5;//Value is set equall to landmark locations
		while(flag==1)
		{
			cout<<"\nEnter source node:";
			cin>>i;
			cout<<"\nEnter destination node:";
			cin>>j;
			G[i][j]=1;
			cout<<"\nDo you want to add more edge yes=1 or no=0:";
			cin>>flag;
		}
	}
	
	//Function for printing graph as Adjacency Matrix
	//Print graph as adjacency matrix
	void printGAM()
	{
		int i,j,k=0;
		cout<<"\n\t";
		for (i=0;i<mNodes;i++)
			cout<<landmark[i]<<"\t";
		cout<<"\n";
		for (i=1;i<=mNodes;i++)
		{
			cout<<landmark[i-1]<<"\t";
			for(j=1;j<=mNodes;j++)
				cout<<G[i][j]<<"\t";
			
			cout<<"\n";
		}
	}
	
	//Function for adding linked list node in graph as Adjacency List
	void addNode(int pos,int val)
	{
		NODE *p,*cur;
		p=new NODE;
		p->data=val;
		p->next=NULL;
		if (Header[pos].next ==NULL)
			Header[pos].next=p;
		else
		{
			cur=Header[pos].next;
			while(cur->next !=NULL)
				cur=cur->next;
			
			cur->next=p;			
		}
	}
	
	//Function for reading graph as Adjacency List
	void readGAL(int n)
	{
		int i,j;
		int nan,val;
		lNodes=n;
		for (i=0;i<n;i++)
		{
			cout<<"\nHow many no. of adjacent nodes to node "<<Header[i].data<<" :";
			cin>>nan;
			if(nan !=0)
				for (j=1;j<=nan;j++)
				{
					cout<<"\nEnter value of "<<j<<" node::";
					cin>>val;
					addNode(i,val);// add the adjacent nodes to the current header
				}
		}
		cout<<"\nNo. of Nodes in List::"<<lNodes;
	}
	
	//Function for reading graph as Adjacency List
	void printGAL()
	{
		int i,j;
		int nan,val;
		NODE *cur;
		for (i=0;i<lNodes;i++)
		{
			cur=Header[i].next;
			cout<<"\n["<<landmark[Header[i].data-1]<<"|"<<Header[i].next<<"]->";
			while(cur !=NULL)
			{
				cout<<"["<<landmark[cur->data-1]<<"|"<<cur->next<<"]->";
				cur=cur->next;
			}				
			cout<<"NULL";
		}
	}
	
	//Function for Recursive DFS Traversal
	void DFS_RECURSIVE(int i)
	{
		int j;
		cout<<" "<<landmark[i-1];
		visited[i]=1; //Mark the starting node visited 
		for(j=1;j<=mNodes;j++)//Check which nodes are adjacent to current node 'i'
			if(!visited[j] && G[i][j]==1) // if 'j' is adjacent node to 'i;
				DFS_RECURSIVE(j);//Call recursively DFS on adjacent node 'j'
	}
	
	//Function for Non-Recursive DFS Traversal
	void DFS_NON_RECURSIVE(int v)
	{
		stack s;
		int i;
		//initialization of visited array to zero
		for (int i=0;i<10;i++)
			visited[i]=0;
		
		s.push(v);// Push starting node on stack
		while(!s.empty()) //Till stack is not empty do
		{
			v=s.pop(); //Pop the top node on stack 
			if(!visited[v])// if Node is not visited
			{
				visited[v]=1;//Mark it visited 
				cout<<"  "<<landmark[v-1];
				for(i=1;i<=mNodes;i++)// Check which nodes are adjacent to current node 'v'
					{
						if(visited[i]==0 && G[v][i]!=0)// if 'i' is adjacent node to 'v; and is not visited  
							s.push(i);//Push it on to the stack and traver in DFS fashion
					}
			}
		}
	}

	//Function for BFS Traversal on Adjacency Matrix
	void BFS_Matrix(int v)
	{
		Queue q;
		int i,j;
		
		//initialization of visited array to zero
		for (int i=0;i<10;i++)
			visited[i]=0;
		
		q.insert(v); //Add starting node in Queue
		cout<<"  "<<landmark[v-1];
		while(!q.empty()) //Till Queue is not empty do
		{
			v=q.delet(); //delete front node from queue
			for(i=1;i<=mNodes;i++) // Check which nodes are adjacent to current node 'v'
				if(visited[i]==0 && G[v][i]!=0) // if 'i' is adjacent node to 'v; and is not visited  
				{
					q.insert(i); // Add the adjacent node in Queue
					visited[i]=1; //Mark node visited
					cout<<"  "<<landmark[i-1];
				}
		}
	}
	
	//Function for BFS Traversal on Adjacency List
	void BFS_List(int v)
	{
		Queue q;
		int i,j;
		NODE *cur;
		
		//initialization of visited array to zero
		for (int i=0;i<10;i++)
			visited[i]=0;
		q.init();
		q.insert(v); //Add starting node in Queue
		visited[v]=1;
		while(!q.empty()) //Till Queue is not empty do
		{
			v=q.delet(); //delete front node from queue
			
			cout<<landmark[v-1]<<"  ";
			cur=Header[v-1].next;//Traverse to all adjacent nodes of the current node
			while(cur!=NULL)
			{
				if(visited[cur->data]==0) // if the adjacent node is not visited  
				{
					q.insert(cur->data); // Add the adjacent node in Queue
					visited[cur->data]=1; //Mark node visited
				}
				cur=cur->next;
			}
			cout<<"\n";
		}
	}
	
};

/** Main with Menu **/
int main()
{
    Graph g1;
	int n,val;
	int cho=0;
	
	while(cho != 8)
	{
		cout<<"\n********GRAPH TRAVERSAL*********";
		cout<<"\n1-Read Graph Adjacency Matrix";
		cout<<"\n2-Print Graph Adjacency Matrix";
		cout<<"\n3-Read Graph Adjacency List";
		cout<<"\n4-Print Graph Adjacency List";
		cout<<"\n5-Recursive DFS on Adjacency Matrix";
		cout<<"\n6-Non Recursive DFS on Adjacency Matrix";
		cout<<"\n7-BFS on Adjacency List";
		cout<<"\n8-EXIT";
		cout<<"\nEnter ur choice:";
		cin>>cho;
		switch(cho)
		{
			case 1:
				g1.initAM();
				g1.readGAM();
				break;
			case 2:
				g1.printGAM();
				break;
			case 3:
				g1.initAL();
				g1.printHeader();
				cout<<"\nHow many nodes in graph:";
				cin>>n;
				g1.readGAL(n);
				break;
			case 4:
				g1.printHeader();
				cout<<"\nAdjecancy List\n";
				g1.printGAL();
				break;
			case 5:
				cout<<"\nEnter the starting node::";
				cin>>val;
				g1.initVisited();
				g1.DFS_RECURSIVE(val);
				break;
			
			case 6:
				cout<<"\nEnter the starting node::";
				cin>>val;
				g1.DFS_NON_RECURSIVE(val);
				break;
			case 7:
				cout<<"\nEnter the starting node::";
				cin>>val;
				g1.BFS_List(val);
				break;
			case 8:
				cout<<"\nProgram Exits!!";
				break;
			default:
				cout<<"\nWrong choice!";
		}
	}
	
    return 0;
}