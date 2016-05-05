#include "BinaryTree.h"
#include <vector>
#include <queue>

using namespace std;

void stackInorder(Node *r) {
	if (!r ) return;
	
	vector<Node*> st;
	Node *n  = r;
	do {
		while (n) {
			st.push_back(n);
			n  = n->left;
		}

		n = st.back(); st.pop_back();

		printf("%d\t", n->data);
		n = n->right; 
	} while (!st.empty() || n);

	printf("\n");
}
void stackPreorder(Node *r) {
	if (!r ) return;
	
	vector<Node*> st;

	st.push_back(r);
	
	while (!st.empty()) {
		Node *n = st.back(); st.pop_back();
		printf("%d\t", n->data);
		if (n->right) {
			st.push_back(n->right);
		}
		if (n->left) {
			st.push_back(n->left);
		}
	}

	printf("\n");
}
void twostackPostorder(Node *r) {
	if (!r ) return;
	vector<Node*> st1, st2;

	st1.push_back(r);
	while (!st1.empty()) {
		Node *n = st1.back();st1.pop_back(); st2.push_back(n);
		if (n->left) {
			st1.push_back(n->left);
		}
		if (n->right) {
			st1.push_back(n->right);
		}
	}

	while (!st2.empty()) {
		Node *p = st2.back(); st2.pop_back();
		printf("%d\t", p->data);
	}
	printf("\n");
}

void levelOrder(Node *r) {
	if (!r) return;
	deque<Node*> q;
	q.push_back(r);
	int c = 1;
	while (!q.empty()) {
		Node *n = q.front(); q.pop_front(); c--;
		printf("%d\t", n->data);
		if (n->left) {
			q.push_back(n->left);
		}
		if (n->right) {
			q.push_back(n->right);
		}
	
		if (c == 0) {
			printf("\n");
			c = q.size();
		}
	}
		 
}

void levelOrder(Node *r) {
	if (!r) return;
	deque<Node*> q;
	q.push_back(r);
	int c = 1;
	while (!q.empty()) {
		Node *n = q.front(); q.pop_front(); c--;
		printf("%d\t", n->data);
		if (n->left) {
			q.push_back(n->left);
		}
		if (n->right) {
			q.push_back(n->right);
		}
	
		if (c == 0) {
			printf("\n");
			c = q.size();
		}
	}
		 
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
	stackInorder(sol.tree);
	twostackPostorder(sol.tree);
	stackPreorder(sol.tree);
	levelOrder(sol.tree);
	return 0;
}
