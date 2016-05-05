#include "BinaryTree.h"


Node *mybsearch(Node *r, int key) {
	if (!r) return NULL;
	if (r->data == key) return r;
	if (r->data > key) return mybsearch(r->left, key);
	return mybsearch(r->right , key);
}
//duplicate keys

int main () {
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
	printf("\n");
		
	for (int k = 0 ; k < 32; ++k) {
		printf("k = %d at %p\n",k, mybsearch(sol.tree, k));
	}
	printf("\n");


		
}
