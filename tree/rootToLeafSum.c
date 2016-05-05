#include "BinaryTree.h"

bool hasPathSum(Node *root, int sum) {
	if (!root) {
		return false;
	}
	if (isLeaf(root) && sum == root->data) return true;
	return (hasPathSum(root->right, sum- root->data)|| hasPathSum(root->left, sum - root->data));
	
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

	for (int  k = 15 ; k < 130; ++k) {
		printf("sum %d : %s\n",k,	hasPathSum(sol.tree, k)?"true":"false");
	}
	printf("\n");

	return 0;
}
