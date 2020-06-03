#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include "vector.h"
using namespace std;
class matrix{
	private:
	int rows;
	int cols;
	vector* ptr;
	public:
	matrix();
	matrix(int,int);
	matrix(int);
	double& operator()(int,int);
	void operator()(int,int,double);
	void display();
};

matrix::matrix()
{
	rows=0;
	cols=0;
	ptr=NULL;
}
matrix::matrix(int rows,int cols)
{
	this->rows=rows;
	this->cols=cols;
	ptr =new vector[rows];
	for(int i=0;i<rows;i++)
		ptr[i].setsize(cols);
}
matrix::matrix(int size)
{
	this->rows=size;
	this->cols=size;
	ptr=new vector[size];
	for(int i=0;i<size;i++)
		ptr[i].setsize(size);
}

double& matrix::operator()(int i,int j)
{
	return ptr[i][j];
}
void matrix::display()
{
	for(int i=0;i<rows;i++)
	{
		ptr[i].display();
		cout<<endl;
	}
}
void matrix::operator()(int  a,int  b,double  c)
{
	this->ptr[a][b]=c;
}
#endif