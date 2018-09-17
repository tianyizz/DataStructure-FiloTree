// SyntaxCheckerFilo.cpp
// goddard - 2017
#include <iostream>
using namespace std;
#include "FiloTree.h"

int main( )
{
  string test[] = {"Art", "Business", "Chemistry", "Dentistry"};
  FiloTree F( test, 2);
  F.dump( );
  cout << endl;

  string testToo[] = {"Art", "Chemistry", "Business", "Dentistry"};
  FiloTree I( testToo, 2);
  cout << boolalpha << FiloTree::compare(F,I) << endl;  // should be false
  cout << endl;

  FiloTree G("ABCD.txt");
  G.dump( );
  cout << boolalpha << FiloTree::compare(F,G) << endl; // should be true
  cout << endl;

  FiloTree H("ABCDtoo.txt");
  H.dump( );
  cout << boolalpha << FiloTree::compare(F,H) << endl; // should be false

  FiloTree X("test1.txt");
    X.dump( );
    cout << boolalpha << FiloTree::compare(H,X) << endl; // should be false

    FiloTree Z("test2.txt");
      Z.dump( );
      cout << boolalpha << FiloTree::compare(Z,X) << endl; // should be false
  return 0;
}
