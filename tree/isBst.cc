#include "BinaryTree.h"
#include <limits>
using namespace std;
const int LO = numeric_limits<int>::min();
const int HI = numeric_limits<int>::max();
bool isBst(Node *root, int lo=LO , int hi=HI) {
	if (!root) return true;
	printf(" for %d  lo : %dhi :%d\n", root->data , lo, hi);
	if (root->data <= lo  ||  root->data > hi)  return false;
	return (isBst(root->left, lo, root->data) && isBst(root->right, root->data, hi));
}



int main() {
	BinaryTree sol;
	sol.addKey(10);
	sol.addKey(21);
	sol.addKey(5);
	sol.addKey(7);
	sol.addKey(2);
	sol.addKey(17);
	sol.addKey(31);
	sol.addKey(19);
	sol.addKey(16);

	sol.printKeys();
	printf("%s",isBst(sol.tree)?"true":"false");
	return 0;
}
