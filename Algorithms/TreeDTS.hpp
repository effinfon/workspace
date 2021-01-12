#ifndef TREEDTS_HPP_INCLUDED
#define TREEDTS_HPP_INCLUDED

/* namespace TreeDTS_v3 {

void BST::insert(int key)
{
  if (root != NULL) {
    insert(root, key);
  } else {
    root = new node;
    root->data = key;
    root->left = NULL;
    root->right = NULL;
  }
}

void BST::insert(node* leaf, int key)
{
  if (key < leaf->data){
    if (leaf->left != NULL) {
      insert(leaf->left, key);
    } else {
      leaf->left = new node;
      leaf->left->data = key;
      leaf->left->left = NULL;
      leaf->left->right = NULL;
    }
  } else {
    if (leaf->right != NULL) {
      insert(leaf->right, key);
    } else {
      leaf->right = new node;
      leaf->right->data = key;
      leaf->right->left = NULL;
      leaf->right->right = NULL;
    }
  }
}

node* BST::find(int key)
{
  // start from the root
  return find(root, key);
}

node* BST::find(node* leaf, int key)
{
  if (leaf == NULL) {
    return NULL;
  } else if (key == leaf->data) {
      return leaf;
  } else if (key < leaf->data){
    return find(leaf->left, key);
  } else return find(leaf->right, key);
}

node* BST::remove(int key)
{
  return remove(root, key);
}

node* BST::remove(node* t, int key)
{
  node* temp;

  // base case with empty node
  if (t == NULL)
    return NULL;

  if (key < t->data) {
    t->left = remove(t->left, key); // look in left subtree
  } else if (key > t->data) {
    t->right = remove(t->right, key); // look in right subtree
  }
  else {
  // key has been found.
  if (isLeafNode(t)){
    delete t;
    t = NULL;
  } else if (t->right && t->left) {
    // removing a node with two childen is tricky.
    // first we find the minimum leaf on the right side of the node we're deleting.
    // copy the data from the mimimum node to the node we're deleting.
    // finally delete the minimum node in the right subtree.
    node* temp = findMin(t->right);
    t->data = temp->data;
    t->right = remove(t->right, t->data);
  } else {
    temp = t;
    if (t->right == NULL)
      t = t->left;
    else if (t->left == NULL)
      t = t->right;
      delete temp;
    }
  }
  // eventually returns root node after node removal completes
  return t;
}

bool BST::isLeafNode(node* t)
{
  if (t != NULL && t->left == NULL && t->right == NULL)
    return true;
  else return false;
}

// find minimum
node* BST::findMin(node* t)
{
  if (t == NULL)
    return t;
  else if (t->left == NULL)
    return t;
  else return findMin(t->left);
}

node* BST::findMax(node* t)
{
  if (t == NULL)
    return t;
  else if (t->right == NULL)
    return t;
  else return findMax(t->right);
}

void BST::destroyTree()
{
  destroyTree(root);
}

void BST::destroyTree(node* leaf)
{
  if (leaf != NULL) {
    destroyTree(leaf->left);
    destroyTree(leaf->right);
  }

  delete leaf;
}

void BST::inOrder(node* t)
{
  if (t != NULL) {
    inOrder(t->left);
    cout << t->data <<" ";
    inOrder(t->right);
  }
}

void BST::preOrder(node* t)
{
  if (t != NULL) {
    cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
  }
}

void BST::postOrder(node* t)
{
  if (t != NULL) {
    postOrder(t->left);
    postOrder(t->right);
    cout << t->data << " ";
  }
}
void BST::display()
{
  cout<<"preOrder: ";
  preOrder(root);
  cout<<"\ninOrder: ";
  inOrder(root);
  cout<<"\npostOrder: ";
  postOrder(root);
  cout<<"\nlevelOrder: ";
  levelOrder(root);
}

// time complexity is always O(n). aaverage space complexity is O(n) for worst case. O(1) for best case
void BST::levelOrder(node* t)
{
  if (t != NULL) {
    queue<node*>q;

    // enque root node
    q.push(t);

    // deque root node, enque left and right children. exit loop when queue is empty.
    while(!q.empty()) {
      node* current = q.front();
      cout<<current->data<<" ";
      if (current->left)
        q.push(current->left);
      if (current->right)
        q.push(current->right);
      q.pop(); //remove the element at the front
    }
  }
}

// returns the max root-to-leaf depth of the tree.
// O(n)
int maxDepth(node* t)
{
  if (t == NULL) {
    return 0;
  } else {
    int ld = maxDepth(t->left);
    int rd = maxDepth(t->right);

    return (max(ld, rd) + 1);
  }
}

node* BST::getRoot()
{
  return root;
}

int main() {

  BST* tree = new BST();
  tree->insert(50);
  tree->insert(19);
  tree->insert(28);
  tree->insert(40);
  tree->insert(16);
  tree->insert(70);
  tree->insert(55);
  tree->insert(56);
  tree->insert(17);
  tree->insert(90);
  tree->display();
  cout<<"\n"<<maxDepth(tree->getRoot());

  delete tree;
  return 0;
}
};
*/

/* namespace TreeDTS_v4 {

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

struct Node {
	unsigned long long int value;
	Node *left;
	Node *right;
};

Node* add_node(unsigned long long int value) {
	Node *new_node = new Node;
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

// construct a bst using a pre-order traversal (T(N) = O(N))
Node* create_bst(unsigned long long int preorder[], unsigned long long int *index, unsigned long long int pivot, unsigned long long int min, unsigned long long int max, unsigned long long int size) {
	if (*index >= size) {
		return NULL;
	}
	Node *root = NULL;
	if (min <= pivot && max >= pivot) {
		root = add_node(pivot);
		*index = *index + 1;
		if (*index <= size) {
			root->left = create_bst(preorder, index, preorder[*index], min, pivot, size);
			root->right = create_bst(preorder, index, preorder[*index], pivot, max, size);
		}
	}
	return root;
}

// perform a preorder traversal
void print_preorder(Node *root) {
	if (root == NULL) {
		return;
	}
	cout << root->value << " ";
	print_preorder(root->left);
	print_preorder(root->right);
}

// perform an inorder traversal
void print_inorder(Node *root) {
	if (root == NULL) {
		return;
	}
	print_inorder(root->left);
	cout << root->value << " ";
	print_inorder(root->right);
}

// compute the sum of even levels
void compute_even_sum(Node *root, unsigned long long int *sum, unsigned long long int level) {
	if (root == NULL) {
		return;
	}
	compute_even_sum(root->left, sum, level + 1);
	compute_even_sum(root->right, sum, level + 1);
	if (level % 2 == 0) {
		*sum = *sum + root->value;
	}
}

int main() {
	unsigned long long int n, i, min, max;
	cin >> n;
	unsigned long long int *preorder = new unsigned long long int[n];

	Node *root;
	cin >> preorder[0];
	min = preorder[0];
	max = min;

	for (i = 1; i < n; i++) {
		cin >> preorder[i];
		if (preorder[i] < min) {
			min = preorder[i];
		}
		if (preorder[i] > max) {
			max = preorder[i];
		}
	}

	// build bst given preorder traversal
	unsigned long long int index = 0;
	root = create_bst(preorder, &index, preorder[0], min, max, n);
	unsigned long long int sum = 0;
	compute_even_sum(root, &sum, 0);
	cout << sum << "\n";
	return 0;
}
};
*/

namespace TreeDTS_v5 {

using namespace std;
struct Node
{
    int value;

    Node *right;
    Node *left;

    Node(int value)
    {
        this->value = value;
        this->right = NULL;
        this->left = NULL;
    }
};


class BST
{
    private:
        // Root node
        Node *root;

        // Insert private operation
        void insert(Node *root, int value);

        // Remove private operation
        bool remove(Node *parent, Node *current, int value);

        // Find next larger node for deletion
        Node* nextLarger(Node *node);
        // Find node with the given value
        Node* findNodeWithValue(int value);

        // Printing
        void print(Node *node);

    public:
        void insert(int value);
        bool remove(int value);

        // Find node with minimum value
        Node* findMin();
        // Find node with maximum value
        Node* findMax();
        // Return root node
        Node* getRoot();

