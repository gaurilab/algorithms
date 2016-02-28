#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Node {
    public:
    Node ():key(0), left(0), right(0) {}
    Node (int v):key(v), left(0), right(0) {}
    int key;
    Node *left,*right;

};

struct BinarySearchTree {
    public:
    BinarySearchTree():ROOT(0) { }

    BinarySearchTree(const char *file):ROOT(0) {}

    Node* insert(Node *node, int key) {
        if (!node) {
            Node *n = new Node(key);
            return n;
        }
        if (key <= node->key) {
            node->left = insert(node->left, key);
        }
        else {
            node->right = insert(node->right , key);
        }
        return node;
    }

    void insert(int key) {
        ROOT = insert(ROOT, key);
    }
    
    void print(Node* node) {
        if (!node) return;
        printf("%4.2d: ",node->key);
        printf("%4.2d ",node->left ? node->left->key:-1);
        printf("%4.2d ",node->right ? node->right->key:-1);
        printf("\n");
        print(node->left);        
        print(node->right);        
    }

    void print() {
        print(ROOT);
    }
    
    Node* min(Node *node) {
        Node *p = node;
        for (; node;p = node ,node=node->left);
        return p;
    }

    Node* max(Node *node) {
        Node *p = node;
        for (; node;p = node ,node=node->right);
        return p;
    }


    Node *sucessor(Node *node) {
        if (!node) return NULL;
        if (node->right) return min(node->right);
        Node *result = NULL;
        Node *c = ROOT;
        while(c) {
            if ( node->key <= c->key) {
                result = c;
                c = c->left;
            } else {
                c = c->right;
            }
        }
      return result;  
    }

    Node *predecessor(Node *node) {
        if (!node) return NULL;
        if (node->left) return max(node->left);
        Node *result = NULL;
        Node *c = ROOT;
        while(c) {
            if ( node->key <= c->key) {
                result = c;
                c = c->right;
            } else {
                c = c->left;
            }
        }
      return result;  
    }

    Node *find(Node *n, int key) {
        if (!n || key == n->key) {
            return n;
        }
        if (key < n->key) { return find(n->left, key); }
        else {return find (n->right, key);}
        return NULL;
    }
       
    Node *find(int key){
       return find(ROOT, key);
    }
    void remove(int key) {
        ROOT = remove(ROOT, key);
    }

    Node*  remove(Node *n, int key) {
        if (!n) return NULL;
        if (key < n->key) {
            n->left = remove(n->left, key);
            return n;
        }
        else if (key > n->key) {
            n->right = remove(n->right, key);
            return n;
        } else  { 

            if (!n->right && !n->left) {
                delete(n);
                return NULL;
            } else if (!n->left && n->right) {
                Node *x = n;
                n = n->right;
                delete (x);
                return n;
            } else if (n->left && !n->right) {
                Node *x = n;
                n = n->left;
                delete (x);
                return n;
            }

            Node *x = n->right;
            Node *p = n;
            for (; x->left;p = x ,x=x->left);
            int t = x->key;
            p->right == x ? p->right = x->right : p->left = x->right;
            delete(x);
            n->key =t;
            return n;
        }
    }

    private:
    Node *ROOT;


};

int main() {

    BinarySearchTree bst;
    int t;
    cin>>t;
    while (t--) {
        int i;
        cin>>i;
        bst.insert(i);
    }
    bst.print();
    cin>>t;
    while (t--) {
        int i;
        cin>>i;
        bst.remove(i);
        bst.print();
    }
    return 0;
}
