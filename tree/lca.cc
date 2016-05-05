
#include <iostream>
#include <cstdio>

class Node {
	public:
		Node(int k=0) : data (k) , left(0), right(0) {}
		int data;
		Node *left, *right;
};


class Lca {
	private :
		Node *tree;

	public:
		Lca():tree(0){}

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
			} else {
				root->right= addKeyHelper(k, root->right);
			}
			return root;
		}

		void printKeys() {
			printKeysHelper(tree);
		}

		void printKeysHelper(Node *root) {
			if (!root) return;
			printKeysHelper(root->left);
			printf("%d\t", root->data);
			printKeysHelper(root->right);
		}

		Node* find(Node* root, int k) {
			if (!root) return NULL;

			if (root->data == k) return root;
			Node *l = find(root->left , k);
			if (l) return l;
			Node *r = find(root->right, k);
			return r;
		}

		Node* lcaUtil(Node* root, int k1, int k2, bool &f1, bool &f2) {

			if (!root || (f1 && f2) ) return NULL;

			int b1 = root->data  ==  k1;
			int b2 = root->data  ==  k2;
			Node *t = NULL;
			if (b1 || b2) {
				if (!f1 &&  b1) {
					t =	find(root, k2);
				} else if (!f2 && b2) {
					t =	find(root, k1) ;
				}
					f1 = f1 || b1;
					f2 = f2 || b2;
				if (t) {
					f1 = f1 || t->data == k1;
					f2 = f2 || t->data == k2; 
				}	
				return root;
			}
			// did not find anything
			Node *l = NULL , *r =NULL;
			if (root->left ) {
				l = lcaUtil(root->left, k1 , k2 , f1 , f2);
			} 

			if (root->right && (!f1 || !f2)) {
				r = lcaUtil(root->right , k1 , k2 , f1 , f2);
			}
			if (l && r) return root;
			if (l) return l;
			return r;
		}

		Node* findLca(int k1, int k2) { 
			bool f1 = false;
			bool f2 = false;
			Node *r = lcaUtil(tree , k1 ,k2 ,f1, f2);

			if (f1 && f2 ) return r;
			return NULL;

		}

};

int main() {
	Lca sol;
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
	do {
		printf("\n Give two keys\n");
		int a, b;
		scanf("%d %d",&a, &b);
		Node* x = sol.findLca(a,b);

		printf("%d\n",x ? x->data:-1);
	} while(getchar() != EOF);
	return 0;
}
