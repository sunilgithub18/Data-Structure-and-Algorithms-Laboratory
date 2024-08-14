/*
 AIM:
 There are flight paths between cities.
 If there is a flight between city A and city B then there is an edge between the cities.
 The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey.
 Represent this as a graph.
 The node can be represented by airport name or name of the city.
 i. Use adjacency Matrix/list representation of the graph.
 ii. Check whether the graph is connected or not. Justify the storage representation used. 
 
INPUT: Nodes of graph as cities of India
OUTPUT: Adjacency Matrix/List, True if graph is connected otherwise False

Author: Dr. Sunil Damodar Rathod.
Date: 05.05.2023
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

class Graph
{
	int G[10][10];
	NODE Header[10];
	const char city[5][20]={"Pune","Mumbai","Delhi","Jaipur","Chakan"};
	int visited[10];
	int mNodes; //No. of nodes in Adjacency Matrix Graph
	int lNodes; //No. of nodes in Adjacency List Graph
	public:
	Graph()
	{
		//Initialization of Adjacency Matrix
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
			
		//Initialization of List Header
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
			visited[i]=0;
		}
		mNodes=0;
		lNodes=0;
	}
	
	//Initialization of Adjacency Matrix
	void init_Matrix()
	{
		mNodes=5;//set this value equal to number of cities
		for (int i=0;i<10;i++)
			for(int j=0;j<10;j++)
				G[i][j]=0;
	}
	
	//Initialization of List Header
	void init_List()
	{
		for (int i=0;i<10;i++)
		{
			Header[i].data=i+1;
			Header[i].next=NULL;
			visited[i]=0;
		}
	}
	
	//Initialization of visited array
	void init_visited()
	{
		for (int i=0;i<10;i++)
			visited[i]=0;
	}
	
	//Read graph as adjacency matrix
	void readGAM()
	{
		int i,j;
		int flag=1;
		init_Matrix();
		mNodes=5;//set this value equal to number of cities
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
	
	//Print graph as adjacency matrix
	void printGAM()
	{
		int i,j,k=0;
		cout<<"\n\t";
		for (i=0;i<mNodes;i++)
			cout<<city[i]<<"\t";
		cout<<"\n";
		for (i=1;i<=mNodes;i++)
		{
			cout<<city[i-1]<<"\t";
			for(j=1;j<=mNodes;j++)
				cout<<G[i][j]<<"\t";
			
			cout<<"\n";
		}
	}

	//Function for DFS traversal
	void DFS_RECURSIVE(int i)
	{
		int j;
		cout<<" "<<i;
		visited[i]=1;
		for(j=1;j<=mNodes;j++)
			if(!visited[j] && G[i][j]==1)
				DFS_RECURSIVE(j);
	}
	
	//Function to see whether graph is connected or not
	bool isConnected()
	{
		int i;
		init_visited();
		
		//Make a DFS traversal on complete graph starting from vertax '1'
		DFS_RECURSIVE(1);
		
		//if any of the nodes in graph is not connected then it will remain unvisited
		for(i=1;i<=mNodes;i++)
			if(visited[i]==0)//if a node is unvisited then graph is not connected
				return false;
		
		return true;//if all nodes are visted then graph is connected
	}
};


/** Main Contains menu **/
int main()
{
    Graph g1;
	int n;
	int cho=0;
	while(cho != 4)
	{
     cout<<"\n********CONNECTED GRAPH*********";
     cout<<"\n1-Read Graph Adjacency Matrix";
     cout<<"\n2-Print Graph Adjacency Matrix";
	 cout<<"\n3-Check Graph Connected or Not Connected";
     cout<<"\n4-EXIT";
     cout<<"\nEnter ur choice:";
     cin>>cho;
     switch(cho)
     {
       case 1:
		g1.readGAM();
		break;
       case 2:
		g1.printGAM();
		break;
	   case 3:
		if (g1.isConnected())
			cout<<"\nGraph is connected!";
		else
			cout<<"\nGraph is not connected!";
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