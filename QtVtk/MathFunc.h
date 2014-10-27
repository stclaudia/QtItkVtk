
//#include "stdafx.h"
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;

double omiga(double lams,double lamt)
{
	double gamma=0.5;
	double alpha=0.25;
	
	double w;
	if(-lamt<=lams&&lams<=0)
	{
	w=pow(1+(lams/lamt),gamma);
	}
	else if(lamt/alpha>=lams&&lams>=0)
	{
	w=pow(1-(alpha*(lams/lamt)),gamma);
	}
	else
		w=0;
	return w;
}

double sheet(double lam1,double lam2,double lam3)
{

if (lam3<0)
{
lam3=-lam3;
double weight=lam3*omiga(lam2,lam3)*omiga(lam1,lam3);
cout<<weight<<endl;
return weight;
}
else
	return 0;
}
