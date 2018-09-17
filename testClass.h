/*
 * testClass.h
 *
 *  Created on: Dec 8, 2017
 *      Author: tianyiz
 */


/*
 * FiloTree.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Tianyi Zhang
 *
 *  CSPC 2120
 *  ASSIGNMENT 3
 */

#ifndef TEST_H_
#define TEST_H_

#include<string>
#include<iostream>
using namespace std;

class Adder{
public:
	Adder(){cout<<"1";}
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

#endif /* FILOTREE_H_ */