        void printTree();
};

Node* BST::findNodeWithValue(int value)
{
    // Save the current node, starting with root
    Node *current = root;

    // Loop for left/right node while current node is not NULL
    while (current)
    {
        if (current->value == value)
            break;

        if (value > current->value)
            current = current->right;
        else
            current = current->left;

    }
    return current;
}

Node* BST::nextLarger(Node *node)
{
    // Start with the right node
    Node *nextLarger = node->right;

    // Get left node while it's not null
    while (nextLarger->left)
    {
        nextLarger = nextLarger->left;
    }

    return nextLarger;
}
void BST::insert(Node *root, int value)
{

    if (value > root->value)
    {
        // Higher value than root
        if (!root->right)
            // Insert on the right of the root
            root->right = new Node(value);
        else
            // Go deeper
            insert(root->right, value);
    }
    else
    {
        // Lower value than root

        if (!root->left)
            // Insert on the left of the root
            root->left = new Node(value);
        else
            // Go deeper
            insert(root->left, value);
    }
}
void BST::insert(int value)
{

    // If tree is empty, new node becomes root
    if (!root){
        root = new Node(value);
    }
    else
    {
        this->insert(root, value);
    }

}

bool BST::remove(Node *parent, Node *current, int value)
{
    if (!current)
    {
        // Did not find any node with the given value
        return false;
    }
    // Right node to remove
    if (current->value == value)
    {
        // Check if node is leaf
        if (!current->left && !current->right)
        {
            // Found node and is leaf
            // Remove and return
            if (parent->right == current)
                parent->right = NULL;
            else
                parent->left = NULL;
            delete current;
            current = NULL;
            return true;
        }
        // Check if node to delete has one child
        else if (!current->left || !current->right)
        {
            // Get the only child
            Node *child = current->left;
            if (!child)
                child = current->right;


            // If deleting root node, child becomes root
            if (!parent)
            {
                this->root = child;
            }
            else
            {
                // Parent now points to current's child
                if (child->value > parent->value)
                    parent->right = child;
                else
                    parent->left = child;
            }
            delete current;
            current = NULL;
        }

        // Current has two children
        else
        {
            //TODO
            // Get the next larger node from current
            Node *nextLargerNode = nextLarger(current);
            // Set next larger node's value into current node
            current->value = nextLargerNode->value;
            // Remove next larger node, which is a leaf
            delete nextLargerNode;
            nextLargerNode = NULL;
        }
        return true;
    }

    // Not the right node to remove
    if (value > current->value){
        return remove(current, current->right, value);
    }else {
        return remove(current, current->left, value);
    }
}

void BST::print(Node *root)
{
    if (!root)
        return;
    print(root->left);
    cout<<root->value<<' ';
    print(root->right);
}

void BST::printTree()
{
    if(!root)
        return;
    print(root);
    cout << endl;
}

Node* BST::findMax()
{
    Node *max = root;

    while (max->right)
    {
        max = max->right;
    }

    return max;
}

Node* BST::findMin()
{
    Node *min = root;

    while (min->left)
    {
        min = min->left;
    }

    return min;
}

bool BST::remove(int value)
{
    return remove(NULL, root, value);
}

int main() {
    // Start tree
    BST *bst = new BST();

    // Add nodes
    bst->insert(10);
    bst->insert(20);
    bst->insert(25);
    bst->insert(8);
    bst->insert(9);
    bst->insert(2);
    bst->insert(4);
    bst->insert(1);
    bst->insert(3);

    // Print sorted tree
    bst->printTree();
    cout << endl;

    // Find max
    Node *max = bst->findMax();
    cout << "Max node: " << max->value << endl;

    // Find min
    Node *min = bst->findMin();
    cout << "Min node: " << min->value << endl;

    cout << endl;


    cout << "Removing: 9" << endl;
    // Remove leaf
    bst->remove(9);
    bst->printTree();

    cout << "Removing: 4" << endl;
    // Remove node with 1 child
    bst->remove(4);
    bst->printTree();

    cout << "Removing: 8" << endl;
    // Remove node with 2 children
    bst->remove(8);
    bst->printTree();
}
};

namespace TreeDTS_v6 {


//C++ Program to create a Complete Binary Tree.
//-Ajinkya Sonawane [AJ-CODE-7]
//
//In a complete binary tree every level, except possibly the last, is completely filled,
//and all nodes in the last level are as far left as possible.
//It can have between 1 and 2h nodes at the last level h.
//An alternative definition is a perfect tree whose rightmost leaves (perhaps all) have been removed.
//Some authors use the term complete to refer instead to a perfect binary tree as defined above,
//in which case they call this type of tree an almost complete binary tree or nearly complete binary tree.


#include<iostream>
using namespace std;

class node
{
    int data;           //field to store the value of the element
    node *left,*right;  //link field to the child nodes
    friend class cbt;   //allowing class cbt to access private members of class node
};

class  cbt
{
    node *root,*temp;   //root - Root pointer to the ROOT of the Tree, temp - Temporary node pointer  pointing to the node to be inserted
public:
        cbt();
        inline node* get_root(){return root;}          //getter method for accessing root

        void accept(int);              //method to accept values to be inserted
        node* insert(node*,node*);  //method to insert node in the binary tree
        void display(node*);        //method to display the tree in InOrder traversal

        int height(node*);          //method to get height of a given node
        int bal(node*);             /*method to get the balance factor of a given node
                                    [Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree] */
        bool check(node*);         //method to check any node with balance factor > 0
	~cbt();
};

cbt :: cbt()
{
    //initializing root node to NULL
    root = NULL;
    temp = NULL;
}

bool cbt :: check(node *r)
{
    //traversing the nodes of the subtree to check any node with balance factor > 0
    if(r == NULL)
        return false;
    bool x = check(r->left);
        if(bal(r))
            return true;
    bool y = check(r->right);

    return x||y;    //If any node present with balance factor > 0
}

void cbt :: accept(int t)
{

    for(int i=0;i<t;i++)
    {
        //creating a node to be inserted
        temp = new node;
        temp->left = NULL;
        temp->right = NULL;

        cout<<"\nEnter the element : ";
        cin>>temp->data;

        //inserting the current node in the tree
        root = insert(root,temp);
    }
}

node* cbt :: insert(node* r,node* t)
{
    //Inserting a node in the tree
    if(r == NULL)
        return t;
    else if(bal(r)==0 && check(r->right))  //Condition to insert node in the right sub-tree
        r->right = insert(r->right,t);
    else if(bal(r)==0)                      //condition to insert node in the left sub-tree
        r->left = insert(r->left,t);
    else if(bal(r)==1 && check(r->left))   //condition to insert node in the left sub-tree
        r->left = insert(r->left,t);
    else if(bal(r)==1)
        r->right = insert(r->right,t);      //condition to insert node in right sub-tree

    return r;
}

void cbt :: display(node *r)
{
    //Traversing the tree in InOrder way using recursion
    if(r == NULL)
        return;
    display(r->left);
    cout<<r->data<<"\t";
    display(r->right);
}
int cbt :: height(node *r)
{
    if(r == NULL)
        return 0;
    else
    {
        int lheight = height(r->left)+1;
        int rheight = height(r->right)+1;

    return (lheight > rheight) ? lheight : rheight; //returns maximum height
    }
}

int cbt :: bal(node *r)
{
        if(r == NULL)
            return 0;
        int lheight = height(r->left)+1;
        int rheight = height(r->right)+1;

        return (lheight - rheight); //[Balance Factor = Height of Left Sub-Tree - Height of Right Sub-Tree]
}

cbt :: ~cbt()
{
	delete root;
	delete temp;
}
int main()
{
    cbt c;  //creating object of class cbt
    int ch,t;
    do
    {
        cout<<"\n\n\t| Complete Binary Tree |\n";
        cout<<"\n1.Create";
        cout<<"\n2.Insert";
        cout<<"\n3.Display";
        cout<<"\n4.Exit";
        cout<<"\n>>";
        cin>>ch;

        switch(ch)
        {
            case 1:
                cout<<"\nEnter the total number of elements : ";
                cin>>t;
                c.accept(t);
                break;
            case 2:
                c.accept(1);
                break;
            case 3:
                if(c.get_root() == NULL)
                {
                    cout<<"\n\t**** Tree doesn't exist *****\n";
                    break;
                }
                cout<<"\n\t| Tree Elements |\n\n";
                c.display(c.get_root());
                break;
            case 4:
                cout<<"\n\t**** EXIT ****\n";
                break;
            default:
                cout<<"\n\t**** Invalid Choice ****\n";
                break;
        }
    }while(ch != 4);
    return 0;
}
};

namespace TreeDTS_v7 {
#ifndef __BST__
#define __BST__

#include <iostream>
using namespace std;

template <class T>
struct Node{
	T data;
	Node<T>* left;
	Node<T>* right;
};

template <typename T>
class BST{
	protected:
		Node<T>	*root;

	public:
		BST();
		~BST();

		// Create New Node
		// Params: Node Value
		// Returns: Node
		Node<T>* getNewNode(T);

		// Insertion
		// Params: Root Node, Node Value
		// Returns: Root Node
		Node<T>* insertNode(Node<T>*, T);

		// Search
		// Params: Root Node, Node Value
		// Returns: True | False depending on Node found or not/
		bool searchNode(Node<T>*, T);

		// Find Minimum
		// Params: Root Node
		// Returns: Minimum Node (Left Most in a Binary Search Tree)
		Node<T>* findMin(Node<T>*);

		// Deletion
		// Params: Root Node, Node Value
		// Returns: Root Node
		Node<T>* deleteNode(Node<T>*, T);

		// Check if tree is symmetric or not
		// Params: Root Node
		// Overloaded Params: Left Subtree Root, Right Subtree Root
		// Returns: True | False
		bool isSymmetric(Node<T>*);

		bool isSymmetric(Node<T>*, Node<T>*);



