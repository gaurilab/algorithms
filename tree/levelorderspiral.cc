#include "BinaryTree.h"
#include <vector>
#include <deque>

using namespace std;


void levelorderspiral2(Node * root) {

	if (!root) return ;

	deque<Node*> q;
	q.push_back(root);

	int c = q.size();
	int level = 0;
	int turn =0;
	Node *n = NULL;
	while (!q.empty()) {
		if (turn) {
			n = q.back(); q.pop_back (); --c;
			if (n->right) q.push_front(n->right);
			if (n->left) q.push_front(n->left);

		} else {
			n = q.front(); q.pop_front(); --c;
			if (n->left) q.push_back(n->left);
			if (n->right) q.push_back(n->right);
		}

		if (c == 0)  {
			c = q.size();
			turn = 1 - turn;
		}
		printf("%d\t",n->data);

	}
	printf("\n");
}
void levelorderspiral(Node * root) {

	if (!root) return ;

	vector<Node* > s1 , s2;

	s1.push_back(root);
	Node *c = NULL;

	while (!s1.empty() || !s2.empty()) {
		while (!s1.empty()) {
		 c = s1.back(); s1.pop_back();
		 if (c->left) s2.push_back(c->left);
		 if (c->right) s2.push_back(c->right);
		 printf("%d\t",c->data);
		}
		while (!s2.empty()) {
		 c = s2.back(); s2.pop_back();
		 if (c->right) s1.push_back(c->right);
		 if (c->left) s1.push_back(c->left);
		 printf("%d\t",c->data);
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

	levelorderspiral(sol.tree);
	levelorderspiral2(sol.tree);
	return 0;
}
