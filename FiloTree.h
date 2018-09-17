/*
 * FiloTree.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Tianyi Zhang
 *
 *  CSPC 2120
 *  ASSIGNMENT 3
 */

#ifndef FILOTREE_H_
#define FILOTREE_H_

#include<string>
using namespace std;

typedef struct FiloNode FiloNode;


class FiloTree{

private:
	int deep; //for first constructor
	int strLen; //for second constructor
	FiloNode* root;

public:
	FiloTree(string leaves[], int depth);
	void dump( ) const;
	static bool compare( const FiloTree &A, const FiloTree &B);
	~FiloTree( );
	FiloTree(string fileName);
};


#endif /* FILOTREE_H_ */
