#include <iostream>
#include <cstdio>

class Node {
	public:
		Node(int k=0) : data (k) , left(0), right(0) ,parent(0) {}
		int data;
		Node *left, *right, *parent;
};


class InorderIterative{
	private :
		Node *tree;

	public:
		InorderIterative():tree(0){}
		void addKey(int k) {
			tree =  addKeyHelper(k , tree);
		}
		Node* addKeyHelper(int k , Node *root) {
			if (!root) {
				root= new Node(k);
				return root;
			} 

			if (k < root->data) {
				root->left  = addKeyHelper(k, root->left);
				root->left->parent = root;
			} else {
				root->right= addKeyHelper(k, root->right);
				root->right->parent = root;
			}
			return root;
		}

		void printKeys() {
			printKeysHelper(tree);
		}
		
		bool isRightChild(Node *r) {
			return (r && r->parent && r->parent->right == r);
		}
		bool isLeftChild(Node *r) {
			return (r && r->parent && r->parent->left == r);
		}

		void printKeysHelper(Node *r) {
			if (!r) return;

			while (r->left) {
				r = r->left;
			}
			Node *t = r;
			do {
				r = t;
				printf("%d\t", r->data);
			} while (t = successor(r));
				
		}

		Node * min(Node* r) {
			if (!r ) return  NULL;
			while (r->left) r = r->left;
			return r;
		}

		Node* successor(Node* root) {
			if (!root) return NULL;
			
			//go down
			if (root->right) return min(root->right);

			//traverse up
			while (root && !isLeftChild(root)) {
				root = root->parent;
			}
			return root ? root->parent: root;
		}


};

int main() {
	InorderIterative sol;
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

	return 0;
}
