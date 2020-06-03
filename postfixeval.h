#ifndef POSTFIXEVAL_H
#define POSTFIXEVAL_H
#include"AD1_modified.h"
#include "vector.h"
#include "stack.h"
#include "stackad.h"
#include<iostream>
#include<string>
#include<ctype.h>
using namespace std;
struct ll
{
	char character;
	ll *next;
};
class postfixeval
{
	private:
		int size;
		ll* head; //ptr to   linked list(to hold postfix exp)
		AD1* ptr;//ptr to array of AD1 objects
	public:
	postfixeval();
	postfixeval(int);
	ll* infixtopostfix(string);
	AD1 evaluate(vector,ll*,int,int,int,int);//initiall guess as vector
};
int precedence(char);
postfixeval::postfixeval()
{
	size=0;
	head=NULL;
	ptr=NULL;
	
}
postfixeval::postfixeval(int size)
{
	this->size=size;
	head=NULL;
	ptr=new AD1[size];//creating size-no of AD objects(these are vars )
	for(int i=0;i<size;i++)
	{
		ptr[i].setval(0);//initial all have values 0
		ptr[i].setvariable();//give them ids
	}
	//initilising their fds
	for(int i=0;i<size;i++)
		ptr[i].taketurn();
	
}

//note: this methodd assumes the expression starts with( and ends with ).
//also:this method does not take care of mathematical expressions(update required)
//and this method assumes the constants that appear in the expression are single digits(update required)
ll* postfixeval::infixtopostfix(string s)
{
	stack st(s.length());
	for(int i=0;i<s.length();i++)
	{
		 if((s[i] >= 'a' && s[i] <= 'z')||(s[i] >= 'A' && s[i] <= 'Z')||(isdigit(s[i]))) //if operand or a const is encountered ..put in ll
		 {
			 if(head==NULL) //if ll is empty
			 {
				 head=new ll;
				 head->character=s[i];
				 head->next=NULL;
			 }
			 else  //if ll not empty
			 {
				 ll* travelptr=head;
				 while(travelptr->next!=NULL)
					 travelptr=travelptr->next;
				 travelptr->next=new ll;
				 travelptr->next->character=s[i];
				 travelptr->next->next=NULL;
			 }
		 }
		 
		 else if(s[i]=='(') // if '(' is encountered ..push in stack
		 st.pushback(s[i]);
		 
		 else if(s[i]==')')//if ')' is encountered ... pop from stack until a '(' is encountered and put in ll 
		 {
			 while(st.top()!= '(' )
			 {
				 char temp=st.pop();
				 ll* travelptr=head;
				 while(travelptr->next!=NULL)
					 travelptr=travelptr->next;
				 travelptr->next=new ll;
				 travelptr->next->character=temp;
				 travelptr->next->next=NULL;
			 }
			 if(st.top()=='(')
				st.pop();
		 }
		 else //an operator is encountered
		 {
			 while(precedence(s[i])<=precedence(st.top())&& st.top()!=')' && st.top()!='(')
			 {
				 char temp=st.pop();
				 ll* travelptr=head;
				 while(travelptr->next!=NULL)
					 travelptr=travelptr->next;
				 travelptr->next=new ll;
				 travelptr->next->character=temp;
				 travelptr->next->next=NULL;
			 }
			 st.pushback(s[i]);
		 }
	}
	//ll* travelptr=head;
	//while(travelptr!=NULL)
	//{
	//	cout<<travelptr->character;
	//	travelptr=travelptr->next;
	//}
	return head;
}

