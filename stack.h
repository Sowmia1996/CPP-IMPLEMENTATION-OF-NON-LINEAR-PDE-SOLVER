#ifndef STACK_H
#define STACK_H
#include<iostream>
using namespace std;
class stack
{
	private:
	int size;
	int curr_size;
	char* array;//ptr to char array
	
	public:
	stack();
	stack(int);
	void pushback(char);
	char top();
	char pop();
	void display();
};
stack::stack()
{}
stack::stack(int size)
{
	this->size=size;
	this->curr_size=0;
	array=new char[size];

	
}
void stack::pushback(char symbol)
{
		array[curr_size]=symbol;
		curr_size++;
		
}
char stack:: pop()
{
	char temp;
	temp=array[curr_size-1];
	curr_size--;
	return temp;
}
char stack:: top()
{
	return array[curr_size-1];
}
void stack::display()
{
	for(int i=0;i<curr_size;i++)
		cout<<array[i];
}

	
#endif