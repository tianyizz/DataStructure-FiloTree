/*
 * FiloTree.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Tianyi Zhang
 *
 *  CSPC 2120
 *  ASSIGNMENT 3
 */

#include<stdbool.h>
#include<string>
#include<fstream>
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<cfloat>
#include<limits>
#include"FiloTree.h"

using namespace std;

struct FiloNode{
	string* node;
	FiloNode* leftLink;
	FiloNode* rightLink;

public:
	FiloNode(string* S): node(S),leftLink(nullptr),rightLink(nullptr){}
	FiloNode():node(nullptr),leftLink(nullptr),rightLink(nullptr){
		node=new string("X");
	}
};

//Main constructor for the first constructor
//COmplexity is O(n)
void Derive(string input[],int dep,FiloNode* node){
	int length=(int)pow(2,dep+1)-1;
	int strTotal=(int)pow(2,dep);
	int insert=0;

	if(!(dep>0))return;

	//construct the whole thing based on an array just like a heap but without order
	FiloNode** filoArray=new FiloNode*[length];
	filoArray[0]=node;

	//Complexity: O(2n-1) n is number of the strings
	for(int i=1;i<length;i++){

		if(i<(length-strTotal)){
			FiloNode* newNode=new FiloNode();
			filoArray[i]=newNode;
		}
		else{
			FiloNode* newNode=new FiloNode(&input[insert]);
			filoArray[i]=newNode;
			insert++;
		}

		if(i%2!=0)
		 filoArray[(i-1)/2]->leftLink=filoArray[i];
		else
		 filoArray[(i-1)/2]->rightLink=filoArray[i];
	}

	delete[] filoArray;
}

//Primary destructor
//Complexity O(n) visited every node
void Destroy(FiloNode*node,bool d){

	if(node->leftLink!=nullptr)
		Destroy(node->leftLink,d);
	if(node->rightLink!=nullptr)
		Destroy(node->rightLink,d);

	//delete string if they are created in the process of creating trees
	//(not originally given in the main function)
	if(d)
		delete node->node;
	else if((*node->node).compare("X")==0)
		delete node->node;


	delete node;
}

//whole bunch of helping function to make the code cleaner
//Complexity is O(1) for each of them
bool isString(FiloNode* node){
	return (node->leftLink==nullptr&&node->rightLink==nullptr);
}

bool isParent(FiloNode* node){

	if(isString(node))return false;

	return (isString(node->leftLink)&&isString(node->rightLink));
}

bool hasOneString(FiloNode* node){

	if(isString(node))return false;

	return (isString(node->leftLink)&&!isString(node->rightLink))||
			(!isString(node->leftLink)&&isString(node->rightLink));
}

bool isCommute(FiloNode* node){
	return (node->leftLink!=nullptr&&node->rightLink!=nullptr);
}

//primary print function, a standard preorder recursive
//Complexity is O(n) because visited every node
void printOut(FiloNode* inputNode,int dep){
	//static int count=0;
	int i=dep;

	while(i--)
		cout<<"...";

	cout<<*(inputNode->node)<<endl;


	if(inputNode->leftLink!=nullptr)
		printOut(inputNode->leftLink,dep+1);

	if(inputNode->rightLink!=nullptr)
		printOut(inputNode->rightLink,dep+1);

}

//Merge function that edits the actual number matrix and string array
//Complexity is O(n^2)
void arrayMerge(int pos[],FiloNode* input[],double** inputNum,int length,int cur){
	int min,max;

	//Always merge towards the left
	if(pos[0]<pos[1]){
		min=pos[0];
		max=pos[1];
	}
	else{
		min=pos[1];
		max=pos[0];
	}

	//calculate the new distance and modify in the leftmost position found
	//Complexity: O(n) n is the number of the string
	for(int i=0;i<length;i++){
		if(i!=min){
			inputNum[i][min]=(inputNum[i][min]+inputNum[i][max])/2;
			inputNum[min][i]=inputNum[i][min];
		}
	}

	//creating commute node
	string* str=new string(to_string(cur));
	FiloNode* newNode=new FiloNode(str);

	//insert the commute node
	if((!isString(input[min]))&&(!isString(input[max]))){
		int tempMin=stoi(*(input[min]->node));
		int tempMax=stoi(*(input[max]->node));

		if(tempMax<tempMin){
			newNode->leftLink=input[max];
			newNode->rightLink=input[min];
		}
		else{
			newNode->leftLink=input[min];
			newNode->rightLink=input[max];
		}

	}else{
		newNode->leftLink=input[min];
		newNode->rightLink=input[max];
	}

	input[min]=newNode;

	//matricies reduction
	/*
	 * Always eleminating the rightmost string
	 */
	//Complexity is O(n^2) n is the number of the string
	for(int a=max;a<length-1;a++){
		input[a]=input[a+1];

		for(int b=0;b<length;b++){
			inputNum[b][a]=inputNum[b][a+1];
			inputNum[a][b]=inputNum[b][a];
		}

		inputNum[a][a]=0;
	}

}

//Main merge function
//Complexity is O(n^2)
FiloNode* filoMerge(FiloNode* input[],double** inputNum,int length){
	double min=DBL_MAX;
	int minPos[2]={0,1};
	int nodeCount=1;

	if(length<1) return nullptr;

	while(length>1){

	//find the minimum position
	//Complexity is O(n^2) n is the number of the string
	for(int a=0;a<length;a++){
		for(int b=0;b<length;b++){
			if(inputNum[a][b]!=0&&inputNum[a][b]<min){
				min=inputNum[a][b];
				minPos[0]=a;
				minPos[1]=b;
			}
		}
	}

	//matrices reduction function after the next minimum position is found
	//Complexity is O(n^2) from last function comments
	arrayMerge(minPos,input,inputNum,length,nodeCount);
	length--;
	nodeCount++;
	min=DBL_MAX;
	}



	return input[0];

}

