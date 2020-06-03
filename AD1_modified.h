#ifndef AD1_H

#define AD1_H
#include<iostream>
#include"vector.h" //user defined 
#include"matrix.h"// user defined
#include<cmath>
int no_var=0;
class AD1{
private:
	double  f;
	vector fd; 
	int id;  // only independent vars have identity
	
public:
	AD1();
	AD1(double);
	void setval(double);
	void setvariable();
	int putid();
	void setconst();
	//***********************************************************
	AD1 operator+(AD1); //f+g
	AD1 operator*(AD1);
	AD1 operator-(AD1);
	AD1 operator/(AD1);
	AD1 operator^(AD1);
	void operator*=(AD1);
	//***************************************************************
	AD1 operator+(double ); //f+const
	AD1 operator-(double );
	AD1 operator*(double );
	AD1 operator^(double );
	AD1 operator/(double );
	//****************************************************************
	friend AD1 operator+(double,AD1);
	friend AD1 operator-(double,AD1);
	friend AD1 operator*(double,AD1);
	friend AD1 operator/(double,AD1);
	friend AD1 operator^(double,AD1);
	//************************************************************************
	friend AD1 sin(AD1);
	friend AD1 cos(AD1);
	friend AD1 tan(AD1);
	friend AD1 sec(AD1);
	friend AD1 cot(AD1);
	friend AD1 cosec(AD1);
	friend AD1 log(AD1);
	friend AD1 exp(AD1);
	friend AD1 arcsin(AD1);
	friend AD1 arccos(AD1);
	friend AD1 arctan(AD1);
	friend AD1 cosh(AD1);
	friend AD1 sinh(AD1);
	friend AD1 tanh(AD1);

	//*************************************************************************
	void taketurn();
	double getfd(int);
	double getf();
	vector get_gradient(); // receives array of AD1 objects and returns their gradient
	void display();
	//~ AD1();

	
};
matrix get_jacobian(AD1*,int ); 
vector get_fvalue(AD1 *,int );

AD1::AD1()
{
	f=0;
	
	
}

AD1::AD1(double val)
{
	f=val;
	//id=no_var; //you not supposed to do it for every obj ...only for variables
	//no_var++;
}
//call this fn iff the object is a variable
void AD1::setvariable()
{
	id=no_var;
	no_var++;
}

//compulsary do it for each variable object created
void AD1::taketurn()
{
		
		this->fd.setsize(no_var);
		for(int i=0;i<no_var;i++)
		{
			this->fd[i]=0;
		}
		fd[this->id]=1;
}
//setting an object as constant
void AD1::setconst()
{
	this->fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		this->fd[i]=0;
}
//if object's value is not passed initially!!(i will not increment in default constructor ..coz that pertains to calling dependent vars)
void AD1::setval(double value)
{
	this->f=value;
}
int AD1::putid()
{
	return this->id;
}

AD1 AD1::operator+(AD1 g)
{
	AD1 temp;
	temp.f= f+g.f;
	temp.fd.setsize(no_var);
	for(int i =0;i< no_var;i++)
	{
		temp.fd[i]= fd[i]+g.fd[i];
	}
	return temp;
}

AD1 AD1 ::operator -(AD1 g)
{
	 AD1 temp;
	 temp.f= f-g.f;
	 temp.fd.setsize(no_var);
	 for(int i=0;i<no_var;i++)
	 {
			temp.fd[i]=fd[i]-g.fd[i];
	 }
	 return temp;
}

AD1 AD1::operator *(AD1 g)
{
		AD1 temp;
		temp.f=f*g.f;
		temp.fd.setsize(no_var);
		for (int i=0;i<no_var;i++)
		{
			temp.fd[i]=fd[i]*g.f+f*g.fd[i];
		}
		return temp;
}

AD1 AD1 ::operator /(AD1 g)
{
	AD1 temp;
		temp.f=f/g.f;
		temp.fd.setsize(no_var);
		for(int i=0;i<no_var;i++)
			temp.fd[i]=(fd[i]*g.f-g.fd[i]*f)/(g.f * g.f);
		return temp;
	
}

AD1 AD1:: operator^(AD1 g)
{
	AD1 temp;
	temp.f=pow(f,g.f);
	temp.fd.setsize(no_var);
	for (int i=0;i<no_var;i++)
	{
		temp.fd[i]=temp.f*((g.f*fd[i]/f)+(g.fd[i]*log(f)));
	}
	return temp;
}

void AD1 ::operator*=(AD1 g)
{
	f=f*(g.f);
	for(int i=0;i<no_var;i++)
	{
		fd[i]=fd[i]*(g.f)+(g.fd[i])*f;
	}
	
}


AD1 AD1:: operator+(double c)
{
	AD1 temp;
	temp.f=f+c;
	temp.fd.setsize(no_var);
	temp.fd=this->fd;
	return temp;
}

