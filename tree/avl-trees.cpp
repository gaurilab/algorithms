#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

struct node;

typedef struct node* nodeptr_t;

struct node
{
	nodeptr_t parent;	
	nodeptr_t left;	
	nodeptr_t right;	
	int key;
	node(int k=0):parent(NULL),left(NULL),right(NULL),key(k){}	
};

typedef struct node node_t;

nodeptr_t grandparent(nodeptr_t n)
{
	if ((n != NULL) && (n->parent != NULL))
		return n->parent->parent;
	else
		return NULL;
}
 
nodeptr_t uncle(nodeptr_t n)
{
	nodeptr_t g = grandparent(n);
	if (g == NULL)
		return NULL; // No grandparent means no uncle
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}
nodeptr_t findMin(nodeptr_t x)
{
    nodeptr_t min=NULL;
    if (x!=NULL)
    {
            while(x!=NULL)
            { 
                    min =x;
                    x=x->left;   
            }
    }
    return min;
}
nodeptr_t successor (nodeptr_t 
int height(nodeptr_t x)
{
	if(x == NULL)
		return 0;
	else
	{
	assert(x!=NULL);

	int left_height = height(x->left) ;

	int right_height = height(x->right) ;

	if(left_height<right_height )
		return (right_height +1);
	else
		return (left_height +1);
	}
 	
}
void printGivenLevel(struct node* root, int level, int ltr);

void printLevelOrder(struct node* root)
{
  int h = height(root);
  int i;

  /*ltr -> Left to Right. If this variable is set,
    then the given level is traverseed from left to right. */
  bool ltr = 0;
 printf("\n==================================================\n");	
  for(i=1; i<=h; i++)
  {
    printGivenLevel(root, i, ltr);
    printf("\n");	
  }
 printf("\n==================================================\n");	
}    

/* Print nodes at a given level */
void printGivenLevel(struct node* root, int level, int ltr)
{
  if(root == NULL)
    return;
  if(level == 1)
    printf("%d ", root->key);
  else if (level > 1)
  {
      printGivenLevel(root->left, level-1, ltr);
      printGivenLevel(root->right, level-1, ltr);
  }
}



void left_rotation(nodeptr_t *root_ref,nodeptr_t x)
{
	assert(root_ref !=NULL);
	assert(x !=NULL);
	nodeptr_t right_subtree = x->right;	
	
	if(right_subtree == NULL )
	{
		printf("\n left rotation cannot be performed because the right child %d is NULL ",x->key);
		return;
	}

	nodeptr_t left_of_right_subtree=right_subtree->left;

	if(left_of_right_subtree != NULL )
	{
		printf("\n left rotation :setting parent of  %d to %d\n ",left_of_right_subtree->key,x->key);
		left_of_right_subtree->parent = x ;  
	}
	
	printf("\n left rotation :setting right child of %d to left of  %d\n ",x->key,right_subtree->key);
	x->right=left_of_right_subtree;

	printf("\n left rotation :setting  %d parent to  %d parent\n ",right_subtree->key,x->key);
	right_subtree->parent= x->parent;

	if(x->parent == NULL)
	{
		//x is the root node
		*root_ref=right_subtree;
	}
	else if (x->parent->left == x )
	{
		//left subtree
	printf("\n left rotation :setting  %d to  %d  left child \n ",right_subtree->key,x->parent->key);
		x->parent->left=right_subtree;	
	}
	else
	{
	printf("\n left rotation :setting  %d to  %d  right child \n ",right_subtree->key,x->parent->key);
		x->parent->right=right_subtree;
	}

	printf("\n left rotation :setting  %d left to  %d  right child \n ",right_subtree->key,x->key);
	right_subtree->left=x;

	printf("\n left rotation :setting  %d parent to  %d \n ",x->key,right_subtree->key);
	x->parent = right_subtree;
	return;

	
}

void right_rotation(nodeptr_t * root_ref,nodeptr_t x)
{

	assert(root_ref !=NULL);
	assert(x !=NULL);
	nodeptr_t left_subtree = x->left;	
	
	if(left_subtree == NULL )
	{
		printf("\n right  rotation cannot be performed because the right child of %d is NULL ",x->key);
		return;
	}

	nodeptr_t right_of_left_subtree=left_subtree->right;

	if(right_of_left_subtree != NULL )
	{
		 printf("\n right  rotation: setting the %d parent to %d is NULL ",right_of_left_subtree->key,x->key);
		right_of_left_subtree->parent = x ;  
	}
	printf("\n right rotation :setting left child of  %d to  %d\n ",x->key,left_subtree->key);
	x->left=right_of_left_subtree;
	
	printf("\n right rotation :setting parent of  %d to %d parents \n",left_subtree->key,x->key);
	left_subtree->parent= x->parent;

	if(x->parent == NULL)
	{
		//x is the root node
		*root_ref=left_subtree;
	}
	else if (x->parent->left == x )
	{
		//left subtree
		//setting the parent of x right child to the left subtree
		printf("\n right rotation :setting the  %d to the left of %d  \n",left_subtree->key,  x->parent->key);
		x->parent->left=left_subtree;	
	}
	else
	{
		//setting the parent of x right child to the right subtree
		printf("\n right rotation :setting the  %d to the right of %d  \n",left_subtree->key,  x->parent->key);
		x->parent->right=left_subtree;
	}
	printf("\n right rotation :setting the %d to the right of %d\n",x->key, left_subtree->key);
	left_subtree->right=x;
	 printf("\n right rotation :setting the %d  parent to %d \n", x->key,left_subtree->key);
	x->parent = left_subtree;
	return;
}

int height_difference(nodeptr_t x)
{
	if(x == NULL)
		return 0;
	int left_subtree_height=height(x->left);
	int right_subtree_height=height(x->right);
	return(left_subtree_height -right_subtree_height );
}

void avl_insert_fixup ( nodeptr_t *root_ref , nodeptr_t x )
{

	assert(root_ref !=NULL);
	nodeptr_t z= NULL;
	nodeptr_t y=NULL;
	while( x != NULL )
	{	
		//traverse up the path until you find the node with unbalanced height
		if( abs(height_difference(x))>= 2 )
		{
			//multiple cases 		
			if(y==x->left && z==y->left)
			{
				right_rotation(root_ref , x);
				break;
			}	
			else if(y==x->right && z==y->right)
			{
				left_rotation(root_ref,x);
				break;
			}
			else if ( y==x->right  && z==y->left)
			{
				right_rotation(root_ref,y);
				left_rotation(root_ref,x);
				break;	  
			}
			else if (y==x->left && z==y->right )
			{
				left_rotation(root_ref,y );
				right_rotation(root_ref,x );
				break;	
			}
		}
		else
		{
			//move up in the node
			z=y;
			y=x;
			x=x->parent;

		}

	}	
}
void insert( nodeptr_t *root_ref , int key )
{
	nodeptr_t root=(root_ref)?*root_ref:NULL;	
	nodeptr_t curr;
	nodeptr_t prev;
	
	nodeptr_t tmp = new node_t(key);
	if(root == NULL)
	{
		*root_ref=tmp;	
		return;
	}
	else
	{
		curr = root;	
		while(curr != NULL)
		{
			if(key  <=  curr->key )
			{
				prev =curr;
				curr = curr->left;
			}
			else
			{	
				prev =curr;
				curr = curr->right;
			}
		}

		tmp->parent=prev;
		if( key <= prev->key )
		{
			prev->left=tmp;
		}	
		else
		{
			prev->right= tmp;
		}
	}
		printLevelOrder(*root_ref);
	avl_insert_fixup(root_ref,tmp);
}
#if 1
void delete(nodeptr_t *root_ref , int key)
{
    assert(root_ref !=  NULL)
	nodeptr_t x=*root_ref;
    nodeptr_t y ;
    while(x!=NULL)
    {
            if (x->key == key )
                    break;
            else if (key <= x->key )
            { x=x->left;
            }
            else
            {
                    x=x->right;
            }
            if(x == NULL )
                    return;

            if ((x->left == NULL) ||(x->right == NULL) )
            {
                y=x;
            }
            else
            {   
                y=successor(x);
            }

    }

    
}
#endif
const int MAX_NUL_OF_KEY=313;
const int MAX_VALUE_OF_KEY=137;

int main()
{
	nodeptr_t avl_tree=NULL;
	srand(time(NULL));
	const int size= rand()%MAX_NUL_OF_KEY;
	
	printf("The number of nodes is - %d", size);
	for(int i=1;i<size ;++i)
	{
		int key=rand()%MAX_VALUE_OF_KEY;        
		printf(" key to insert[%d] =%d\n",i,key);
		insert(&avl_tree,key);
		printLevelOrder(avl_tree);
	}
}


