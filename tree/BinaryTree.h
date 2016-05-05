#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include <iostream>
#include <cstdio>

class Node {
	public:
		Node(int k=0) : data (k) , left(0), right(0) ,parent(0) {}
		int data;
		Node *left, *right, *parent;
};

static bool isRightChild(Node *r) {
	return (r && r->parent && r->parent->right == r);
}
static bool isLeftChild(Node *r) {
	return (r && r->parent && r->parent->left == r);
}
static bool isLeaf(Node *t) {
	return (t && t->right == NULL && t->left ==NULL);
}

class BinaryTree{
	public:
		Node *tree;
		BinaryTree():tree(0){}

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

		bool addKeyIterativeHelper(int key , Node **rootRef) {
			if (!rootRef) return false;
			Node *root = *rootRef;
			if (!root) {
				*rootRef = new Node(key);
				return true;
			} 
			Node *p = root;
			while (root != NULL) {
				p = root;
				if (root->data < key ) root = root->right;
				else root = root->left;
			}

			(key <= p->data ? p ->left : p->right) = new Node(key);
			return true;
		}


		void printKeys() {
			printKeysHelper(tree);
			printf("\n");
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

#endif 

