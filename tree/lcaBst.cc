#include "BinaryTree.h"
#include <vector>
#include <deque>

using namespace std;

Node* lca(Node* root, int k1, int k2) {
	if (!root) return NULL;
	
	if (root->data >= k1 && root->data >= k2) {
		return lca(root->left, k1, k2);
	} 
	if (root->data < k1 &&  root->data < k2) {
		return lca(root->right, k1, k2);
	} 
	return root;

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
	Node *n = NULL;
	int a , b;
	printf("Enter two numbers\n");
	while (scanf("%d %d", &a, &b) && (a || b)) {
	
		printf("%d\n", ((n = lca(sol.tree, a, b))  && n) ? n->data : -1);
		printf("Enter two numbers\n");
	}
	return 0;
}