//the compare function
/*The compare function follows a fundamental logic:
 * compare every left child and right child of the two input trees
 * So, if n is the number of the node, the complexity of the function is
 * O(n^2)
 * */
bool compareChild(FiloNode* nodeA, FiloNode* nodeB){

	//function does not consider for special cases
	//filoNode function is supposed to take care of them
	//before using this function to solve tree
	FiloNode* a=nodeA;
	FiloNode* b=nodeB;

	/*
	 * Compare the tree as a unit of three nodes
	 * setup different cases as string node, node with one string and one commute
	 * , node with two commute, node with two string. Another cases are false.*/
	if(isString(a)&&isString(b)){

		return ((*(a->node)).compare(*(b->node))==0);

	}
	else if(hasOneString(a)&&hasOneString(b)){

		//identify the string node compare it and compare the commute node (rest of the tree)
			if(isString(a->leftLink)){
				if(isString(b->leftLink)){
					return ((*(a->leftLink->node)).compare(*(b->leftLink->node))==0&&
							compareChild(a->rightLink,b->rightLink));
				}
				else{
					return ((*(a->leftLink->node)).compare(*(b->rightLink->node))==0&&compareChild(a->rightLink,b->leftLink));
				}
			}
			else{
				if(isString(b->leftLink)){
					return ((*(a->rightLink->node)).compare(*(b->leftLink->node))==0&&
							compareChild(a->leftLink,b->rightLink));
				}
				else{
					return ((*(a->rightLink->node)).compare(*(b->rightLink->node))==0)&&compareChild(a->leftLink,b->leftLink);
				}
			}

	}
	else if(isParent(a)&&isParent(b)){
			bool finda=false;
			bool findb=false;

			//if parents, straight up compare for the child for equal
			if(((*(a->leftLink->node)).compare(*(b->leftLink->node))==0)||
				((*(a->leftLink->node)).compare(*(b->rightLink->node))==0))
				finda=true;

			if(((*(a->rightLink->node)).compare(*(b->leftLink->node))==0)||
			   ((*(a->rightLink->node)).compare(*(b->rightLink->node))==0))
			    findb=true;

			return finda&&findb;
	}
	else if(isCommute(a)&&(isCommute(b))){

		//if commute, compare each possible pair, see the logic for details.
		bool findaLeft=compareChild(a->leftLink,b->leftLink)||compareChild(a->leftLink,b->rightLink);
		bool findaRight=compareChild(a->rightLink,b->leftLink)||compareChild(a->rightLink,b->rightLink);
		return findaLeft&&findaRight;

	}
	else
		//other cases
		return false;


}



//Public methods for FiloTree Class
//O(n)
FiloTree::FiloTree(string leaves[], int depth):deep(depth),strLen(-1),root(nullptr){
	if(depth>0){
		root=new FiloNode();

		//do the derive
		Derive(leaves,depth,root);
	}
	else if(depth==0){
		root=new FiloNode(&leaves[0]);
	}
	else{
		cout<<"need a valid input number."<<endl;
	}
}

//O(n)
void FiloTree::dump( ) const{
	if(root==nullptr)return;
	printOut(root,0);
}


//O(n^2)
bool FiloTree::compare( const FiloTree &A, const FiloTree &B){

	//Special cases
	if((A.deep==0&&B.deep==0)||(A.deep==0&&B.strLen==0)||
	   (A.strLen==0&&B.deep==0)||(A.strLen==0&&B.strLen==0))
		return true;

	//determine the number of leaves for A and B
	int mA=(A.strLen==-1?(int)pow(2,(double)A.deep):A.strLen);
	int mB=(B.strLen==-1?(int)pow(2,(double)B.deep):B.strLen);

	//return false if they not equal
	if(mA!=mB)return false;

	//otherwise start compare
	return compareChild(A.root,B.root);
}


//O(n)
FiloTree::~FiloTree( ){

	//second constructor and the first constructor
	//have different deleting method
	if(root!=nullptr){
		if(deep==-1)
		Destroy(root,true);
		else
		Destroy(root,false);
	}
}

//Complexity is O(n^2) n is the number of the strings
FiloTree::FiloTree(string fileName):deep(-1),strLen(-1),root(nullptr){

	ifstream inFile;

	inFile.open(fileName.c_str());
	inFile>>strLen;

	if(strLen<0){
		cout<<"Need a valid input number."<<endl;
		return;
	}

	//Temporary string Array to store string inputs
	string** strArray=new string*[strLen];
	string tempStr;

	//O(n)
	for(int i=0;i<strLen;i++){
		inFile>>tempStr;
		strArray[i]=new string(tempStr);
	}

	//Temporary matrix to store the numbers
	//O(n)
	double** numArray=new double*[strLen];
	for(int a=0;a<strLen;a++)
		numArray[a]=new double[strLen];

	for(int a=0;a<strLen;a++){
		for(int b=0;b<strLen;b++){
			inFile>>numArray[a][b];
		}
	}

	//All the filoNode needed for the tree
	FiloNode** FiloArray = new FiloNode*[strLen];

	for(int a=0;a<strLen;a++)
		FiloArray[a]=new FiloNode(strArray[a]);

	//Create the tree
	//O(n^2)
	FiloNode* temp=filoMerge(FiloArray,numArray,strLen);

	if(temp!=nullptr)root=temp;

	cout<<endl;

	//release the temporary storage
	if(strLen>0){
		delete [] strArray;

		for(int a=0;a<strLen;a++){
			delete []numArray[a];
		}

		delete []numArray;
		delete []FiloArray;
	}

}
