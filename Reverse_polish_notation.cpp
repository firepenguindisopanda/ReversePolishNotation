
#include<iostream>
#include<cstdlib>
#include <stdio.h>
#include <ctime>
#include<fstream>

using namespace std;

struct Node
{
	char data;
	Node *next;
};

Node* createnode(char);
Node* insertathead(Node *,char);
Node* insertattail(Node*,char);
Node* deleteathead(Node*);
Node*getLast (Node * top);
void print(Node *);

struct stack
{
	Node *top;
};

stack * initStack();
bool isvalid(Node *top);
bool isEmpty(stack *s);
void push(stack *s,char);
char pop(stack *s);

Node * RPN(stack*s,Node*top);
bool isNumber(char);
bool isOperator(char);
int pres(char);
char peek(stack *s);
float evaluate(Node *top);

struct stackdigit//new addition
{
	float element[100];
	int top;
};
stackdigit*initstackd();
bool diisEmptyst(stackdigit *d);
float peek2(stackdigit *d);
void push2(stackdigit *d,float n);
float pop2(stackdigit *n);
bool isFULL(stackdigit *d);
//end of new addition

int main()
{
	Node * top,*top2;
	top=NULL;
	char ch;

	float ans;
	ifstream input1;
	ofstream output1;
	stack *s;
	s=initStack();
	
	input1.open("input.txt");
	output1.open("output.txt");
	
	if(input1.is_open()==false)
	{
		cout<<"Error reading file";
	}
	else
	{	
		input1>>noskipws;
		input1>> ch;
		while(ch != '$')
		{

			top=insertattail(top,ch);
			
			if(ch=='\n')
			{

				
				if(isvalid(top)==true)
				{

					cout<<"Infix: ";
					print(top);
					cout<<"PostFix: ";
					top2=RPN(s,top);
					ans=evaluate(top2);
					cout<<"Answer: "<<ans;
					cout<<endl;
					
					output1<<"Infix: ";
					while(top != NULL)
					{
						output1<<top->data;
						
						top=top->next;
					}
					output1<<"PostFix: ";
					while(top2 != NULL)
					{
						output1<<top2->data;
						top2=top2->next;
					}
					output1<<endl;
					output1<<"Answer: ";
					output1<<ans;
					output1<<endl;
					output1<<endl;
				}
				else
				{
					cout<<"Invalid: ";
					print(top);
					
					output1<<"Invalid: ";
					while(top!=NULL)
					{
						output1<<top->data;
						top=top->next;
					}
					output1<<endl;
					cout<<endl;
				}
				
				top=NULL;
				cout<<endl;
			}
			input1>>ch;
		}
	}

	return 0;
}

//Returns the answer evaluated from the valid expressions
//Parameters:
//Node * top -> The top of the linked list that contains the expression to be evaluated
float evaluate(Node*top)//test
{
	Node*Curr;
	Curr=top;
	
	stackdigit *d;
	d= initstackd();
	
	float ans,ti1,ti2,temp;
	while(Curr != NULL)
	{
		
		if(isNumber(Curr->data)==true)
		{
			
			temp=Curr->data-'0';
			push2(d,temp);
		}
		else
		{
			if(isOperator(Curr->data)==true)
			{
				
				ti1=pop2(d);
				ti2=pop2(d);
				
				if(Curr->data=='+')
				{
					ans=ti2 + ti1;
					push2(d,ans);
				}
				else
				{
					if(Curr->data=='-')
					{
						ans=ti2-ti1;
						push2(d,ans);
					}
					else
					{
						if(Curr->data=='*')
						{
							ans=ti2*ti1;
							push2(d,ans);
						}
						else
						{
							if(Curr->data=='/')
							{
								ans=ti2/ti1;
								push2(d,ans);
							}
							else
							{
								if(Curr->data=='^')
								{
									int i=0,x=1;
									while(i<ti1)
									{
										x=x*ti2;
										i++;
									}
									ans=x;
									push2(d,ans);
								}
							}
						}
					}
				}
			}
		}
		Curr=Curr->next;
	}
	

	return ans;
	cout<<endl;
	return 0;		
}
//start of new addition
stackdigit*initstackd()
{
	stackdigit *d;
	
	d=(stackdigit*)malloc(sizeof(stackdigit));
	d->top=-1;
	
	return d;
}

