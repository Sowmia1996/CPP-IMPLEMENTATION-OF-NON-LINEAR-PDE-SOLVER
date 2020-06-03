//not using templates because..facing issues with templates..otherwise could have used prev stack.h only :( :( 
#ifndef STACKAD_H
#define STACKAD_H
#include<iostream>
using namespace std;
class stackad
{
	private:
	int size;
	int curr_size;
	AD1 *array;//ptr to an array of type AD1
	
	public:
	stackad();
	stackad(int);
	void pushback(AD1);
	AD1 pop();
	AD1 top();
	void display();
};
stackad::stackad()
{
	size=0;
	curr_size=0;
	array=NULL;
}
stackad::stackad(int size)
{
	this->size=size;
	this->curr_size=0;
	this->array=new AD1[size]; //ptr to an AD1 array of size=size
}
void stackad::pushback(AD1 f)
{
	array[curr_size]=f;
	curr_size++;
}
AD1 stackad::top()
{
	return array[curr_size-1];
}
AD1 stackad::pop()
{
	AD1 temp=array[curr_size-1];
	curr_size--;
	return temp;
}
void stackad::display()
{
	for(int i=0;i<curr_size;i++)
	{
		array[i].display();
		cout<<endl;
	}
	
}
#endif