#include "BinaryTree.h"

void morrisPreorder(Node *r) {
	if (!r ) return;
	while (r != NULL) {
		if (r->left == NULL) {
			printf("%d\t",r->data);
			r = r->right; 
		} else {
			Node *pre = r->left;
			while (pre->right && pre->right != r) {
				pre = pre->right;
			}

			if (pre->right == r) {
				pre->right = NULL;
				r = r->right;
			} else {
				pre->right = r;
				printf("%d\t",r->data);
				r = r->left;
			}
		}
	}


	printf("\n");
}
void morrisInorder(Node *r) {
	if (!r ) return;
	while (r != NULL) {
		if (r->left == NULL) {
			printf("%d\t",r->data);
			r = r->right; 
		} else {
			Node *pre = r->left;
			while (pre->right && pre->right != r) {
				pre = pre->right;
			}

			if (pre->right == r) {
				pre->right = NULL;
				printf("%d\t",r->data);
				r = r->right;
			} else {
				pre->right = r;
				r = r->left;
			}
		}
	}

	printf("\n");
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
	morrisInorder(sol.tree);
	sol.printKeys();
	morrisPreorder(sol.tree);
	return 0;
}
