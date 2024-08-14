/*AIM:
C++ Program to Construct an Expression Tree for a Given Prefix Expression
Provide facility to:
i. Read Prefix Expression
ii.Build Tree from Prefix Expression
iii.Print Tree using non recurrsive postOrder traversal

INPUT: Prefix expression
OUTPUT: Binary Tress as Expression Tree

Author: Dr. Sunil Damodar Rathod.
Date: 17.04.2023
*/

#include<iostream>
#include<cstring>
#include<stack>
using namespace std;

//Tree structure Node
struct node
{
	struct node* left;
	char data;
	struct node* right;
};

//Class for Stack used in non recursive Post Order traversal
class Stack
 {
	private:
		struct node* S[30];
		int top;
	public:
		Stack()
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
		void push(struct node* val)
	    {
			S[++top]=val;
	    }
		
		//Function to remove item from stack
		struct node* pop()
	    {
			return(S[top--]);
	    }
 };


//Class for Creation of Tree from prefix expression
class ExpTree
{   
	private:
		char Exp[30];//Input Prefix Expression 
		struct node* root;//Root node addressress
		Stack s;
	public:
		ExpTree()
		{
			root=NULL;
		}
		
		//Function to initialize top of stack & root node address
		void initialize()
		{
			root=NULL;
		}
		
		//Function to Read expression
		void readExpression() 
		{
			cout<<"Enter the Prefix Expression"<<endl;
			cin>>Exp;
		}
		
		//Function to print expression
		void printExpression()
		{
			cout<<"The expression is ::"<<Exp<<endl;
		}
		
		//Function to check whether the token is operand
		bool isOperand(char t)
		{	
			//if a token is alphabet or digit then its operand
			if((t>='a' && t<='z')||(t>='A' && t<='Z') ||(t>=0 && t<=9))
				return true;
			else
				return false;	
		}
		
		//Function to check whether the token is operator
		bool isOperator(char t)
		{
			//if a token is any of +, -, x, / or % then it is operator
			if(t=='*' || t=='+' || t=='-' || t=='/' || t=='%')
				return true;
			else
				return false;
		}

		//Function to add Node in binary tree
		void addNode(char token)
		{	 
			struct node *p;
			p= new struct node;
			p->left=NULL;
			p->data=token;
			p->right=NULL;

			if(isOperand (token))//if a token is operand, push it on to the stack
				{  	 
					s.push(p);//push operand on to the stack
					root=p;//update root address
				}
			else if(isOperator (token))//if it is operator then pop two topmost operand from stack
				{
					p->left=s.pop();;//Pop first stack item, make it left child of the operator
					p->right=s.pop();//Pop Second stack item, make it right child of the operator
					s.push(p);;//Push the partial tree on the stack
					root=p;//update root address
				}
			else
				cout<<"INVALID EXPRESSION"<<endl;
		}
		
		//Function to build tree from given infix expression
		void buildTree()
		{
			initialize();
			//for each token of the expression call add node to build tree
			for(int i=strlen(Exp)-1;i>=0;i--){         
				addNode(Exp[i]);
			}	
		}
		
		//Recurssive Inorder for printing the genereted tree
		void inorder(struct node* t)
		{
			if(t)
			{
				inorder(t->left);
				cout<<t->data;
				inorder(t->right);
			}
		}
		
		//Function to return root address
		struct node* getRoot()
		{ 
			return root;
		}

		void nonRecursivePost(struct node* root)
		{
			if (root == NULL)
				return;

			//Local stacks - stack1 and stack2
			Stack stack1, stack2;

			// Push root to first stack
			stack1.push(root);
			struct node* node;

			// Repeat untill first stack is not empty
			while (!stack1.empty()) {
				// pop node from stack1 and push to stack2
				node = stack1.pop();//pop or remove that node from stack1
				stack2.push(node);//save it in stack2

				// push left and right node of current node popped from stack1 
				if (node->left)
					stack1.push(node->left);
				if (node->right)
					stack1.push(node->right);
			}

			// if stack2 is not empty print the nodes
			while (!stack2.empty()) {
				node = stack2.pop();
				cout << node->data << " ";
			}	
		}
};

int main(){
  	ExpTree e1;
  	int choice=0;
  	
  	while(choice!=6)
  	{	
  		cout<<"\n*************Expression Tree***************";
  		cout<<"\n1. Read Expression";
  		cout<<"\n2. Print Expression";
  		cout<<"\n3. Build Tree ";
  		cout<<"\n4. Print Tree Inorder";
		cout<<"\n5. Print Tree Non Recurssive Postorder";
  		cout<<"\n6. Exit Application";
  		cout<<"\nEnter your choice::";
		cin>>choice;
  		switch (choice){
  			case 1:
				e1.readExpression();
  			 	break;
  			case 2:
  			 	e1.printExpression();
  			 	break;
  			case 3:
  			 	e1.buildTree();
  			 	break;
  			case 4:
  			 	e1.inorder(e1.getRoot());
  			 	break;
			case 5:
  			 	e1.nonRecursivePost(e1.getRoot());
  			 	break;
  			case 6:
  			 	break;
  			default :
  			    cout<<"\nWrong choice!!";
  		}
  	}
}