AD1 AD1::operator-(double c)
{
	AD1 temp;
	temp.f=f-c;
	temp.fd.setsize(no_var);
	temp.fd=this->fd;
	return temp;
}
AD1 AD1 :: operator *(double c)
{
	AD1 temp;
	temp.f=f*c;
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=fd[i]*c;
	return temp;
}
AD1 AD1:: operator /(double c)
{
	AD1 temp;
	temp.f=f/c;
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=fd[i]/c;
	return temp;
}
AD1 AD1:: operator^(double c)
{
	AD1 temp;
	temp.f=pow(f,c);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=c*pow(f,c-1)*fd[i];
	return temp;
}
AD1 operator+(double c,AD1 g)
{
	AD1 temp;
	temp.f=c+g.f;
	temp.fd.setsize(no_var);
	temp.fd=g.fd;
	return temp;
}
AD1 operator-(double c,AD1 g)
{
	AD1 temp;
	temp.f=c-g.f;
	temp.fd.setsize(no_var);
	temp.fd=g.fd;
	return temp;
}
AD1 operator*(double c,AD1 g)
{
	AD1 temp;
	temp.f=c*g.f;
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=c*g.fd[i];
	return temp;
}
AD1 operator /(double c,AD1 g)
{
	AD1 temp;
	temp.f=c/g.f;
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=-c*g.fd[i]/g.f*g.f;
	return temp;
}
AD1 operator ^(double c,AD1 g)
{
	AD1 temp;
	temp.f=pow(c,g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=pow(c,g.f)*log(c)*g.fd[i];
	return temp;
}
AD1  sin(AD1 g)
{
	AD1 temp;
	temp.f=sin(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=cos(g.f)*g.fd[i];
	return temp;
}
AD1  cos(AD1 g)
{
	AD1 temp;
	temp.f=cos(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=-sin(g.f)*g.fd[i];
	return temp;
}
AD1 tan(AD1 g)
{
	AD1 temp;
	temp.f=tan(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=pow(1/cos(g.f),2)*g.fd[i];
	return temp;
}
AD1 cot(AD1 g)
{
	AD1 temp;
	temp.f=1/tan(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=-pow(1/sin(g.f),2)*g.fd[i];
	return temp;
}
AD1 sec(AD1 g)
{
	AD1 temp;
	temp.f=1/cos(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=1/cos(g.f)*tan(g.f)*g.fd[i];
	return temp;
}
AD1 cosec(AD1 g)
{
	AD1 temp;
	temp.f=1/sin(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=-(1/sin(g.f))*(1/tan(g.f))*g.fd[i];
	return temp;
}
AD1 arcsin(AD1 g)
{
	AD1 temp;
	temp.f=asin(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=g.fd[i]/sqrt(1-(g.f*g.f));
	return temp;
}
AD1 arccos(AD1 g)
{
	AD1 temp;
	temp.f=acos(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=-g.fd[i]/sqrt(1-(g.f*g.f));
	return temp;
}
AD1 arctan(AD1 g)
{
	AD1 temp;
	temp.f=atan(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=g.fd[i]/(1+(g.f*g.f));
	return temp;
}

AD1 cosh(AD1 g)
{
	AD1 temp;
	temp.f=cosh(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=sinh(g.f)*g.fd[i];
	return temp;
}
AD1 sinh(AD1 g)
{
	AD1 temp;
	temp.f=sinh(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=cosh(g.f)*g.fd[i];
	return temp;
}
AD1 tanh(AD1 g)
{
	AD1 temp;
	temp.f=tanh(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=(pow(cosh(g.f),2)-pow(sinh(g.f),2))*g.fd[i]/(pow(cosh(g.f),2));
	return temp;
}

AD1 log(AD1 g)
{
	AD1 temp;
	temp.f=log(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=g.fd[i]/(g.f);
	return temp;
}

AD1 exp(AD1 g)
{
	AD1 temp;
	temp.f=exp(g.f);
	temp.fd.setsize(no_var);
	for(int i=0;i<no_var;i++)
		temp.fd[i]=exp(g.f)*g.fd[i];
	return temp;
}

double AD1:: getfd(int i)
{
	return this->fd[i];
}
double AD1::getf()
{
	return this->f;
}
vector AD1::get_gradient()
{
	
	return this->fd;
}


//this will alter for sparse matrix
matrix get_jacobian(AD1 *ptr,int size)
{
	int count=0;
	matrix temp(size,no_var);
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<no_var;j++)
		{
			
			
				temp(i,j,ptr[i].getfd(j));
				
		}
	}
	
	return temp;
}

vector get_fvalue(AD1 *ptr,int size)
{
	vector temp(size);
	for(int i=0;i<size;i++)
		temp[i]=ptr[i].getf();
	return temp;
}

		
		
void AD1:: display()
{
	
	cout<<"value:"<<this->f;
	cout<<"grad:";
	for(int i=0;i<no_var;i++)
		cout<<this->fd[i]<<"\t";
}
	
#endif
