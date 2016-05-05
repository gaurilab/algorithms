#include "BinaryTree.h"
#include <vector>
#include <sstream>
using namespace std;

bool hasPathSum(Node *root, int sum, vector<Node*> &path) {
	if (!root) {
		return false;
	}
	if (isLeaf(root) && sum == root->data) {
		path.push_back(root);
		return true;
	}
	bool r = hasPathSum(root->right, sum- root->data, path);
	if (r ) {
		path.push_back(root);
		return true;
	}
	bool l  = hasPathSum(root->left, sum - root->data,path);
	if (l ) {
		path.push_back(root);
		return true;
	}
	
}

const char *toString(vector<Node*> path) {

	ostringstream oss;
	int k =  path.size() -1;
	for (; k > 0 ; --k) {
		oss<<path[k]->data<<"->";
	}
	if (k == 0) oss<<path[k]->data;

	return oss.str().c_str();

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
	vector<Node*> path;
	for (int  k = 15 ; k < 80; ++k) {
		path.clear();
		printf("sum %d : %s path:%s\n",k,	hasPathSum(sol.tree, k,path)?"true ":"false", toString(path));
		printf(" path:%s\n", toString(path));
	}
	printf("\n");

	return 0;
}
