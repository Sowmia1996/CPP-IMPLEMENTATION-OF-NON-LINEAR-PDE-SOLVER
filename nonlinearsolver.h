#ifndef NONLINEARSOLVER_H
#define NONLINEARSOLVER_H
#include<iostream>
#include"vector.h"
#include"postfixeval.h"
#include"linearsolver_mod.h"
#include"AD1_modified.h"
using namespace std;
class nonlinearsolver
{
	private:
	vector guess;
	int noiter;
	int nomesh; // no of meshpoints
	int xs; //no of mesh-points along y-axis
	int ys; //no of mesh-points along x-axis
	
	public:
	nonlinearsolver();
	nonlinearsolver(int,int,vector);
	void newton(ll*,float,float,float,float,int,int,int ,int );
	//void broyden(string*);
};
nonlinearsolver::nonlinearsolver()
{
	noiter=1;
	nomesh=0;
	xs=0;
	ys=0;
}
nonlinearsolver::nonlinearsolver(int xs,int ys,vector v)
{
	noiter=1;
	nomesh=xs*ys;
	this->xs=xs;
	this->ys=ys;
	guess=v;
	
}
void nonlinearsolver::newton(ll*head,float a,float b,float c,float d,int p,int s,int h, int k)
{
	
	AD1 *ptr=new AD1[nomesh];//'nomesh'-number of AD1 objects to store the evaluated fns 
	vector B;//vector to hold the evaluted system of fns 
	matrix M;//matrix to hold the jacobian of system of eqns
	vector u(7);//vector to send(u(i,j),u(i+1,j),u(i-1.j),u(i,j+1),u(i,j-1),x,y) as arguements to evaluate
	for(int l=0;l<noiter;l++)//for each iteration
	{
		postfixeval eval(nomesh);
		for(int i=0;i<xs;i++)
		{			
			for(int j=0;j<ys;j++)
			{
				
				u[0]=guess[ys*i+j];
				u[5]=p+(j+1)*h;
				u[6]=s-(i+1)*k;
				if(i==0 && j==0)//left-up corner
				{
					u[1]=guess[ys*i+j+1];
					u[2]=a;
					u[3]=guess[ys*(i+1)+j];
					u[4]=c;
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//ptr[ys*i+j].display();
				}
				else if(i==0 && j==ys-1)// right-up corner
				{
					u[1]=b;
					u[2]=guess[ys*i+j-1];
					u[3]=guess[ys*(i+1)+j];
					u[4]=c;
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
				else if(i==xs-1 && j==0)//left-lower corner
				{
					u[1]=guess[ys*i+j+1];
					u[2]=a;
					u[3]=d;
					u[4]=guess[ys*(i-1)+j];
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
					
				}
				else if(i==xs-1 && j==ys-1)//right-lower corner
				{
					u[1]=b;
					u[2]=guess[ys*i+j-1];
					u[3]=d;
					u[4]=guess[ys*(i-1)+j];
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
				else if(i==0 )//upper border
				{
					u[1]=guess[ys*i+j+1];
					u[2]=guess[ys*i+j-1];
					u[3]=guess[ys*(i+1)+j];
					u[4]=c;
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
				else if(i==xs-1)//lower border
				{
					u[1]=guess[ys*i+j+1];
					u[2]=guess[ys*i+j-1];
					u[3]=d;
					u[4]=guess[ys*(i-1)+j];
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
				else if(j==0)//left border
				{
					u[1]=guess[ys*i+j+1];
					u[2]=a;
					u[3]=guess[ys*(i+1)+j];
					u[4]=guess[ys*(i-1)+j];
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
				else if(j==ys-1)//right border
				{
					u[1]=b;
					u[2]=guess[ys*i+j-1];
					u[3]=guess[ys*(i+1)+j];
					u[4]=guess[ys*(i-1)+j];
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
				else //interior points
				{
					u[1]=guess[ys*i+j+1];
					u[2]=guess[ys*i+j-1];
					u[3]=guess[ys*(i+1)+j];
					u[4]=guess[ys*(i-1)+j];
					ptr[ys*i+j]=eval.evaluate(u,head,i,j,xs,ys);
					//cout<<endl;
					//ptr[ys*i+j].display();
				}
			}
		}
		cout<<"\n\n";
		//getting the jacobian(F'(x)) of the system
		M=get_jacobian(ptr,nomesh);
		cout<<"for the last iteration,jacobian(F'(x)) is :"<<endl;
		M.display();
		cout<<"\n \n";
		//getting the F(x) of the system
		B=get_fvalue(ptr,nomesh);
		cout<<"for the last iteration,F(x) is :"<<endl;
		B.display();
		cout<<"\n\n";
		//solving the system F'(x)z=F(x) 
		linearsolver solver;
		vector solution =solver.GUASS_SOLVE(M,B);
		
		cout<<endl;
		guess=guess-solution;          //updating guess
		cout<<"for the last iteration the solution is given by:"<<endl;
		guess.display();
		cout<<"\n\n";
	}
	
	
}

#endif