		// Print
		// Params: Root Node
		// Returns: void | prints the Tree in preOrder fashion
		void print(Node<T>*);
};
#endif
#include <iostream>

using namespace std;

// Default Constructor
template <typename T>
BST<T>::BST(){
	root = NULL;
}

// Default Destructor
template <typename T>
BST<T>::~BST(){

}


// Init a new Node
template <typename T>
Node<T>* BST<T>::getNewNode(T v){
	Node<T>* temp = new Node<T>();
	temp->data = v;
	temp->left = temp->right = NULL;
	return temp;
}

// Insert a Node
template <typename T>
Node<T>* BST<T>::insertNode(Node<T>* root, T v){
	if(root == NULL){
		root = getNewNode(v);
	}else if(v <= root->data){
		root->left = insertNode(root->left, v);
	}else{
		root->right = insertNode(root->right, v);
	}
	return root;
}

// Search a Node
template <typename T>
bool BST<T>::searchNode(Node<T>* root, T v){
	if(root == NULL){
		return false;
	}else if(root->data == v){
		return true;
	}else if(v <= root->data){
		return searchNode(root->left, v);
	}else{
		return searchNode(root->right, v);
	}
}

// find Minium
template <typename T>
Node<T>* BST<T>::findMin(Node<T>* root){
	while(root->left != NULL) root = root->left;
	return root;
}

// Delete a Node
template <typename T>
Node<T>* BST<T>::deleteNode(Node<T>* root, T v){
	if(root == NULL) return root;
	else if(v < root->data) root->left = deleteNode(root->left, v);
	else if(v > root->data) root->right = deleteNode(root->right, v);
	else{
		if(root->left == NULL && root->right == NULL){
			delete root;
			root = NULL;
		}else if(root->left == NULL){
			Node<T>* temp = root;
			root = root->right;
			delete temp;
		}else if(root->right == NULL){
			Node<T>* temp = root;
			root = root->left;
			delete temp;
		}else{
			// Two Children

			Node<T>* temp = findMin(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right,temp->data);
		}
	}
	return root;
}

// Print the Tree - Pre Order Traversal
template <typename T>
void BST<T>::print(Node<T>* root){
		if(root == NULL) return;
		cout<<root->data<<" ";
		print(root->left);
		print(root->right);
}

//Check if tree is symmetric overloaded function
template <typename T>
bool BST<T>::isSymmetric(Node<T>* rootLeft, Node<T>* rootRight){
	if(rootLeft == NULL && rootRight == NULL)
		return true;
	if((rootLeft == NULL && rootRight != NULL) || (rootLeft != NULL && rootRight == NULL))
		return false;
	if(rootLeft->data != rootRight->data)
		return false;
	return isSymmetric(rootLeft->left, rootRight->right) && isSymmetric(rootLeft->right, rootRight->left);
}


//Check if tree is symmetric
template <typename T>
bool BST<T>::isSymmetric(Node<T>* root){
	if(root == NULL)
		return true;
	return isSymmetric(root->left, root->right);
}

#include <iostream>

using namespace std;

int main()
{
	BST<int> b;

	Node<int>* root = NULL;
	root = b.insertNode(root, 15);
	root = b.insertNode(root, 13);
	root = b.insertNode(root, 17);
	root = b.insertNode(root, 12);
	root = b.insertNode(root, 14);
	root = b.insertNode(root, 16);
	root = b.insertNode(root, 19);

	b.print(root);
	cout<<"\n";

	int number;
	cout<<"Enter a node to be searched\n";
	cin>>number;

	if(b.searchNode(root, number) == true) cout<<"Node Found exists in the Tree!\n";
	else cout<<"Node NOT Found!\n";

	int deleteNumber;
	cout<<"Enter a node to be deleted\n";
	cin>>deleteNumber;

	b.deleteNode(root, deleteNumber);
	b.print(root);
	cout<<"\n";

	if(b.isSymmetric(root) == true) cout<<"The tree is symmetric\n";
	else cout<<"The tree is not Symmetric\n";

	// A Binary Search Tree can never be symmetric
	// A Binary Tree can be symmetric

	return 0;
}
};

namespace TreeDTS_v8 {

#include <iostream>

template <class T>
class BinaryTree
{