bool diisEmptyst(stackdigit *d)
{
	if(d->top==-1)
	{
		return true;
	}
	return false;
}
float peek2(stackdigit *d)
{
	if(diisEmptyst(d) == true)
	{
		cout<<"empty";
		return -999;
	}
	else
	{
		return	d->element[d->top];
	}
}
bool isFULL(stackdigit *d)
{
	if(d->top==100-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void push2(stackdigit *d,float n)
{
	if(isFULL(d)==true)
	{
		cout<<"stack full";
	}
	else
	{
		d->top=d->top+1;
		d->element[d->top]=n;
	}	
}
float pop2(stackdigit *d)
{
	if(diisEmptyst(d)==true)
	{
		cout<<"empty";
		return-999;
	}
	else
	{
		float b;
		b=d->element[d->top];
		d->top=d->top-1;
		return b;
	}
}





//end of new addition
char peek(stack *s)
{
	Node *top;
	char n;
	
	if(isEmpty(s)==true)
	{
		return 'z';
	}
	else
	{
		top=s->top;
		n=top->data;
		return n;
	}
}
//Assign a precedence value to different types of mathematical operations
int pres(char c)
{
	if(c=='^')
	{
		return 3;
	}
	else
	{
		if(c=='*'||c=='/')
		{
			return 2;
		}
		else
		{
			if(c=='+' || c=='-')
			{
				return 1;
			}
			else
			{
				if(c=='(')
				{
					return 4;
				}
			}
		}
	}
}
//checks if a character passed as a parameter is an operator
//returns true if it is am operator, otherwise false;
bool isOperator(char ch)
{
	if(ch == '+'||ch=='-'||ch=='/'||ch=='*'||ch=='^')
	{
		return true;
	}
	return false;
}
//checks if a character passsed as a parameter is a number
//returns true if it is a number, otherwise false;
bool isNumber(char x)
{
	if(x>='0' && x<='9')
	{
		return true;
	}
	return false;
}
//This function applies the reverse polish alogrithm.
//Need to review, research a shorter way to do this,  too convoluted to follow along.
//Break it apart into multiple functions maybe??? :^( 
Node* RPN(stack*s,Node*top)
{
	Node*curr, *Top2;
	stack *sym,*op,*op2;
	sym=initStack();
	op=initStack();
	op2=initStack();
	curr = top;
	char temp,st,cu;
	int num=0,ff=0,x=0,y=0;
	bool rpc = false;
	
	while(curr != NULL)
	{
		if(isNumber(curr->data)==true)
		{
			cout<<curr->data;
			Top2=insertattail(Top2,curr->data);
		}
		else
		{
			if(isOperator(curr->data)==true)
			{
				if(isEmpty(sym)==true)
				{
					push(sym,curr->data);
				}
				else
				{
					temp=peek(sym);
					
					st=pres(temp);
					cu=pres(curr->data);
					
					if(cu>st)
					{
						push(sym,curr->data);
					}
					else
					{
						if(st==4)
						{
							push(sym,curr->data);
						}
						else
						{
							if(cu<st)
							{
								int t;
								while(isEmpty(sym)!=true)
								{
									temp=peek(sym);
									
									t=pres(temp);
									
									if(t==4)
									{
										break;
									}
									else
									{
										if(t>=cu)
										{

											char test;
											test=pop(sym);
											cout<<test;
											Top2=insertattail(Top2,test);
										}
									}
								}
								
								if(isEmpty(sym)==true||t==4)
								{
									push(sym,curr->data);
								}
							}
							else
							{
								if(cu==st)
								{
									
									char test;
									
									test = pop(sym);
									cout<<test;
									Top2=insertattail(Top2,test);
									push(sym,curr->data);
								}
							}
							
						}
					}
				}
			}
			else
			{
				if(curr->data=='(')
				{
					push(sym,curr->data);
				}
				else
				{
					if(curr->data==')')
					{
						while(isEmpty(sym) != true)
						{
							temp=pop(sym);
							
							if(temp=='(')
							{
								break;
							}
							else
							{
								Top2=insertattail(Top2,temp);
								cout<<temp;
							}
						}
					}
				}
			}
		}
		curr=curr->next;
	}
	
	while(isEmpty(sym) != true)
	{

		char test;
		test=pop(sym);
		cout<<test;
		Top2=insertattail(Top2,test);
	}
	cout<<endl;
	return Top2;

}	


Node*deleteathead(Node*top)
{
	Node*curr;
	
	curr=top;
	
	if(top==NULL)
	{
		return NULL;
	}
	else
	{
		curr=top;
		top=top->next;
		free(curr);
		return top;
	}
}
void push(stack *s,char ch)
{
	s->top=insertathead(s->top,ch);
}

bool isEmpty(stack * s) {

    if(s->top==NULL)
    {
    	return true;
	}
	else
	{
		return false;//return (s->top == NULL);
	}
}

char pop(stack *s)
{
	char ch;
	
	if(isEmpty(s)==true)
	{
		cout<<"Empty Stack";
	}
	else
	{
		ch=s->top->data;
		s->top=deleteathead(s->top);
		return ch;
	}
}
bool isvalid(Node *top)
{
	Node * Curr;
	Curr= top;
	int lparc=0,rparc=0;
	stack *s=initStack();
	bool xr=false;
	while(Curr != NULL)
	{
	
		if(Curr->data=='(')
		{
			push(s,Curr->data);
		}
		
		if((Curr->data==')') &&(isEmpty(s)==false))
		{
			pop(s);
		}
		else
		{
			if((Curr->data==')') &&(isEmpty(s)==true))
			{
				xr=true;
			}
		}
		Curr=Curr->next;
	}
	
	if(isEmpty(s)==true&&xr==false)
	{
		return true;
	}
	else
	{
		if(isEmpty(s)==true && xr==true)
		{
			return false;
		}
		
	}
	
}

stack *initStack()
{
	stack *s;
	s=(stack*)malloc(sizeof(stack));
	s->top=NULL;
	
	return s;
}
Node* creatnode(char ch)
{
	Node *newnode;
	
	newnode=(Node*)malloc(sizeof(Node));
	
	newnode->data=ch;
	newnode->next=NULL;
	
	return newnode;
}

Node *insertathead(Node *top, char ch)
{
	Node *newnode;
	
	newnode =creatnode(ch);
	
	if(top==NULL)
	{
		top=newnode;
	} 
	else
	{
		newnode->next=top;
		top=newnode;
	}
	
	return newnode;
}

Node *insertattail(Node*top,char ch)
{
	Node * newNod;
    Node * lastNode;
    
    newNod = creatnode (ch);
   	lastNode = getLast (top);
   	
   	if(lastNode==NULL)
   	{
   		top=newNod;
   		lastNode=getLast(top);
	}
	else
	{
		lastNode->next=newNod;
	}
	
	return top;
}

Node *getLast (Node * top) {
  
   Node * curr;
   Node * last;
   
   last = NULL;     
   curr = top;
   while (curr != NULL) {
      last = curr;
      curr = curr->next;
   }
   
   return last;
}
void print(Node *top)
{
	Node *curr;
	
	if(top==NULL)
	{
		cout<<"NODE EMTPY";
		return;
	}
	else
	{
		curr=top;
		
		while(curr!= NULL)
		{
			cout<<curr->data;
			
			curr=curr->next;
		}
	}
}

