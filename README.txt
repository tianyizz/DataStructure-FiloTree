For the easiness of reading, detailed analysis regarding complexity is commented throughout the FiloTree.cpp file, below is a summary:

FiloTree(string leaves[], int depth):
O(n), with n as the number of the strings, because the way my code implemented...
*The complexity could be O(2^n) if n is the depth input

void dump( ) const:
O(n), with n as the number of the nodes, because the dump method visited each node once to print the content

static bool compare( const FiloTree &A, const FiloTree &B):
O(n^2), with n as the number of the nodes, because the basic algorithem for this function is to compare every left child and every right child of the two trees with each other, which means, each node of the two trees are visited twice in the worst case.

~FiloTree( ):
O(n), with n as number of the nodes, because the constructor recursively visited every single node once

FiloTree(string fileName):
Complexity is O(n^2) n is the number of the strings, based on the way my code works...