	struct node{
		T value;
		struct node* right;
		struct node* left;
	};

public:
	BinaryTree();
	~BinaryTree();
	void add(T val);
	void printPreOrder();
	void printInOrder();
	void printPostOrder();
	int size();
	bool lookup(T val);

private:
	struct node* root;
	int treeSize;
	void add(struct node** node, T val);
	bool lookup(struct node* node, T val);
	void printPreOrder(struct node* node);
	void printInOrder(struct node* node);
	void printPostOrder(struct node* node);
	void deleteTree(struct node* node);
};

template <class T>
BinaryTree<T>::BinaryTree(){
	this->root = NULL;
	this->treeSize = 0;
}

template <class T>
BinaryTree<T>::~BinaryTree(){
	deleteTree(this->root);
}

template <class T>
int BinaryTree<T>::size(){
	return this->treeSize;
}

template <class T>
void BinaryTree<T>::add(T val){
	add(&(this->root), val);
}

template <class T>
void BinaryTree<T>::add(struct node** node, T val){

	if(*node == NULL)	{
		struct node* tmp = new struct node;
		tmp->value = val;
		tmp->left=NULL;
		tmp->right = NULL;
		*node = tmp;

		this->treeSize++;
	}else{
		if(val > (*node)->value){
			add(&(*node)->right, val);
		}else{
			add(&(*node)->left, val);
		}
	}
}

template <class T>
void BinaryTree<T>::printInOrder(){
	printInOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printInOrder(struct node* node){
	if(node != NULL){
		printInOrder(node->left);
		std::cout << node->value << ", ";
		printInOrder(node->right);
	}
}

template <class T>
void BinaryTree<T>::printPreOrder(){
	printPreOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPreOrder(struct node* node){
	if(node != NULL)	{
		std::cout << node->value << ", ";
		printInOrder(node->left);
		printInOrder(node->right);
	}
}

template <class T>
void BinaryTree<T>::printPostOrder(){
	printPostOrder(this->root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPostOrder(struct node* node){
	if(node != NULL){
		printInOrder(node->left);
		printInOrder(node->right);
		std::cout << node->value << ", ";
	}
}


template <class T>
void BinaryTree<T>::deleteTree(struct node* node){
	if(node != NULL){
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

template <class T>
bool BinaryTree<T>::lookup(T val){
	return lookup(this->root, val);
}

template <class T>
bool BinaryTree<T>::lookup(struct node* node, T val){
	if(node == NULL){
		return false;
	}else{
		if(val == node->value){
			return true;
		}

		if(val > node->value){
			return lookup(node->right, val);
		}else{
			return lookup(node->left, val);
		}
	}

}

int main(){

	BinaryTree<int> tree;

	tree.add(5);
	tree.add(4);
	tree.add(7);
	tree.add(10);
	tree.add(1);
	tree.add(2);

	tree.printPostOrder();
	tree.printInOrder();
	tree.printPreOrder();

	std::cout << "Tree size: " << tree.size() << std::endl;

	BinaryTree<char> tee;

	tee.add('z');
	tee.add('0');
	tee.add('9');
	tee.add('a');
	tee.add('A');
	tee.add('Z');

	std::cout << "Contains 9? : "<< ((tee.lookup('9'))? "true" : "false" ) << std::endl;

	tee.printPostOrder();
	tee.printInOrder();
	tee.printPreOrder();

	std::cout << "Tree size: " << tee.size() << std::endl;
}

};

/* namespace TreeDTS_v9 {
#include <string>

class Node {
 public:
  string data;
  int value;
  Node* lchild;
  Node* rchild;

  Node(string, int);
};

Node::Node(string data, int value) {
  this->data = data;
  this->value = value;
  this->rchild = NULL;
  this->lchild = NULL;
}

#include <vector>
#include <map>

class BST {
 public:
  Node* root;

  BST(Node*);
  BST(string, int);

  int insert(string, int);
  int insert(string, int, Node*);
  int depthOf(int);
  int depthOf(int, Node*);
  bool includes(int);
  bool includes(int, Node*);
  int max();
  Node* maxNode();
  int min();
  Node* minNode();
  vector<map<string, int>> sort();
  void sort(Node*);
  void load(string);

 private:
  vector<map<string, int>> sorted;
};

#include <stdexcept>
#include <fstream>
#include <sstream>


BST::BST(Node *node) {
  this->root = node;
}

BST::BST(string data, int value) {
  Node *node = new Node(data, value);
  this->root = node;
}

int BST::insert(string data, int value) {
  return insert(data, value, this->root);
}

int BST::insert(string data, int value, Node* currentNode) {
  if (currentNode->value < value) {
    if (currentNode->rchild == NULL) {
      Node *node = new Node(data, value);
      currentNode->rchild = node;
      return depthOf(value);
    } else {
      return insert(data, value, currentNode->rchild);
    }
  } else {
    if (currentNode->lchild == NULL) {
      Node *node = new Node(data, value);
      currentNode->lchild = node;
      return depthOf(value);
    } else {
      return insert(data, value, currentNode->lchild);
    }
  }
}

int BST::depthOf(int value) {
  return depthOf(value, this->root);
}

int BST::depthOf(int value, Node* currentNode) {
  if (currentNode->value == value) {
    return 1;
  } else {
    if (currentNode->value < value) {
      return 1 + depthOf(value, currentNode->rchild);
    } else {
      return 1 + depthOf(value, currentNode->lchild);
    }
  }
}

bool BST::includes(int value) {
  return includes(value, this->root);
}

bool BST::includes(int value, Node* currentNode) {
  if (currentNode->value == value) {
    return true;
  } else {
    if (currentNode->value < value) {
      return includes(value, currentNode->rchild);
    } else {
      return includes(value, currentNode->lchild);
    }
  }
}

Node* BST::maxNode() {
  Node* currentNode = this->root;
  while (currentNode->rchild != NULL) {
    currentNode = currentNode->rchild;
  }
  return currentNode;
}

int BST::max() {
  return maxNode()->value;
}

Node* BST::minNode() {
  Node* currentNode = this->root;
  while (currentNode->lchild != NULL) {
    currentNode = currentNode->lchild;
  }
  return currentNode;
}

int BST::min() {
  return minNode()->value;
}

vector<map<string, int>> BST::sort() {
  sort(this->root);
  return this->sorted;
}

void BST::sort(Node* currentNode) {
  if (currentNode->lchild != NULL) {
    sort(currentNode->lchild);
  }

  map<string, int> hash;
  hash[currentNode->data] = currentNode->value;
  this->sorted.push_back(hash);

  if (currentNode->rchild != NULL) {
    sort(currentNode->rchild);
  }
}

void BST::load(string filename) {
  vector<string> data;
  string line;
  ifstream file;
  file.open(filename);
  while (getline(file, line)) {
    data.push_back(line);
  }

  vector<map<string, int>> parsedLines;
  for (const string s : data) {

    string::size_type loc = s.find( ",", 0 );
    string value = s.substr(0, loc);
    int val = atoi(value.c_str());

    string data = s.substr(loc+1);
    map<string, int> hash;
    hash[data] = val;
    parsedLines.push_back(hash);
  }

  for (int i = 0; i < parsedLines.size(); i++) {
    for ( const auto &pair : parsedLines[i]){
      int value = pair.second;
      string data = pair.first;
      insert(data.erase(0,1), value);
    }
  }
}

int main() {
  BST bst = BST("root node", 50);

  cout << "root node data: " <<  bst.root->data << ", value: " <<  bst.root->value << endl;

  bst.insert("rchild 1", 55);
  bst.insert("lchild 1", 45);

  cout << "root->rchild data: " << bst.root->rchild->data
       << ", value: " << bst.root->rchild->value << endl;

  cout << "root->lchild data: " << bst.root->lchild->data
       << ", value: " << bst.root->lchild->value << endl;

  bst.insert("rchild 2", 52);
  bst.insert("lchild 2", 48);

  Node *rchildTwo = bst.root->rchild->lchild;
  cout << "root->rchild->lchild data: " << rchildTwo->data
       << ", value: " << rchildTwo->value << endl;

  Node *lchildTwo = bst.root->lchild->rchild;
  cout << "root->lchild->rchild data: " << lchildTwo->data
       << ", value: " << lchildTwo->value << endl;

  cout << "depth of root node is: " << bst.depthOf(50) << endl;
  cout << "depth of root->rchild is: " << bst.depthOf(55) << endl;
  cout << "depth of root->lchild is: " << bst.depthOf(45) << endl;

  cout << "depth of root->rchild->lchild is: " << bst.depthOf(52) << endl;
  cout << "depth of root->lchild->rchild is: " << bst.depthOf(48) << endl;

  bst.insert("rchild 3", 53);
  bst.insert("rchild 4", 54);

  cout << "depth of root->rchild->lchild->rchild is: " << bst.depthOf(53) << endl;
  cout << "depth of root->rchild->lchild->rchild->rchild is: " << bst.depthOf(54) << endl;

  if (bst.includes(50)) {
    cout << "bst includes a node with a value of 50" << endl;
  } else {
    cout << "something went wrong" << endl;
  }

  bst.insert("max node", 100);
  bst.insert("min node", 0);

  cout << "Max value in tree: " << bst.max() << endl;
  cout << "Min value in tree: " << bst.min() << endl;

  cout << "Value of max node in tree " << bst.maxNode()->value << endl;
  cout << "Value of min node in tree " << bst.minNode()->value << endl;

  BST newBST = BST("root node", 50);
  newBST.load("data.txt");

  cout << "\nCreate new tree, load from file, print sorted tree" << endl << endl;

  vector<map<string, int>> sortedTree = newBST.sort();
  for (int i = 0; i < sortedTree.size(); i++) {
    for ( const auto &myPair : sortedTree[i] ) {
      cout << "{ " << myPair.first << ", " << myPair.second << " }" << endl;
    }
  }

  return 0;
}

};
*/

/*namespace TreeDTS_v10 {
#include <iostream>
#include <new>
#include <cassert>

#define NUMBER 9

template <typename T> class Node {
public:

	Node<T> *parent, *left, *right;
	T data;

	Node() : parent(NULL), left(NULL), right(NULL) {
		parent = NULL;
		left = NULL;
		right = NULL;
	}

	Node(T data) : data(data),  parent(NULL), left(NULL), right(NULL) {
	}

	Node(T data, Node<T> *parent, Node<T> *left, Node<T> *right) :
		data(data), parent(parent), left(left), right(right) {

	}

 	static void walk(const Node<T> *tree);
 	static Node<T> *find(Node<T> *tree, T value);
 	static Node<T> *minimum(Node<T> *tree);
 	static Node<T> *maximum(Node<T> *tree);
 	static Node<T> *successor(Node<T> *tree);

	// Always returns the root of the tree, whether it had to be modified
	// or not
 	static Node<T> *insertNode(Node<T> *tree, Node<T> *node);
 	static Node<T> *deleteNode(Node<T> *tree, Node<T> *node);

private:
 	static Node<T> *transplant(Node<T> *tree, Node<T> *u, Node<T> *v);
};

template<typename T> std::ostream &operator<<(std::ostream &output, Node<T> node);

int main() {
	Node<int> list[NUMBER] = {
		45, 50, 1, 9, 44, 56, 98, 43, 32
	};

	// construct a tree
	Node<int> *root = NULL;

	// We will just use the first tree as the root
	for (int i = 0; i < NUMBER; ++i) {
		root = Node<int>::insertNode(root, (list + i));
	}

	Node<int>::walk(root);

	std::cout << *Node<int>::find(root, 43);
	std::cout << "Minimum: " << *Node<int>::minimum(root);
	std::cout << "Maximum: " << *Node<int>::maximum(root);

	Node<int> *nine = Node<int>::find(root, 9);
	std::cout << "9: " << *nine;
	std::cout << "Successor: " << *Node<int>::successor(nine);

	Node<int> *fortyFour = Node<int>::find(root, 44);
	std::cout << "44: " << *nine;
	std::cout << "Successor: " << *Node<int>::successor(fortyFour);

	root = Node<int>::deleteNode(root, root);
	Node<int>::walk(root);

	return 0;
}

template <typename T> void Node<T>::walk(const Node<T> *tree) {
	if (tree == NULL) return;

	walk(tree -> left);
	std::cout << tree -> data << "\n";
	walk(tree -> right);
}

template <typename T> Node<T> *Node<T>::insertNode(Node<T> *tree, Node<T> *node) {
	if (!tree) {
		tree = node;
		node -> parent = NULL;
	} else {
		Node<T> *parent, *search = tree;
		bool left = false;
		while (search != NULL) {
			parent = search;
			if (node -> data <= search -> data) {
				search = search -> left;
				left = true;
			} else {
				search = search -> right;
				left = false;
			}
		}
		node -> parent = parent;
		if (left) parent -> left = node;
		else parent -> right = node;
	}

	return tree;
}

template <typename T> Node<T> *Node<T>::find(Node<T> *tree, T value) {
	if (!tree || tree -> data == value) return tree;
	if (value < tree -> data) return find(tree -> left, value);
	else return find(tree -> right, value);
}

template <typename T> Node<T> *Node<T>::minimum(Node<T> *tree) {
	if (!tree) return NULL;

	while (tree -> left) {
		tree = tree -> left;
	}

	return tree;
}

template <typename T> Node<T> *Node<T>::maximum(Node<T> *tree) {
	if (!tree) return NULL;

	while (tree -> right) {
		tree = tree -> right;
	}

	return tree;
}

template <typename T> Node<T> *Node<T>::successor(Node<T> *node) {
	if (!node) return NULL;

	if (node -> right) {
		return minimum(node -> right);
	} else {
		// We need to traverse upwards in the tree to find a node where
		// the node is the left child of a parent
		// parent is the successor

		Node<T> *parent = node -> parent;
		while(parent && node != parent -> left) {
			node = parent;
			parent = node -> parent;
		}

		return parent;
	}

}

// make node U's paarent have node v has its child
template <typename T> Node<T> *Node<T>::transplant(Node<T> *tree, Node<T> *u, Node<T> *v) {
	if (!u -> parent) tree = v;
	else if (u -> parent -> left == u) {
		u -> left = v;
	} else if (u -> parent -> right == u) {
		u -> right = v;
	}
	if (v) v -> parent = u -> parent;
	return tree;
}

template <typename T> Node<T> *Node<T>::deleteNode(Node<T> *tree, Node<T> *node) {
	if (!node -> left) {
		tree = transplant(tree, node, node -> right);
	} else if (!node -> right) {
		tree = transplant(tree, node, node -> left);
	} else {
		// Has two children -- successor must be on the right
		Node <int> *successor = minimum(node -> right);
		assert(successor -> left == NULL);
		if (successor != node -> right) {
			tree = transplant(tree, successor, successor -> right);
			successor -> right = node -> right;
			successor -> right -> parent = successor;
		}

		tree = transplant(tree, node, successor);
		successor -> left = node -> left;
		successor -> left -> parent = successor;
	}
	return tree;
}

template<typename T> std::ostream &operator<<(std::ostream &output, Node<T> node) {
	output << "Value: " << node.data;
	if (node.parent) output << " Parent: " << node.parent -> data;
	if (node.left) output << " Left: " << node.left -> data;
	if (node.right) output << " Right: " << node.right -> data;
	output << "\n";
	return output;
}

};
*/

/*namespace TreeDTS_v11 {
#include <iostream>

using namespace std;

template <typename T>
class BSTree {

private:

    typedef struct Node {
        T key;
        Node *left, *right;

        Node() {
            left = right = NULL;
        }
    } Node;

    Node *root;

    // in-order traversal tree deletion
    template<typename Func>
    void inOrder(Node *node, Func f) {
        if(node != NULL) {
            inOrder(node->left, f); // recurse to left subtree
            f(node);
            inOrder(node->right, f); // recurse to right subtree
        }
    }

    Node *insert(Node *node, T n) {

        // if we hit the jackpot
        // then create new node here with new value
        if (node == NULL) {
            node = new Node;
            node->key = n;

        // not hitting the jackpot yet!??!!?!

        // value is less than root's key? then recurse to left
        } else if(n < node->key) {
            node->left = insert(node->left, n);

        // or recurse right if value is more than root's key
        } else if(n > node->key) {
            node->right = insert(node->right, n);
        }

        return node;
    }

    Node *search(Node *node, T n) {

        // if root = NULL (empty tree)
        // or root = what we want to find for
        // then return root itself
        if(node == NULL || node->key == n) {
            return node;

        // if key is less than root's key, then go find in left-subtree
        } else if(n < node->key) {
            return search(node->left, n);

        // if key is more than root's key, then go find in right-subtree
        } else if(n > node->key) {
            return search(node->right, n);
        }

    }

    Node *deleteNode(Node *node, T n) {

        if(node == NULL)
            return NULL;

        else if(n < node->key)
            node->left = deleteNode(node->left, n);

        else if(n > node->key)
            node->right = deleteNode(node->right, n);

        else { // if found node that we want to delete

            Node *current, *tmp;

            // if only have right child node
            if(node->left == NULL) {
                tmp = node->right;
                delete node;
                return tmp;

            // if only have left child node
            } else if(node->right == NULL) {

                tmp = node->left;
                delete node;
                return tmp;

            // if have both childs
            } else {

                for(current = node->right;
                    current != NULL;
                    current = current->left) {} // lowest below in right subtree

                node->key = current->key;
                deleteNode(current, current->key);
            }
        }

        return node;
    }

public:

    BSTree() {
        root = NULL;
    }

    ~BSTree() {
        inOrder([](Node *node) {
            delete node;
        });
    }

    void insert(T n) {
        root = insert(root, n);
    }

    bool search(T n) {
        Node *get = search(root, n);
        return get != NULL;
    }

    void deleteNode(T n) {
        root = deleteNode(root, n);
    }

    template<typename Func>
    void inOrder(Func f) {
        inOrder(root, f);
    }

    void inOrder_print() {

        cout << "Element inside BSTree : ";

        inOrder([](Node *node) {
            cout << node->key << ' ';
        });

        cout << endl;
    }
};

int main(int argc, char const *argv[]) {

    BSTree<int> bt;

    // insert some dummy value
    bt.insert(12);
    bt.insert(1);
    bt.insert(2);
    bt.insert(1000);

    bt.inOrder_print();

    // delete some node
    bt.deleteNode(1);

    bt.inOrder_print();

    // search some node
    cout << "54 was " << (bt.search(54) ? "found" : "not found") << " inside BSTree" << endl;

    return 0;
}

};
*/

/*namespace TreeDTS_v12 {
//====================================================================
// Object.h
//
// This class represents an Object class that stores a character as
// its data member. Simple operations can be done with it such as
// output, assignmet, and comparison.
//
// Author: John Steele <steelejr@u.washington.edu>
// Date  : 2010/10/19
// Class : CSS 343 - Lab 2
//====================================================================
// Object class:
//   Includes following features:
// 	- allows output << of the Object.
// 	- allows for assignment of 2 Objects.
//	- allows comparisons (< and >) of an Object.
//	- allows for equality and inequality comparisons of 2 Objects.
// Assumptions:
//====================================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>
using namespace std;

class Object {

	//============================================================
	// Overloaded  output operator for Object class.
	//
	// Preconditions: none.
	//
	// Postconditions: my_char is sent to output using iostream.
	//============================================================
	friend ostream& operator<< (ostream &, const Object &);

public:

	//========================Constructor=========================
	// Creates an Object with the specified character.
	//
	// Preconditions:  None.
	//
	// Postconditions: my_char is set to the_char.
	//============================================================
	Object (char);


	//========================Copye-Constructor===================
	// A simple copy constructor.
	//
	// Preconditions:  None.
	//
	// Postconditions: my_char is set to the_other.my_char
	//============================================================
	Object (const Object &);


	//========================operator(=)=========================
	// Overloaded assignment operator.
	//
	// Preconditions:
	//
	// Postconditions: the_other is copied into this.
	//		   this is then returned.
	//============================================================
	const Object& operator=  (const Object &);


	//========================operator(==)========================
	// Determine if two Objects are equal. Two Object are equal
	// if they have the same character.
	//
	// Preconditions: none.
	//
	// Postconditions: true is returned if the this and the_other
	//		   Object have the same character.
	//		   false otherwise.
	//============================================================
	bool operator==  (const Object &) const;


	//========================operator(!=)========================
	// Determine if two Objects are not equal. Two Objects are
	// not equal if they d not have the same character.
	//
	// Preconditions: none.
	//
	// Postconditions: false is returned if the Objects have the
	// 		   same character. True otherwise.
	//============================================================
	bool operator!= (const Object &) const;


	//========================operator(<)========================
	// Overloaded comparison operator. Compares this Object with
	// the_other for less than value. If the value of this
	// my_char is less than the_other.my_char it returns true.
	// Valus are compared based on their ASCII value.
	//
	// Preconditions: none.
	//
	// Postconditions: Returns true if the ASCII value of my_char
	// 		   is less than the ASCII value of the_other.
	//		   my_char. Returns false otherwise.
	//============================================================
	bool operator< (const Object &) const;


	//========================operator(>)========================
	// Overloaded comparison operator. Compares this Object with
	// the_other for greater than value. If the value of this
	// my_char is greater than the_other.my_char it returns true.
	// Valus are compared based on their ASCII value.
	//
	// Preconditions: none.
	//
	// Postconditions: Returns true if the ASCII value of my_char
	// 		   is greater than the ASCII value of
	//		   the_other.my_char. Returns false otherwise.
	//============================================================
	bool operator> (const Object &) const;

private:

	char my_char;      // The character this object holds.
};
#endif
//====================================================================
// Object.cpp
//
// This class represents an Object class that stores a character as
// its data member. Simple operations can be done with it such as
// output, assignmet, and comparison.
//
// Author: John Steele <steelejr@u.washington.edu>
// Date  : 2010/10/19
// Class : CSS 343 - Lab 2
//====================================================================
// Object class:
//   Includes following features:
// 	- allows output << of the Object.
// 	- allows for assignment of 2 Objects.
//	- allows comparisons (< and >) of an Object.
//	- allows for equality and inequality comparisons of 2 Objects.
// Assumptions:
//====================================================================


//========================Constructor=================================
// Creates an Object with the specified character.
//
// Preconditions:  None.
//
// Postconditions: my_char is set to the_char.
//====================================================================
Object::Object (char the_char)
{
	my_char = the_char;
}


//========================Copye-Constructor===========================
// A simple copy constructor.
//
// Preconditions:  None.
//
// Postconditions: my_char is set to the_other.my_char
//====================================================================
Object::Object (const Object &the_other)
{
	// Calls our overloaded operator=.
	*this = the_other;
}

//========================operator(=)=================================
// Overloaded assignment operator.
//
// Preconditions:
//
// Postconditions: the_other is copied into this.
//		   this is then returned.
//====================================================================
const Object& Object::operator=  (const Object &the_other)
{
	my_char = the_other.my_char;
	return *this;
}


//========================operator(==)================================
// Determine if two Objects are equal. Two Object are equal if they
// have the same character.
//
// Preconditions: none.
//
// Postconditions: true is returned if the this and the_other Object
//		   have the same character. false otherwise.
//====================================================================
bool Object::operator==  (const Object &the_other) const
{
	return (my_char == the_other.my_char);
}


//========================operator(!=)================================
// Determine if two Objects are not equal. Two Objects are not equal
// if they d not have the same character.
//
// Preconditions: none.
//
// Postconditions: false is returned if the Objects have the same
// 		   character. Returns true otherwise.
//====================================================================
bool Object::operator!= (const Object &the_other) const
{
	return !(*this == the_other);
}


//========================operator(<)=================================
// Overloaded comparison operator. Compares this Object with the_other
// for less than value. If the value of this my_char is less than
// the_other.my_char it returns true. Valus are compared based on
// their ASCII value.
//
// Preconditions: none.
//
// Postconditions: Returns true if the ASCII value of my_char is less
// 		   than the ASCII value of the_other.my_char.
//		   Returns false otherwise.
//====================================================================
bool Object::operator< (const Object &the_other) const
{
	return (my_char < the_other.my_char);
}


//========================operator(>)=================================
// Overloaded comparison operator. Compares this Object with the_other
// for greater than value. If the value of this my_char is greater
// than the_other.my_char it returns true. Valus are compared based
// on their ASCII value.
//
// Preconditions: none.
//
// Postconditions: Returns true if the ASCII value of my_char is
//		   greater than the ASCII value of the_other.my_char.
//		   Returns false otherwise.
//====================================================================
bool Object::operator> (const Object &the_other) const
{
	return (my_char > the_other.my_char);
}



//====================================================================
// Overloaded  output operator for Object class.
//
// Preconditions: none.
//
// Postconditions: my_char is sent to output using iostream, output
//		   is then returned.
//====================================================================
ostream& operator<< (ostream &output, const Object &the_other)
{
	output << the_other.my_char;
	return output;
}

//====================================================================
// BSTree.h
//
// This class represents a node-based binary search tree data
// structure, which has the following properties: The left subtree
// of a node contains only nodes with keys less than the node's key;
// The right subtree of a node contains only nodes with keys greater
// than the node's key; Both the left and right subtrees must also
// be binary search trees.
//
// Author: John Steele <steelejr@u.washington.edu>
// Date  : 2010/10/19
// Class : CSS 343 - Lab 2
//====================================================================
// Binary class:
//   Includes following features:
// 	- allows output << of a BSTree.
//	- allows insterting an Object into the tree.
//	- allows removing an Object from the tree.
//	- allows retrieving an Object from the tree.
//	- allows getting the depth of a node in the tree.
//	- allows checking if the tree is empty.
//	- allows making the tree empty.
//	- allows getting the number of descendents a node has.
// 	- allows for equality and inequality comparisons of 2 BSTrees.
//	- allows for assignment of 2 BSTrees.
// Assumptions:
//====================================================================

#ifndef _BSTREE_H_
#define _BSTREE_H_
#include <iostream>
using namespace std;


class BSTree {

	//============================================================
	// Overloaded  output operator for BSTree class.
	//
	// Preconditions: the_bstree.my_root must point to the first
	//		  element of the BSTree, or NULL.
	//
	// Postconditions: The elements of the_bstree are sent to
	//		   the output using iostream using a frequency
	//		   table format. It uses an in-order traversal
	//		   of the tree and orders them accordting to
	//		   ASCII. The stream is then returned.
	//============================================================
	friend ostream& operator<< (ostream &, const BSTree &);


public:
	//========================Default-Constructor=================
	// Creates a BSTree object with a null root.
	//
	// Preconditions:  None.
	//
	// Postconditions: This BSTree object has been instantiated,
	//		   and my_root points to NULL.
	//============================================================
	BSTree ();


	//========================Copy-Constructor====================
 	// Copies the_other BSTree object into this.
	//
	// Preconditions:  the_other.my_root points to NULL or the
	//		   first Object in the_other's BSTree.
	//
	// Postconditions: the_other is copied into *this.
	//============================================================
	BSTree (const BSTree &);


	//========================Destructor==========================
	// Cleans up and deallocates all dynamic memory.
	//
	// Preconditions:  my_root points to NULL or the first Object
	// 		   in this BSTree.
	//
	// Postconditions: This BSTree memory has been deallocated.
	//============================================================
	~BSTree ();


	//========================retrieve============================
	// Finds the provided object in this tree. Returns NULL if the
	// item is not found. Calls a recursive helper method.
	//
	// Preconditions: The Object is not NULL and contains a valid
	// 		  ASCII character.
	//
	// Postconditions: Returns a pointer to the Object if found,
	//	 	   a NULL pointer is returned otherwise.
	//============================================================
	const Object * retrieve (const Object &) const;


	//========================depth===============================
	// Returns the depth of a character in the tree. The depth
	// of root is 0.
	//
	// Preconditions: my_root is not NULL.
	//
	// Postconditions: Returns the depth of the character in this
	//		   tree, returns -1 if not found.
	//============================================================
	int depth (const Object &) const;


	//========================descendents=========================
	// Returns the number of descendents of the node storing the
	// character in the BSTree. A leaf has zero descendents.
	//
	// Preconditions: Overloaded output operator of Object class
	//		  must be overrided to display the character.
	//
	// Postconditions: Returns the number of Node descendents of
	// 		   the Node storing the provided character.
	//		   Retuns -1 if the object is not found.
	//============================================================
	int descendents (const Object &) const;


	//========================isEmpty=============================
	// Returns true if this BSTree contains no data.
	//
	// Preconditions: my_root points to NULL or the first Object
	// 		  in this BSTree.
	//
	// Postconditions: returns true if this BSTree contains no
	// 		   data, false otherwise.
	//============================================================
	bool isEmpty () const;


	//========================insert==============================
	// Inserts the given Object into this BSTree. If the character
	// in the object is already in the tree its count is
	// incremented, and this tree does not take responsibility
	// for the memory of the Object. It it isn't in the tree
	// the tree takes responsibility of the memory of the Object.
	//
	// Preconditions: my_root points to NULL or the first Object
	// 		  in this BSTree. Additionally,
	//		  the_item != NULL.
	//
	// Postconditions: Returns true if the_item is insterted in
	//		   this BSTree.False is returned if the char-
	//		   acter is found, the character count is
	//		   just incremented. This BSTree only takes
	//		   ownership of the Object if the character
	// 		   is not found.
	//============================================================
	bool insert (Object *);


	//========================remove==============================
	// Removes one occurance of the item from this BSTree. If
	// it is the last occurence, the Object is removed. Calls a
	// helper recursive method.
	//
	// Preconditions: the_item is a reference to a non NULL
	//		  object.
	//
	// Postconditions: Returns true if the item is found and
	//		   an occurance of it is removed. If it is the
	//		   last occurence the Object is removed. False
	// 		   is returned if the item is not found.
	//============================================================
	bool remove (const Object &);


	//========================makeEmpty===========================
	// Deallocates all Objects in this BSTree and sets its
	// root to NULL, isEmpty() would then return true.
	//
	// Preconditions: my_root points to NULL or the first Object
	// 		  in this BSTree.
	//
	// Postconditions: All memory has been deallocated,
	//		   root is NULL.
	//============================================================
	void makeEmpty ();


	//========================operator(=)=========================
	// Overloaded assignment operator.
	//
	// Preconditions: the_other.my_root points to the first Node
	//		  in the tree, or NULL.
	//
	// Postconditions: the_other is copied into this.
	//		   this is then returned.
	//============================================================
	const BSTree& operator=  (const BSTree &);


	//========================operator(==)========================
	// Determine if two BSTrees are equal. Two trees are equal
	// if they have the same data, the same structure, and the
	// same number of occurances for each character.
	//
	// Preconditions: my_root and the_other.my_root point to the
	//		  first Node in the tree, or NULL.
	//
	// Postconditions: true is returned if the this and the_other
	//		   tree have the same data, the same structure
	//		   and the same number of occurances for each
	//		   character.
	//============================================================
	bool operator==  (const BSTree &) const;


	//========================operator(!=)========================
	// Determine if two BSTrees are not equal. Two trees are not
	// equal if they do not have the same data, or same structure,
	// or same number of of occurances for each character.
	//
	// Preconditions: my_root and the_other.my root point to the
	//		  first Node their tree or NULL.
	//
	// Postconditions: false is returned if the trees have the
	// 		   same data, same structure, and same
	// 		   number of occurances of each character.
	//		   True otherwise.
	//============================================================
	bool operator!= (const BSTree &) const;


private:

	// The Node structure in the BSTree.
	struct Node {
		Object *item;   // Object data being stored.
		Node *left;     // Left  child subtree.
		Node *right;    // Right child subtree.
		int occurances; // Occurances of the character.
	};

	Node *my_root;	        // The root of this BSTree.


	//========================insertHelper========================
	// A helper method for instert that recursively inserts the
	// given Object into this tree. Returns true and inserts the
	// Object only if its item does not exist in the tree. Other
	// if found it increments the count and returns false, thus
	// ownership of the Object remains with the client.
	//
	// Preconditions: my_root points to NULL or the first Object
	// 		  in this BSTree.
	//
	// Postconditions: Returns true if the_item is insterted in
	//		   this BSTree.False is returned if the char-
	//		   acter is found, the character count is
	//		   just incremented. This BSTree only takes
	//		   ownership of the Object if the character
	// 		   is not found.
	//============================================================
	bool insertHelper (Node *&, Object *);


	//========================retrieveHelper======================
	// A helper method for retrieve. It recursively finds the
	// provided object in this tree. Returns NULL if the item is
	// not found.
	//
	// Preconditions: The Object is not NULL and has operator<
	//  		  implemented correctly to compare values.
	//
	// Postconditions: Returns a pointer to the Object if found,
	//	 	   a NULL pointer is returned otherwise.
	//============================================================
	const Object * retrieveHelper (const Node *root,
					const Object &) const;


	//========================removeHelper========================
	// Removes one occurance of the item from this BSTree. If
	// it is the last occurence, the Object is removed.
	//
	// Preconditions: the_item is a reference to a non NULL
	//		  object.
	//
	// Postconditions: Returns true if the item is found and
	//		   an occurance of it is removed. If it is the
	//		   last occurence the Object is removed. False
	// 		   is returned if the item is not found.
	//============================================================
	bool removeHelper (Node *&, const Object &);


	//========================deleteRoot==========================
	// Deletes the node that the given pointer points to. If
	// left and right pointer of the node is not NULL, then we
	// we delete the item in the node and replace it with the
	// most left node in its right subtree.
	//
	// Preconditions: root is not NULL.
	//
	// Postconditions: the root has been deleted.
	//============================================================
	void deleteRoot (Node *&);


	//========================findAndDeleteMostLeft===============
	// Returns the Object item from the node that is located
	// at the most left subtree of the given root.
	//
	// Preconditions: root is not NULL.
	//
	// Postconditions: Returns a pointer to the Object of the most
	// 		   left node. That node that previously stored
	// 		   the item is then deleted.
	//============================================================
	Object * findAndDeleteMostLeft (Node *&);


	//========================depthHelper=========================
	// A helper method that recursively calcuates the depth of
	// the provided Object.
	//
	// Preconditions: The Object is not NULL.
	//
	// Postconditions: Returns the depth of the given Object.
	//		   Returns -1 if the Object is not found.
	//============================================================
	int depthHelper (Node *, const Object &) const;


	//========================descendentsHelper===================
	// A helper method that calculates the descendents of the
	// given Object.
	//
	// Preconditions: The Object is not NULL.
	//
	// Postconditions: Returns the number of descendents the given
	//		   Object has. Returns -1 if the Object is not
	//		   found.
	//============================================================
	int descendentsHelper (const Node *, const Object &) const;


	//========================countNodes==========================
	// Counts the number of nodes in the given tree.
	//
	// Preconditions: root is not NULL.
	//
	// Postconditions: Returns number of nodes in the given tree.
	//============================================================
	int countNodes (const Node *) const;


	//========================makeEmptyHelper=====================
	// Deletes the nodes in the given tree recursively.
	//
	// Preconditions: root is not NULL.
	//
	// Postconditions: The tree is empty.
	//============================================================
	void makeEmptyHelper (Node *&) const;


	//========================printHelper=========================
	// A helper method that recursively prints the the given
	// tree in-order.
	//
	// Preconditions: root is not NULL.
	//
	// Postconditions: The tree is sent to the output.
	//============================================================
	void printHelper (ostream &, const Node *) const;


	//========================clone===============================
	// Clones the given originalTree into the subtree of copy
	// recursively.
	//
	// Preconditions: origninalTree is not NULL. Object has a
	//		  copy-constructor.
	//
	// Postconditions: copy now contains its own copies of the
	//		   nodes contained in the originalTree.
	//============================================================
	void clone (Node *&, const Node *);


	//========================compareHelper=======================
	// A recursive method that compares two trees. Returns false
	// if they are not the same.
	//
	// Preconditions: root and other are not NULL.
	//
	// Postconditions: Returns false if the trees are not the
	//		   same.
	//============================================================
	bool compareHelper (const Node *, const Node *) const;

};
#endif

//====================================================================
// BSTree.cpp
//
// This class represents a node-based binary search tree data
// structure, which has the following properties: The left subtree
// of a node contains only nodes with keys less than the node's key;
// The right subtree of a node contains only nodes with keys greater
// than the node's key; Both the left and right subtrees must also
// be binary search trees.
//
// Author: John Steele <steelejr@u.washington.edu>
// Date  : 2010/10/19
// Class : CSS 343 - Lab 2
//====================================================================
// Binary class:
//   Includes following features:
// 	- allows output << of a BSTree.
//	- allows insterting an Object into the tree.
//	- allows removing an Object from the tree.
//	- allows retrieving an Object from the tree.
//	- allows getting the depth of a node in the tree.
//	- allows checking if the tree is empty.
//	- allows making the tree empty.
//	- allows getting the number of descendents a node has.
// 	- allows for equality and inequality comparisons of 2 BSTrees.
//	- allows for assignment of 2 BSTrees.
// Assumptions:
//====================================================================



//========================Default-Constructor=========================
// Creates a BSTree object with a null root.
//
// Preconditions:  None.
//
// Postconditions: This BSTree object has been instantiated, and
//		   my_root points to NULL.
//====================================================================
BSTree::BSTree ()
{
	my_root = NULL;
}


//========================Copy-Constructor============================
// Copies the_other BSTree object into this.
//
// Preconditions:  the_other.my_root points to NULL or the first
//		   Object in the_other's BSTree.
//
// Postconditions: the_other is copied into *this.
//====================================================================
BSTree::BSTree (const BSTree &the_other)
{
	my_root = NULL;
	*this = the_other;
}


//========================Destructor==================================
// Cleans up and deallocates all dynamic memory.
//
// Preconditions:  my_root points to NULL or the first Object in
//		   this BSTree.
//
// Postconditions: This BSTree memory has been deallocated.
//====================================================================
BSTree::~BSTree()
{
	makeEmpty();
}



//========================retrieve====================================
// Finds the provided object in this tree. Returns NULL if the item
// is not found.
//
// Preconditions: The Object is not NULL and contains a valid
//		  ASCII character.
//
// Postconditions: Returns a pointer to the Object if found,
//	 	   a NULL pointer is returned otherwise.
//====================================================================
const Object * BSTree::retrieve (const Object &the_item) const
{
	return retrieveHelper(my_root, the_item);
}


//========================retrieveHelper==============================
// A helper method for retrieve. It recursively finds the provided
// object in this tree. Returns NULL if the item is not found.
//
// Preconditions: The Object is not NULL and has operator<
//  		  implemented correctly to compare values.
//
// Postconditions: Returns a pointer to the Object if found,
//	 	   a NULL pointer is returned otherwise.
//====================================================================
const Object * BSTree::retrieveHelper (const Node *root,
					const Object &the_item) const
{
	if (root == NULL) return NULL;

	else if (the_item == *root->item)
		return root->item;

	else if (the_item < *root->item)
		return retrieveHelper (root->left, the_item);

	else
		return retrieveHelper (root->right, the_item);
}


//========================depth=======================================
// Returns the depth of a character in the tree. The depth
// of root is 0.
//
// Preconditions: my_root is not NULL.
//
// Postconditions: Returns the depth of the character in this tree,
// 		   returns -1 if not found.
//====================================================================
int BSTree::depth (const Object &the_item) const
{
	return depthHelper(my_root, the_item);
}


//========================depthHelper=================================
// A helper method that recursively calcuates the depth of the
// provided Object.
//
// Preconditions: The Object is not NULL.
//
// Postconditions: Returns the depth of the given Object. If the
//		   Returns -1 the Object is not found.
//====================================================================
int BSTree::depthHelper (Node *root, const Object &the_item) const
{
	// Item not found.
	if (root == NULL) return -1;
	// Found it.
	if (*root->item == the_item) return 0;

	int subtree = depthHelper (root->left, the_item);

	if (subtree == -1)
		 subtree = depthHelper (root->right, the_item);

	if (subtree == -1) return -1;

	else return 1 + subtree;
}


//========================descendents=================================
// Returns the number of descendents of the node storing the character
// in the BSTree. A leaf has zero descendents.
//
// Preconditions: Overloaded output operator of Object class
//		  must be overrided to display the character.
//
// Postconditions: Returns the number of Node descendents of
// 		   the Node storing the provided character.
//		   Retuns -1 if the object is not found.
//====================================================================
int BSTree::descendents (const Object &the_item) const
{
	int result = descendentsHelper(my_root, the_item);
	return (result == -1 ? -1 : result - 1);
}


//========================descendentsHelper===========================
// A helper method that calculates the descendents of the
// given Object.
//
// Preconditions: The Object is not NULL.
//
// Postconditions: Returns the number of descendents the given
//		   Object has. Returns -1 if the Object is not found.
//====================================================================
int BSTree::descendentsHelper (const Node *root,
					const Object &the_item) const
{
	if (root == NULL) return -1;

	if (the_item == *root->item) {
		// We found the node, now return the number of nodes
		// in it's left and right subtrees.
		return countNodes (root);
	}
	if (the_item < *root->item)
		return descendentsHelper (root->left, the_item);
	else
		return descendentsHelper (root->right, the_item);

}


//========================countNodes==================================
// Counts the number of nodes in the given tree.
//
// Preconditions: root is not NULL.
//
// Postconditions: Returns number of nodes in the given tree.
//====================================================================
int BSTree::countNodes (const Node *root) const
{
	if (root == NULL) return 0;

	return 1 + countNodes (root->left) + countNodes (root->right);
}


//========================isEmpty=====================================
// Returns true if this BSTree contains no data.
//
// Preconditions: my_root points to NULL or the first Object
// 		  in this BSTree.
//
// Postconditions: returns true if this BSTree contains no data,
//		   returns false otherwise.
//====================================================================
bool BSTree::isEmpty () const
{
	return (my_root == NULL);
}


//========================insert======================================
// Inserts the given Object into this BSTree. If the character in the
// object is already in the tree its count is incremented, and this
// tree does not take responsibility for the memory of the Object.
// It it isn't in the tree the tree takes responsibility of the
// memory of the Object.
//
// Preconditions: my_root points to NULL or the first Object in this
// 		  BSTree. Additionally, the_item != NULL.
//
// Postconditions: Returns true if the_item is insterted in this
//		   BSTree.False is returned if the character is found,
//		   the character count is just incremented.
//		   This BSTree only takes ownership of the Object if
//		   the character is not found.
//====================================================================
bool BSTree::insert (Object *the_item)
{
	return insertHelper (my_root, the_item);
}

//========================insertHelper================================
// A helper method for instert that inserts the given Object into
// this tree. Returns true and inserts the Object only if its item
// does not exist in the tree. Other if found it increments the
// count and returns false, thus ownership of the Object remains
// with the client.
//
// Preconditions: my_root points to NULL or the first Object
// 		  in this BSTree.
//
// Postconditions: Returns true if the_item is insterted in
//		   this BSTree.False is returned if the char-
//		   acter is found, the character count is
//		   just incremented. This BSTree only takes
//		   ownership of the Object if the character
// 		   is not found.
//====================================================================
bool BSTree::insertHelper (Node *&the_root, Object *the_item)
{
	if (the_root == NULL) {
		the_root        = new Node;
		// We're taking ownership of the Object.
		the_root->item  = the_item;
		the_root->left  = NULL;
		the_root->right = NULL;
		the_root->occurances = 1;
		return true;
	}

	else if (*the_root->item == *the_item) {
		// Ownership of Object goes back to client.
		the_root->occurances++;
		return false;
	}

	else if (*the_item < *the_root->item)
		return insertHelper(the_root->left, the_item);

	 else
		return insertHelper(the_root->right, the_item);
}


//========================remove======================================
// Removes one occurance of a character from this BSTree. If it is the
// last occurence, the Object is removed. Calls a helper method that
// recursively removes the node.
//
// Preconditions: the_item is a reference to a non NULL object.
//
// Postconditions: Returns true if the character is found and an
//		   occurance of it is removed. If it is the last
// 		   occurence the Object is removed. False is returned
//		   if the character is not found.
//====================================================================
bool BSTree::remove (const Object &the_item)
{
	return removeHelper (my_root, the_item);
}


//========================removeHelper================================
// Removes one occurance of the item from this BSTree. If it is the
// last occurence, the Object is removed.
//
// Preconditions: the_item is a reference to a non NULL
//		  object.
//
// Postconditions: Returns true if the item is found and an occurance
//		   of it is removed. If it is the last occurence the
//		   Object is removed. False is returned if the
//		   item is not found.
//====================================================================
bool BSTree::removeHelper (Node *&root, const Object &the_item)
{
	if (root == NULL) return false;

	else if (the_item == *root->item) {
		// More than one occurance, so decrment one.
		if (root->occurances > 1)
			root->occurances--;

		// Otherwise, there's one occurance, so delete it.
		else
			deleteRoot (root);

		// We decremented the occurance or deleted the node.
		return true;
	}

	else if (the_item < *root->item)
		return removeHelper (root->left, the_item);
	else
		return removeHelper (root->right, the_item);
}


//========================deleteRoot==================================
// Deletes the node that the given pointer points to. If left and
// right pointer of the node is not NULL, then we we delete the item
// in the node and replace it with the most left node in its right
// subtree.
//
// Preconditions: root is not NULL.
//
// Postconditions: the root has been deleted.
//====================================================================
void BSTree::deleteRoot (Node *&root)
{
	// Only node in the tree, or a leaf, so delete it.
	if (root->left == NULL && root->right == NULL) {
		delete root->item;
		delete root;
		root = NULL;
	}

	else if (root->left == NULL) {
		Node *temp = root;
		root = root->right;
		delete temp->item;
		delete temp;
	}

	else if (root->right == NULL) {
		Node *temp = root;
		root = root->left;
		delete temp->item;
		delete temp;
	}

	// We have a subtree on both sides, delete the root's item.
	// Replace it with the most left item in the right subtree.
	else {
		delete root->item;
		root->item = findAndDeleteMostLeft(root->right);
	}
}


//========================findAndDeleteMostLeft=======================
// Returns a pointer to the Object item from the node that is located
// at the most left subtree of the given root.
//
// Preconditions: root is not NULL.
//
// Postconditions: Returns a pointer to the Object of the most left
//		   node. That node that previously stored the item
//		   is then deleted.
//====================================================================
Object * BSTree::findAndDeleteMostLeft (Node *&root)
{
	// If we reached the furthest left node.
	if (root->left == NULL) {
		// Get the item to return.
		Object *result = root->item;
		Node *temp     = root;
		root           = root->right;
		delete temp;
		return result;
	}

	else  // Keep going left until we're NULL.
		return findAndDeleteMostLeft (root->left);
}


//========================makeEmpty===================================
// Deallocates all Objects in this BSTree and sets its root to NULL,
// isEmpty() would then return true.
//
// Preconditions: my_root points to NULL or the first Object in
// 		  this BSTree.
//
// Postconditions: All memory has been deallocated, root is NULL.
//====================================================================
void BSTree::makeEmpty ()
{
	makeEmptyHelper (my_root);
}


//========================makeEmptyHelper=============================
// Deletes the nodes in the given tree recursively.
//
// Preconditions: root is not NULL.
//
// Postconditions: The tree is empty.
//====================================================================
void BSTree::makeEmptyHelper (Node *&root) const
{
	if (root != NULL) {
		makeEmptyHelper (root->left);
		makeEmptyHelper (root->right);
		delete root->item;
		delete root;
		root->item = NULL;
	}
	root = NULL;
}


//========================operator(=)=================================
// Overloaded assignment operator.
//
// Preconditions: the_other.my_root points to the first Node in the
//		  tree, or NULL.
//
// Postconditions: the_other is copied into this.
//		   this is then returned.
//====================================================================
const BSTree& BSTree::operator=  (const BSTree &the_other)
{
	// Check for self assignment.
	if (this != &the_other) {
		// Delete our current memory.
		makeEmpty();
		// Now copy the other's tree.
		clone (my_root, the_other.my_root);
	}
	return *this;
}


//========================clone=======================================
// Clones the given originalTree into the subtree of copy recursively.
//
// Preconditions: originalTree is not NULL. Object has a
//		  copy constructor.
//
// Postconditions: copy contains its own copy of the originalTree.
//====================================================================
void BSTree::clone (Node *&copy, const Node *originalTree)
{
	if (originalTree == NULL) {
		copy = NULL;
	}

	else {
		// Our new Node.
		copy = new Node;

		// Link the data into our new Node.
		copy->item       = new Object (*originalTree->item);
		copy->occurances = originalTree->occurances;
		// Now clone left and right subtrees.
		clone(copy->left,  originalTree->left);
		clone(copy->right, originalTree->right);
	}
}


//========================operator(==)================================
// Determine if two BSTrees are equal. Two trees are equal if they
// have the same data, the same structure, and the same number of
// occurances for each character.
//
// Preconditions: my_root and the_other.my_root point to the first
//		  Node in the tree, or NULL.
//
// Postconditions: true is returned if the this and the_other tree
//		   have the same data, the same structure and the
//		   same number of occurances for each character.
//====================================================================
bool BSTree::operator==  (const BSTree &the_other) const
{
	return compareHelper (my_root, the_other.my_root);
}


//========================compareHelper===============================
// A recursive method that compares two trees. Returns false
// if they are not the same.
//
// Preconditions: root and other are not NULL.
//
// Postconditions: Returns false if the trees are not the
//		   same.
//====================================================================
bool BSTree::compareHelper (const Node *root, const Node *other) const
{

	// Is one NULL and not the other.
	if (root == NULL && other != NULL ||
		root != NULL && other == NULL) return false;

	// Are they both NULL.
	if (root == NULL && other == NULL) return true;

	// Is one item NULL and not the other.
	if (root->item == NULL && other->item != NULL ||
		root->item != NULL && other->item == NULL) return false;

	// We know that the items of each Object are not NULL,
	// so it's safe to dereference and compare.
	if (*root->item != *other->item) return false;

	// Same Object, now check occurances.
	if (root->occurances != other->occurances) return false;

	// Everything matched.
	// Now lets check the left and right subtree.
	compareHelper (root->left, other->left);
	compareHelper (root->right, other->right);
}


//========================operator(!=)================================
// Determine if two BSTrees are not equal. Two trees are not equal if
// they do not have the same data, or same structure, or same number
// of of occurances for each character.
//
// Preconditions: my_root and the_other.my root point to the first
//		  Node their tree or NULL.
//
// Postconditions: false is returned if the trees have the same data,
//		   same structure, and same  number of occurances of
//		   each character. Returns True otherwise.
//====================================================================
bool BSTree::operator!= (const BSTree &the_other) const
{
	return !(*this == the_other);
}


//====================================================================
// Overloaded  output operator for BSTree class.
//
// Preconditions: the_bstree.my_root must point to the first element
//		  of the BSTree, or NULL.
//
// Postconditions: The elements of the_bstree are sent to the output
//		   using iostream using a frequency table format.
//		   It uses an in-order traversal of the tree.
//		   The stream is then returned.
//====================================================================
ostream& operator<< (ostream &output, const BSTree &the_other)
{
	the_other.printHelper(output, the_other.my_root);
	return output;
}


//========================printHelper=================================
// A helper method that recursively prints the the given
// tree in-order.
//
// Preconditions: root is not NULL.
//
// Postconditions: The tree is sent to the output.
//====================================================================
void BSTree::printHelper (ostream &output, const Node *root) const
{
	if (root != NULL) {
		printHelper (output, root->left);
		output << *root->item
		       << " "
		       << root->occurances
	  	       << endl;
		printHelper (output, root->right);
	}
}

#include <iostream>
#include <fstream>
using namespace std;


//-------------------------- buildTree --------------------------------------
// Builds a BSTree of characters by reading them from a file stream
// Preconditions:   infile has been successfully initialized
// Postconditions:  T stores the characters (and number of occurrences)
//                   of the unprocessed characters remaining in infile,
//                   (in addition to whatever was previously stored in T)

void buildTree(ifstream &infile, BSTree &T) {
   char ch;

   for (;;) {
      ch = infile.get();                   // gets each and every character
      if (infile.eof()) break;             // no more data

      Object* ptr = new Object(ch);
      bool success = T.insert(ptr);
      if (!success) {                      // must be repeat character
         delete ptr;                       // deallocate if not inserted
      }
   }
}



//-------------------------- main -------------------------------------------
// Tests the BSTree class by reading data from "test.txt" and playing with it
// Preconditions:   None (although it won't test anything if "test.txt"
//					 doesn't exist.)
// Postconditions:  All of the basic operations of the BSTree class are used.
//                  Should compile, run to completion, and output correct
//                  answers if BSTree is implemented correctly.

int main() {
   // create file object and open the datafile
   ifstream infile("HW2.txt");
   if (!infile) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

	BSTree tree;
	tree.insert (new Object ('b'));
	tree.insert (new Object ('a'));
	tree.insert (new Object ('c'));
	tree.insert (new Object ('d'));
	tree.insert (new Object ('e'));
	cout << "depth of a : " << tree.depth ('a') << endl;
	cout << "depth of b : " << tree.depth ('b') << endl;
	cout << "depth of c : " << tree.depth ('c') << endl;
	cout << "depth of d : " << tree.depth ('d') << endl;
	cout << "depth of'e': " << tree.depth ('e') << endl;
	cout << "e descendents: " << tree.descendents ('e') << endl;
	cout << "b descendents: " << tree.descendents ('b') << endl;
	cout << "d descendents: " << tree.descendents ('d') << endl;
	cout << "a descendents: " << tree.descendents ('a') << endl;
	cout << "f descendetns: " << tree.descendents ('f') << endl;

   // test copy constructor, operator=, self-assignment
   BSTree T, T2, duplicate;
   buildTree(infile, T);

  cout << "Tree:" << endl << T << endl;
   BSTree first(T);
   duplicate = duplicate = T;
   duplicate.makeEmpty();

   // test operator<<
   cout << "Frequency table:  " << endl;
   cout << T;
   cout << endl;

   // test retrieve
  const Object *p1 = T.retrieve('n');  // need char Object constructor
  cout << "Retrieve 'n':       " << (p1 != NULL ? "found" : "not found")
       << endl;
  const Object *p2 = T.retrieve('z');
   cout << "Retrieve 'z':       " << (p2 != NULL ? "found" : "not found")
      << endl;

   //test operator==, operator!=
   T2 = T;
   cout << "T == T2?            " << (T == T2 ? "equal" : "not equal") << endl;
   cout << "T != T2?            " << (T != T2 ? "not equal" : "equal") << endl;
   BSTree T3 = T2;                        // test copy constructor, too
   T2.makeEmpty();

   Object *newData = new Object('z');
   bool success = T3.insert(newData);
   if (!success){cout << "Couldn't insert z" << endl;  delete newData;}
   cout << "T == T3?            " << (T == T3 ? "equal" : "not equal") << endl;
   cout << "T != T3?            " << (T != T3 ? "not equal" : "equal") << endl;

   // test depth and descendents
   // if 'q' is in tree, might want to try another character
   cout << "depth of 'a': " << T.depth('a') << endl;
   cout << "depth of 'q': " << T.depth('q') << endl;
   cout << "descendents of 'a': " << T.descendents('a') << endl;
   cout << "descendents of 'q': " << T.descendents('q') << endl;
   cout << "descendents of 'c': " << T.descendents('c') << endl;

   // test remove
   if (!T.remove('a'))
	   cout << "Node 'a' not found." << endl;
   else
	   cout << "Node 'a' removed." << endl;
   cout << "depth of 'a':       " << T.depth('a') << endl;
   if (!T.remove('q'))
	   cout << "Node 'q' not found." << endl;
   else
	   cout << "Node 'q' removed." << endl;
   cout << "depth of 'q':       " << T.depth('q') << endl;

   // test isEmpty, makeEmpty
   cout << "T empty?            " << (T.isEmpty() ? "empty" : "not empty") << endl;
   cout << "Making T empty. " << endl;
   T.makeEmpty();
   cout << "T empty?            " << (T.isEmpty() ? "empty" : "not empty") << endl;

   return 0;
}
};
*/

#endif // TREEDTS_HPP_INCLUDED
