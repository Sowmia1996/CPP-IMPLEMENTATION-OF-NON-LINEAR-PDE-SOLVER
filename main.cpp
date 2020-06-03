#include "nlpde.h"
#include<iostream>
#include<string>
#include"postfixeval.h"
using namespace std;
int main()
{
	string s[5];
	//solving problem 1 u_x''+u_y''=xy//
	s[0]="1";
	s[1]="1";
	s[2]="0";
	s[3]="0";
	s[4]="x*y";
	nlpde object(1,8,1,8,6,6.8,5.5,5,s);
	cout<<"the discretised equation is :"<<endl;
	ll*head=object.equation();
	ll* tvlptr=head;
	cout<<"\n";
	cout<<"the discretised equation in the postfix form is:"<<endl;
	while(tvlptr!=NULL)
	{
		cout<<tvlptr->character;
		tvlptr=tvlptr->next;
	}

	object.solve(head);
	return 0;
}