int precedence(char s)
{
    if(s == '^') 
    return 3; 
    else if(s == '*' || s == '/') 
    return 2; 
    else if(s == '+' || s == '-') 
    return 1; 
    else
    return -1; 
} 
AD1 postfixeval::evaluate(vector v,ll* head,int i,int j,int xs,int ys)//i and j are indices of (x,y) in their respective vectors X,Y
{
	stackad st(100);//fill length of expression
	ll* travelptr=head;
	while(travelptr!=NULL)
	{
		//if a is encounterd ..it is u(i,j)

		if(travelptr->character=='a')
		{
			
			ptr[ys*i+j].setval(v[0]);
			st.pushback(ptr[ys*i+j]);
			travelptr=travelptr->next;
		}
		
		// if x or y is encountered initialise with the cordinate values
		else if(travelptr->character=='x')
		{
			AD1 object(v[5]);
			object.setconst();
			st.pushback(object);
			travelptr=travelptr->next;
		}
		else if(travelptr->character=='y')
		{
			AD1 object(v[6]);
			object.setconst();
			st.pushback(object);
			travelptr=travelptr->next;
		}
		else if(isdigit(travelptr->character))
		{
			char temp=travelptr->character;
			int value=temp-'0';
			AD1 object(value);
			object.setconst();
			st.pushback(object);
			travelptr=travelptr->next;
		}
		
		//now if b or c or d or e is encountered,we have to take cases
		//case1) (i,j) is a corner point
					//subcases:left up corner,left down corner,right up corner,right down corner
		//case2)(i,j) is a border point
					//subcases:left border,right border,upper border,lower border
		//case3)(i,j) is a interior point
		
		
		
		else if(travelptr->character=='b' ||travelptr->character=='c' ||travelptr->character=='d'||travelptr->character=='e')
		{
			
			if(i==0 && j==0)//left-up corner
			{
				if(travelptr->character=='b')
				{
					ptr[1].setval(v[1]);
					st.pushback(ptr[1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					AD1 object(v[2]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					ptr[ys].setval(v[3]);
					st.pushback(ptr[ys]);
					travelptr=travelptr->next;
				}
				else
				{
					AD1 object(v[4]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
			}
			else if(i==0 && j==ys-1)// right-up corner
			{
				if(travelptr->character=='b')
				{
					AD1 object(v[1]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					ptr[ys-2].setval(v[2]);
					st.pushback(ptr[ys-2]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					ptr[2*ys-1].setval(v[3]);
					st.pushback(ptr[2*ys-1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					AD1 object(v[4]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
			}
			else if(i==xs-1 && j==0)//left-lower corner
			{
				if(travelptr->character=='b')
				{
					ptr[(xs-1)*ys+1].setval(v[1]);
					st.pushback(ptr[(xs-1)*ys+1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					AD1 object(v[2]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					AD1 object(v[3]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					ptr[ys*(xs-2)].setval(v[4]);
					st.pushback(ptr[ys*(xs-2)]);
					travelptr=travelptr->next;
				}
			}
			else if(i==xs-1 && j==ys-1)//right-lower corner
			{
				if(travelptr->character=='b')
				{
					AD1 object(v[1]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					ptr[ys*xs-2].setval(v[2]);
					st.pushback(ptr[xs*ys-2]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					AD1 object(v[3]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					ptr[(xs-1)*ys-1].setval(v[4]);
					st.pushback(ptr[(xs-1)*ys-1]);
					travelptr=travelptr->next;
				}
			}
			else if(i==0 )//upper border
			{
				
				if(travelptr->character=='b')
				{
					ptr[j+1].setval(v[1]);
					st.pushback(ptr[j+1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					ptr[j-1].setval(v[2]);
					st.pushback(ptr[j-1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					ptr[ys+j].setval(v[3]);
					st.pushback(ptr[ys+j]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					AD1 object(v[4]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
			}
			else if(i==xs-1)//lower border
			{
				
				if(travelptr->character=='b')
				{
					ptr[ys*i+j+1].setval(v[1]);
					st.pushback(ptr[ys*i+j+1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					ptr[ys*i+j-1].setval(v[2]);
					st.pushback(ptr[ys*i+j-1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					AD1 object(v[3]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					ptr[ys*(i-1)+j].setval(v[4]);
					st.pushback(ptr[ys*(i-1)+j]);
					travelptr=travelptr->next;
				}
			}
			else if(j==0)//left border
			{
				
				if(travelptr->character=='b')
				{
					ptr[ys*i+1].setval(v[1]);
					st.pushback(ptr[ys*i+1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					AD1 object(v[2]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')
				{
					ptr[ys*(i+1)].setval(v[3]);
					st.pushback(ptr[ys*(i+1)]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					ptr[ys*(i-1)].setval(v[4]);
					st.pushback(ptr[ys*(i-1)]);
					travelptr=travelptr->next;
				}
			}
			else if(j==ys-1)//right border
			{
				
				if(travelptr->character=='b')
				{
					AD1 object(v[1]);
					object.setconst();
					st.pushback(object);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					ptr[ys*i+j-1].setval(v[2]);
					st.pushback(ptr[ys*i+j-1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')//start here
				{
					ptr[ys*(i+1)+j].setval(v[3]);
					st.pushback(ptr[ys*(i+1)+j]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					ptr[ys*(i-1)+j].setval(v[4]);
					st.pushback(ptr[ys*(i-1)+j]);
					travelptr=travelptr->next;
				}
			}
			else //interior points
			{
				
				if(travelptr->character=='b')
				{
					ptr[ys*i+j+1].setval(v[2]);
					st.pushback(ptr[ys*i+j+1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='c')
				{
					ptr[ys*i+j-1].setval(v[2]);
					st.pushback(ptr[ys*i+j-1]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='d')//start here
				{
					ptr[ys*(i+1)+j].setval(v[3]);
					st.pushback(ptr[ys*(i+1)+j]);
					travelptr=travelptr->next;
				}
				else if(travelptr->character=='e')
				{
					ptr[ys*(i-1)+j].setval(v[4]);
					st.pushback(ptr[ys*(i-1)+j]);
					travelptr=travelptr->next;
				}
			}
		}
			
			
				
				
				
						
				
				
				
		else //operator encountered
		{
			AD1 temp;
			if(travelptr->character=='*')
			{
				AD1 f=st.pop();
				AD1 g=st.pop();
				temp=g*f;
				st.pushback(temp);
				travelptr=travelptr->next;
			}
			else if(travelptr->character=='/')
			{
				AD1 f=st.pop();
				AD1 g=st.pop();
				temp=g/f;
				st.pushback(temp);
				travelptr=travelptr->next;
			}
			else if(travelptr->character=='+')
			{
				AD1 f=st.pop();
				AD1 g=st.pop();
				temp=g+f;
				st.pushback(temp);
				travelptr=travelptr->next;
			}
			else if(travelptr->character=='-')
			{
				AD1 f=st.pop();
				AD1 g=st.pop();
				temp=g-f;
				st.pushback(temp);
				travelptr=travelptr->next;
			}
			else if(travelptr->character=='^')
			{
				AD1 f=st.pop();
				AD1 g=st.pop();
				temp=g^f;
				st.pushback(temp);
				travelptr=travelptr->next;
			}
		}
	}
	
	return st.pop();
}
#endif
