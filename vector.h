#ifndef VECTOR_H
#define VECTOR_H 
#include<iostream>
using namespace std;
class vector{
	private:
	int Size;
	double* ptr;
	
	public:
	vector();
	vector(int);
	void display();
	void setsize(int);
	int size();
	double& operator[](int);
	vector operator-(vector);
	double* getptr();
};
vector::vector()
{
	Size=0;
	ptr=NULL;
}
vector::vector(int size)
{
	this->Size=size;
	ptr=new double[size];
}
int vector::size()
{
	return this->Size;
}

void vector::display()
{
	for(int i=0;i<this->Size;i++)
	{
		cout<<this->ptr[i]<<"\t";
	}
}
void vector::setsize(int size)
{
	delete []ptr;
	this->Size=size;
	this->ptr=new double[size];

}

////////////////////////////////////////////////// BLUNDER!!!!!! SEE WHAT HAPPENS WHEN U DIDN'T RETURN BY REFERENCE!!!!!!(safe it were on rigth side of assignment ..but left side??!!)
//////////////////////////////////////////////////LESSON:DO NOT BLINDLY PASS/return(SEE TO WHETHER PASS BY REF AND RETURN BY REF OR PTR OR VALUE!!)

double& vector::operator[](int i)
{
	return ptr[i];
}
vector vector::operator-(vector v)
{
	vector temp(Size);
	for(int i=0;i<Size;i++)
	{
		temp[i]=ptr[i]-v[i];
	}
	return temp;
}
			





#endif