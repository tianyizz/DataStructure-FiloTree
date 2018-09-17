/*
 * test.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: tianyiz
 */

#include<string>
#include<iostream>
using namespace std;

class Adder{
public:
	Adder(){cout<<"1";}
	Adder(Adder& other){cout<<"9";}
	Adder(string name){cout<<"2";}
	virtual void bite(){cout<<"3";}
	virtual ~Adder(){cout<<"4";}
};

class Boa: public Adder{
public:
	Boa(){cout<<"5";}
	Boa(string name){cout<<"6";}
	virtual void bite(){cout<<"7";}
	~Boa(){cout<<"8";}
};

int main(){
	cout<<"Constructor: ";
	Adder A;
	Boa* B=new Boa();
	cout<<endl;
	Adder* C=new Adder(A);
	cout<<endl<<"Bite: ";
	A.bite();
	B->bite();
	C->bite();
	cout<<endl<<"Pointer: ";
	A=*B;
	A.bite();
	B->bite();
	cout<<endl<<"Destructor: ";
	//delete B;
	cout<<endl<<"No Specified: ";
}
