#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

class Node {
    public:
    Node ():key(0),height(1), left(0), right(0) {}
    Node (int v):key(v),height(1), left(0), right(0) {}
    int key;
    Node *left,*right;
    int height;

};

struct AvlTree {
    public:
    AvlTree():ROOT(0) { }
    int getb(Node* n){
        int lh = n->left ? n->left->height:0;
        int rh = n->right ? n->right->height:0;
        return lh - rh;
    }
    AvlTree(const char *file):ROOT(0) {}
     Node *lrotate(Node* gp) {
        Node *p = gp->right;
        Node *t = p->left;
        p->left = gp;
        gp->right = t;

        gp->height = 1 + std::max(gp->left?gp->left->height:0,gp->right ? gp->right->height:0);
        p->height = 1 + std::max(p->left?p->left->height:0,p->right ? p->right->height:0);
        return p;
    }
    Node *rrotate(Node* gp) {
        Node *p = gp->left;
        Node *t = p->right;
        p->right = gp;
        gp->left = t;

        gp->height = 1 + std::max(gp->left?gp->left->height:0,gp->right ? gp->right->height:0);
        p->height = 1 + std::max(p->left?p->left->height:0,p->right ? p->right->height:0);
        return p;
    }

    Node* insert(Node *node, int key) {
        if (!node) {
            Node *n = new Node(key);
            return n;
        }
        if (key <= node->key) {
            node->left = insert(node->left, key);
            node->height = 1 + std::max(node->left->height, node->right ? node->right->height:0);
        }
        else {
            node->right = insert(node->right , key);
            node->height = 1 +  std::max(node->left?node->left->height:0,
                    node->right ? node->right->height:0);
        }

        int b = getb(node);
        printf("b:%d\n",b);
        if (b > 1) {
            if (key < node->left->key) {
                //ll
                node = rrotate(node);
            } else {
                //lr
                node->left = lrotate(node->left);
                node = rrotate(node);
            }
        } else if (b < -1) {
            if (key <= node->right->key) {
                //rl
                node->right = rrotate(node->right);
                node = lrotate(node);
            } else {
                //rr
                node = lrotate(node);
            }
        }
        return node;
    }

    void insert(int key) {
        ROOT = insert(ROOT, key);
    }
    
    void print(Node* node) {
        if (!node) return;
        printf("%4.2d(%2d): ",node->key,node->height);
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
        }
        else if (key > n->key) {
            n->right = remove(n->right, key);
        } else  { 

            if (!n->right && !n->left) {
                delete(n);
                n = NULL;
            } else if (!n->left && n->right) {
                Node *x = n;
                n = n->right;
                delete (x);
            } else if (n->left && !n->right) {
                Node *x = n;
                n = n->left;
                delete (x);
            } else {
                Node *x = n->right;
                Node *p = n;
                for (; x->left;p = x ,x=x->left);
                int t = x->key;
                x->key = n->key;
                n->key =t;
                x = remove(x,key);
                p->right == x ? p->right = x->right : p->left = x->right;
            }
        }
        if (!n) return n;

        n->height =  1 + std::max(n->left?n->left->height:0,n->right ? n->right->height:0);

        int b = getb(n);

        printf("b:%d\n",b);
        if (b > 1) {
            Node *z = n->left;
            int lb = z->left?z->left->height:0 - (z->right? z->right->height:0);
            if (lb >= 0) {
                //ll
                n = rrotate(n);
            } else {
                //lr
                n->left = lrotate(n->left);
                n = rrotate(n);
            }
        } else if (b < -1) {
            Node *z = n->right;
            int rb = z->left?z->left->height:0 - (z->right? z->right->height:0);
            if (rb > 0) {
                //rl
                n->right = rrotate(n->right);
                n = lrotate(n);

            } else {
                //rr
                n = lrotate(n);
            }
        }

        return n;
    }

    private:
    Node *ROOT;


};

int main() {

    AvlTree bst;
    int t;
    cin>>t;
    while (t--) {
        int i;
        cin>>i;
        bst.insert(i);
        bst.print();
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
