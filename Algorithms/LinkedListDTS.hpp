#ifndef LINKEDLISTDTS_HPP_INCLUDED
#define LINKEDLISTDTS_HPP_INCLUDED

 //* Delete element at a given position

void single_llist::delete_pos()
{
    int pos, i, counter = 0;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    cout<<"Enter the position of value to be deleted: ";
    cin>>pos;
    struct node *s, *ptr;
    s = start;
    if (pos == 1)
    {
        start = s->next;
    }
    else
    {
        while (s != NULL)
        {
            s = s->next;
            counter++;
        }
        if (pos > 0 && pos <= counter)
        {
            s = start;
            for (i = 1;i < pos;i++)
            {
                ptr = s;
                s = s->next;
            }
            ptr->next = s->next;
        }
        else
        {
            cout<<"Position out of range"<<endl;
        }
        free(s);
        cout<<"Element Deleted"<<endl;
    }
}


 //* Update a given Node

void single_llist::update()
{
    int value, pos, i;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    cout<<"Enter the node postion to be updated: ";
    cin>>pos;
    cout<<"Enter the new value: ";
    cin>>value;
    struct node *s, *ptr;
    s = start;
    if (pos == 1)
    {
        start->info = value;
    }
    else
    {
        for (i = 0;i < pos - 1;i++)
        {
            if (s == NULL)
            {
                cout<<"There are less than "<<pos<<" elements";
                return;
            }
            s = s->next;
        }
        s->info = value;
    }
    cout<<"Node Updated"<<endl;
}


// * Searching an element

void single_llist::search()
{
    int value, pos = 0;
    bool flag = false;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    cout<<"Enter the value to be searched: ";
    cin>>value;
    struct node *s;
    s = start;
    while (s != NULL)
    {
        pos++;
        if (s->info == value)
        {
            flag = true;
            cout<<"Element "<<value<<" is found at position "<<pos<<endl;
        }
        s = s->next;
    }
    if (!flag)
        cout<<"Element "<<value<<" not found in the list"<<endl;
}


// * Reverse Link List

void single_llist::reverse()
{
    struct node *ptr1, *ptr2, *ptr3;
    if (start == NULL)
    {
        cout<<"List is empty"<<endl;
        return;
    }
    if (start->next == NULL)
    {
        return;
    }
    ptr1 = start;
    ptr2 = ptr1->next;
    ptr3 = ptr2->next;
    ptr1->next = NULL;
    ptr2->next = ptr1;
    while (ptr3 != NULL)
    {
        ptr1 = ptr2;
        ptr2 = ptr3;
        ptr3 = ptr3->next;
        ptr2->next = ptr1;
    }
    start = ptr2;
}


// Display Elements of a link list

void single_llist::display()
{
    struct node *temp;
    if (start == NULL)
    {
        cout<<"The List is Empty"<<endl;
        return;
    }
    temp = start;
    cout<<"Elements of list are: "<<endl;
    while (temp != NULL)
    {
        cout<<temp->info<<"->";
        temp = temp->next;
    }
    cout<<"NULL"<<endl;
}
};
*/

/*namespace _v7 {

#include<iostream>

using namespace std;

//built node .... node = (data and pointer)
struct node     //node or link
{
    int data;   //data item
    node* next; //pointer to next node

};

//built linked list
class linkedlist
{
    private:
        node* head; //head or first ... pointer to the first node

    public:
        linkedlist()    //constructor
        {
            head=NULL;  //head pointer points to null in the beginning == empty list

        }

        //declaration
        void addElementFirst(int d);            //add element (one node)
        void addElementEnd(int d);              //add element (one node)
        void addElementAfter(int d,int b);      //add element b after node d
        void deleteElement(int d);
        void display();                         //display all nodes

};

//definition

//1-Push front code
void linkedlist::addElementFirst(int d)
{
    //create new node with name newNode with the same size of node and make it pointer to node
    node* newNode=new node;         //new node means allocate the same size of the node
    newNode->data=d;                //give newNode data which is d ...we used -> operator not . operator because newNode is pointer to class .... and we don't use newNode.data=d;
    newNode->next=head;             //make the pointer of new node (newNode) which called (next) points to where the head pointer points to it NOW
    head=newNode;                   //make head pointer points to the new node (newNode)

}

//1-Push back code
void linkedlist::addElementEnd(int x)
{
    node* newNode=new node;     //newNode is the pointer of the new node
    node* temp=new node;        //temp or fromStartToEnd is the pointer must be pointer to the same as head points
    temp=head;                  //fromStartToEnd is the pointer must be pointer to the same as head points
    newNode->data=x;            //in newNode in data put x
    if(temp==NULL)              //means if linked list is empty
    {
        newNode->next=NULL;
        head=newNode;
        return;                 //to end function

    }

    //if not,if there end(head in first then called end) points to node
    while(temp->next!=NULL)
    {
        temp=temp->next;        //make end pointer points to the next node

    }
    newNode->next=NULL;         //make put pointer points to null
    temp->next=newNode;         //then make end pointer points to the new node (put)

}


//head->10->5->8->NULL
//if d=5,key=2
//head->10->5->2->8->NULL
void linkedlist::addElementAfter(int d,int key)    //d is the value that we want
{
    node* search=new node;    //search is pointer must search to points to the node that we want
    search=head;              //firstly search must points to what head points
    while(search!=NULL)       //if linked list has nodes and is not empty
    {
        if(search->data==d)   //if our pointer points to the same value we search
        {
            node* newNode=new node; //create new node called newNode and make it pointer to node
            newNode->data=key;      //put key in data in newNode
            newNode->next=search->next;   //make the next of newNode pointer to the next to search pointer
            search->next=newNode;         //then make search pointer to the newNode
            return;                       //or break;

        }

        //else,means make want pointer to the new next
        search=search->next;
    }
    //if search pointer to null means empty linked list or we reached to the last element and not found the node that we want
    if(search==NULL)  //if linked list empty
        cout<<"The link not inserted because there is not found the node "<<d<<" in the LinkedList. "<<endl;

}

void linkedlist::deleteElement(int d)
{
    node* del;  //del is pointer points to node
    del=head;   //first we make del points to where the head points

    if(del==NULL)   //means if linked list is empty
    {
        cout<<"Linked list is empty"<<endl;
        return;     //return to main

    }

    if(del->data==d)    //if first element in linked list is the element that we want to delete ... or one element is what we want
    {
        head=del->next; //make head points to the next to del
        return;
    }

    //if(del->data!=d) .... the same
    if(del->next==NULL) //if first element in linked list is not the element that we want to delete ... or one element is not what we want
    {
        cout<<"Is not here, So not deleted."<<endl;
        return;
    }

    //if here more one nodes...one node points to another node ... bigger than 2 nodes .. at least 2 nodes
    while(del->next!=NULL)
    {
        if(del->next->data==d)
        {
            del->next=del->next->next;
            return;

        }
        //else
        del=del->next;

    }
    cout<<"Is not here, So not deleted."<<endl;

}


//void linkedlist::display(node *head)
void linkedlist::display()
{
    int n=0;                        //counter for number of node
    node* current=head;             //current is pointer points to where head point .... same as node* current=new node; current=head;

    //if linked list is empty
    if (current==NULL)
        cout<<"This is empty linked list."<<endl;

    //if linked list has nodes
    while(current!=NULL)            //until current reach to null (last element)
    {
        cout<<"The node data number "<<++n<<" is "<<current->data<<endl;  //print data
        current=current->next;      //move to next node

    }
    cout<<endl;

}


int main()
{
    linkedlist li;      //li is object from linkedlist class

    li.display();       //empty list

    li.addElementFirst(25);  //head->25->NULL
    li.addElementFirst(36);  //head->36->25->NULL
    li.addElementFirst(49);  //head->49->36->25->NULL
    li.addElementFirst(64);  //head->64->49->36->25->NULL
    cout<<"After adding in the first of linked list"<<endl;
    li.display();
        //64
        //49
        //36
        //25


    cout<<endl;
    //head->64->49->36->25->NULL	//current linked list from prev addElementFirst method

    cout<<"After adding in the end of linked list"<<endl;
    li.addElementEnd(25);  //head->25->NULL
    li.addElementEnd(36);  //head->25->36->NULL
    li.addElementEnd(49);  //head->25->36->49->NULL
    li.addElementEnd(64);  //head->25->36->49->64->NULL
    li.display();
    //head->64->49->36->25->25->36->49->64->NULL

    cout<<endl;

    //head->64->49->36->25->25->36->49->64->NULL

    cout<<"linked list after adding 10 after node that has data = 49"<<endl;
    li.addElementAfter(49,10);
    li.display();
    //head->64->49->10->36->25->25->36->49->64->NULL

    //head->64->49->10->36->25->25->36->49->64->NULL
    cout<<"linked list after adding deleting 49"<<endl;
    li.deleteElement(49);
    li.display();
    //head->64->10->36->25->25->36->49->64->NULL
    //Notice :delete the first 49 ... not permission for duplicates

    for(int i=0; li.size() ;++i)
    {
	if(li.deleteElement(49))
            li.display();
    }

    return 0;
}



};
*/

/*namespace _v8 {
#include <iostream>

using namespace std;

template<class T>
class Node {
public:
    T value;
    Node<T> *next;

    Node();

    explicit Node(T val);
};

template<class T>
Node<T>::Node() {
    next = nullptr;
}

template<class T>
Node<T>::Node(T val) {
    value = val;
    next = nullptr;
}


template<class E>
class LinkedList {

private:
    Node<E> *head;
    int s;

public:

    const static int SORT_ASC = 0;
    const static int SORT_DESC = 1;

    LinkedList();


//     * Appends the specified element to the end of this list.
//     *
//     * @param e - the element to add

    void add(E e);


//     * Inserts the specified element at the specified position in this list.
//     * Shifts the element currently at that position (if any) and any subsequent
//     * elements to the right (adds one to their indices).
//     *
//     * @param index index at which the specified element is to be inserted
//     * @param e  element to be inserted

    void add(int index, E e);


//     * Inserts the specified element at the beginning of this list.
//     *
//     * @param e  the element to add

    void addFirst(E e);


//     * Appends the specified element to the end of this list.
//     *
//     * @param e the element to add

    void addLast(E e);


//     * Removes the first occurrence of the specified element from this list, if it is present.
//     * If this list does not contain the element, it is unchanged.
//     *
//     * @param e

    void remove(E e);


//     * Removes and returns the first element from this list.

    void removeFirst();


//     * Removes and returns the last element from this list.

    void removeLast();


//     * Returns the number of elements in this list.
//     *
//     * @return the number of elements in this list

    int size();


//     * Returns true if this list contains the specified element.
//     *
//     * @param e element whose presence in this list is to be tested
//     * @return <b>true</b> if this list contains the specified element

    bool contains(E e);


//     * Reverse the whole list

    void reverse();


//     * Sort the list by the given order
//     *
//     * @param order the order to sort the list

    void sort(int order);


//     * Displays the whole list

    void print();


//     * Removes all of the elements from this list and free the allocated memory.

    void clear();
};

template<class E>
LinkedList<E>::LinkedList() {
    head = nullptr;
    s = 0;
}

template<class E>
void LinkedList<E>::addFirst(E e) {
    auto *newNode = new Node<E>(e);
    if (head == nullptr) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }

    s++;
}

template<class E>
void LinkedList<E>::add(E e) {

    auto *newNode = new Node<E>(e);
    if (head == nullptr) {
        head = newNode;
        s++;
        return;
    }

    Node<E> *current = head;
    Node<E> *tmp;

    do {
        tmp = current;
        current = current->next;
    } while (current != nullptr);


    tmp->next = newNode;

    s++;
}

template<class E>
void LinkedList<E>::remove(E e) {

    Node<E> *current = head;
    Node<E> *prev = nullptr;
    bool found = false;

    if (current == nullptr) {
        cerr << "Err: can't perform remove() on an empty list" << endl;
        return;
    }

    do {
        if (current->value == e) {
            found = true;
            break;
        }

        prev = current;
        current = current->next;
    } while (current != nullptr);

    if (!found) {
        cerr << "Err: no element found with value " << e << endl;
        return;
    }

    // if the first element
    if (current == head) {
        prev = head;
        head = current->next;
        delete prev;
        return;
    }

    // if the last element
    if (current->next == nullptr) {
        prev->next = nullptr;
        delete current;
        return;
    }

    prev->next = current->next;
    delete current;

    s--;
}

template<class E>
void LinkedList<E>::removeFirst() {
    Node<E> *tmp = head;

    if (tmp == nullptr) {
        cerr << "Err: can't perform removeFirst() on an empty list" << endl;
        return;
    }

    head = tmp->next;
    delete tmp;

    s--;
}

template<class E>
void LinkedList<E>::removeLast() {
    Node<E> *current = head;
    Node<E> *prev = nullptr;

    if (current == nullptr) {
        cerr << "Err: can't perform removeLast() on an empty list" << endl;
        return;
    }

    do {
        prev = current;
        current = current->next;
    } while (current->next != nullptr);


    if (current->next == nullptr) {
        prev->next = nullptr;
        delete current;
        s--;
        return;
    }

}

template<class E>
void LinkedList<E>::reverse() {

    Node<E> *current = head;
    Node<E> *newNext = nullptr;
    Node<E> *tmp;

    if (current == nullptr) {
        cerr << "Err: can't perform reverse() on an empty list" << endl;
        return;
    }

    do {
        tmp = current->next;
        current->next = newNext;
        newNext = current;
        current = tmp;
    } while (current != nullptr);

    head = newNext;
}

template<class E>
void LinkedList<E>::sort(int order) {

    Node<E> *tmpPtr = head;
    Node<E> *tmpNxt = nullptr;

    if (tmpPtr == nullptr) {
        cerr << "Err: can't perform sort() on an empty list" << endl;
        return;
    }

    tmpNxt = head->next;

    E tmp;

    while (tmpNxt != nullptr) {
        while (tmpNxt != tmpPtr) {
            if (order == SORT_ASC) {
                if (tmpNxt->value < tmpPtr->value) {
                    tmp = tmpPtr->value;
                    tmpPtr->value = tmpNxt->value;
                    tmpNxt->value = tmp;
                }
            } else if (order == SORT_DESC) {
                if (tmpNxt->value > tmpPtr->value) {
                    tmp = tmpPtr->value;
                    tmpPtr->value = tmpNxt->value;
                    tmpNxt->value = tmp;
                }
            } else {
                cerr << "Err: invalid sort order '" << order << "'" << endl;
                return;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = head;
        tmpNxt = tmpNxt->next;
    }
}

template<class E>
void LinkedList<E>::print() {

    Node<E> *current = head;

    cout << "Size:" << s << " -> [ ";
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "] " << endl;
}

template<class E>
void LinkedList<E>::clear() {

    Node<E> *current = head;

    do {
        Node<E> *tmp = current;
        current = current->next;
        delete tmp;
    } while (current != nullptr);

    head = nullptr;

    s = 0;
}

template<class E>
int LinkedList<E>::size() {
    return s;
}

template<class E>
void LinkedList<E>::addLast(E e) {
    add(e);
}

template<class E>
void LinkedList<E>::add(int index, E e) {

    if (index < 0 || index > s) {
        char buff[32];
        snprintf(buff, sizeof(buff), "Index: %d, Size: %d", index, s);
        throw std::out_of_range(buff);
    }

    if (index == 0) {
        addFirst(e);
        return;
    }

    if (index == s) {
        addLast(e);
        return;
    }

    Node<E> *current = head;
    auto *newNode = new Node<E>(e);

    int i = 0;
    do {
        if (i++ == index) {
            break;
        }
        current = current->next;
    } while (current != nullptr);

    newNode->next = current->next;
    current->next = newNode;

    s++;

}

template<class E>
bool LinkedList<E>::contains(E e) {
    Node<E> *current = head;

    while (current != nullptr) {
        if (current->value == e) {
            return true;
        }
        current = current->next;
    }
    return false;
}


int main() {
    LinkedList<int> ll{};


    ll.add(20);
    ll.add(10);
    ll.add(50);
    ll.add(40);
    ll.add(70);
    ll.add(60);
    ll.add(80);

    ll.addFirst(15);
    ll.add(90);
    ll.add(2, 0);
    ll.add(5, 30);
    ll.addLast(100);

    ll.print();

    cout << endl << "LinkedList#remove(60)" << endl;
    ll.remove(60);
    ll.print();

    cout << endl << "LinkedList#reverse()" << endl;
    ll.reverse();
    ll.print();

    cout << endl << "LinkedList#sort(LinkedList<E>::SORT_DESC)" << endl;
    ll.sort(LinkedList<int>::SORT_DESC);
    ll.print();

    cout << endl << "LinkedList#sort(LinkedList<E>::SORT_ASC)" << endl;
    ll.sort(LinkedList<int>::SORT_ASC);
    ll.print();

    cout << endl << "LinkedList#removeFirst()" << endl;
    ll.removeFirst();
    ll.print();

    cout << endl << "LinkedList#removeLast()" << endl;
    ll.removeLast();
    ll.print();

    cout << endl << "LinkedList#removeFirst()\nLinkedList#removeLast()" << endl;
    ll.removeFirst();
    ll.removeLast();
    ll.print();

    ll.clear();

    return 0;
}
};
*/

/*namespace _v9 {

// Linked_list implementation for cracking the code questions

#include <iostream>
#include <stdlib.h>
#include <map>

using namespace std;
template <typename dataType>

class List{

private:
	struct Node{
		Node *next;
		dataType data;
	};

public:
	//constructer
	List();
	List(const List& aList); //copy constructer for deep copy
	List(Node *head);

	//destructor
	~List();

	//operations
	bool isEmpty();
	int getLength();
	void insert(int index, dataType data);
	void remove(int index);
	dataType retrieve(int index);
	dataType extract(int index); // get the value and remove the node
	void printList();
	void removeDuplicates();
	void randomIntFill(int item_num, int max);
	void removeNode(Node* node);
	Node* find(int index);
	Node* sumDigitsWithCarry(Node* head1, Node* head2); // given two list of digits sum those lists
							   // like they are natural numbers with given 1o's order
							   // 9 -> 5 + 9 -> 4 = 8 -> 0 -> 1 = 108

private:
	int size;
	Node *head;
};


template <typename dataType>
List<dataType>::~List(){
	while(!isEmpty())
		remove(0);
}

template <typename dataType>
List<dataType>::List(){
	size = 0;
	head = NULL;
}

template <typename dataType>
List<dataType>::List(Node* aHead){
	size = 0;
	head = aHead;
	for(Node* cur = head; cur != NULL; cur = cur->next){
		// cout << cur -> data << endl;
		size++;
	}
}

template <typename dataType>
List<dataType>::List(const List& aList){
	size = aList.size;

	head = new Node;
	head -> data = aList.head->data;
	Node *cur = head;

	for(Node *cp_node = aList.head->next; cp_node != NULL ; cp_node = cp_node->next){
		cur -> next = new Node;
		cur = cur->next;
		cur -> data = cp_node -> data;
	}

	cur -> next = NULL;
}

template <typename dataType>
void List<dataType>::insert(int index, dataType data){
	if (index < 0){
		cout << "Negative index!!" << endl;
		return;
	}
	if (index > size){
		cout << "Extension is not supported!!" << endl;
		return;
	}
	//if insert head
	if(index == 0){
		Node *new_head = new Node;
		new_head -> next = head;
		new_head -> data = data;
		head = new_head;
	}//if insert into middle
	else{
		Node *prev = find(index-1);
		Node *node = new Node;
		node -> data = data;
		node -> next = prev -> next;
		prev -> next = node;
	}
	size ++;
}

template <typename dataType>
dataType List<dataType> :: extract(int index){
	if (index < 0 || index >= size){
		cout << "Wrong index value !!!" << endl;
		return 0;
	}
	Node* node = find(index);
	dataType ret_data = node -> data;
	remove(index);
	node = NULL;
	return ret_data;
}

template <typename dataType>
void List<dataType>::remove(int index){
	if(size == 0){
		cout << "No item to remove in list!!" << endl;
		return;
	}
	else if (index >= size || index < 0){
		cout << "No item with given index!!" << endl;
		return;
	}

	Node *cur;
	//if head ptr
	if(index ==  0){
		cur = head;
		head = head->next;
	}
	else{
		Node *prev = find(index-1);
		cur = prev->next;
		prev->next = cur->next;
	}
	cur->next = NULL;
	delete cur;
	cur = NULL;
	size --;
}


//REMOVE DUPLICATE ENTRIES INPLACE

template <typename dataType>
void List<dataType> :: removeDuplicates(){
	if(size < 2)
		return;

	Node* ind = head;
	Node* temp = NULL;
	for(Node* cur = head->next; cur != NULL; cur = cur->next){
		dataType value = cur -> data;
		temp = head;
		for(temp = head; temp != ind -> next; temp = temp->next ){
			if(value ==  temp -> data)
				break;
		}
		if (temp == ind->next){
			ind = ind->next;
			ind->data = value;
		}
	}
	// remove remaining list
	while(ind->next != NULL){
		size --;
		Node* temp = ind->next;
		ind -> next = temp -> next;
		temp -> next = NULL;
		delete temp;
		temp = NULL;
	}
}


//	REMOVE DUBLICATES USING A MAP FOR BOOKING

// template <typename dataType>
// void List<dataType> :: removeDuplicates(){
// 	if(size < 2)
// 		return;
// 	map<dataType, bool> booking;
// 	int cur_index = 0;
// 	for(Node* cur = head; cur != NULL; cur = cur->next){
// 		dataType value = cur -> data;
// 		if(!booking[value]){
// 			remove(cur_index);
//			size--;
// 		}
// 		else{
// 			booking[value] = true;
// 		}
// 	}
// }


//	REMOVE GIVEN NODE FROM THE LIST

template <typename dataType>
void List<dataType>::removeNode(Node *node){
	if(size == 0){
		cout << "List is empty!!" << endl;
		return;
	}
	if(node -> next == NULL){ // if node is the tail
		remove(getLength()-1);
	}else{
		Node * next_node = node -> next;
	    node -> data = next_node -> data;
	    // remove next_node
	    node -> next = next_node -> next;
	    next_node -> next = NULL;
	    delete next_node;
	    next_node = NULL;
	}
    size--;
}


//	Two list should have same size

template <typename dataType>
typename List<dataType>::Node* List<dataType> :: sumDigitsWithCarry(Node* num1,Node* num2){
    Node* newHead = new Node;
    Node* newCur = newHead;
    int carry = 0;
    for(Node * cur1 = num1, *cur2 = num2; cur1 != NULL && cur2 != NULL; cur1 = cur1 -> next, cur2 = cur2 -> next){
	    int val1 = cur1 -> data ;
	    int val2 = cur2 -> data;
	    int sum = val1 + val2;
	    int newDig = (sum % 10) + carry;

		newCur -> data = newDig;
		newCur -> next = new Node;
		newCur = newCur -> next;

		carry = (sum / 10) ? 1 : 0;
	}

	if(carry == 1){
		newCur -> data = 1;
		newCur -> next = NULL;
	}

	newCur = NULL;
	return newHead;
}



//Enter random int values in the range [0, max] to the begining
//of the linked list

template <typename dataType>
void List<dataType> :: randomIntFill(int item_num, int max){
	for(int i = 0; i < item_num; i ++){
		int next_val = rand() % max;
		insert(0,next_val);
	}
}

template <typename dataType>
dataType List<dataType>::retrieve(int index){
	if(index > size || index < 0){
		cout << "Wrong index value!!!" << endl;
		return;
	}
	Node *ptr = find(index);
	return ptr->data;
}

template <typename dataType>
typename List<dataType>::Node* List<dataType>::find(int index){
	Node *cur = head;
	for(int i = 0; i < index; i++){
		cur = cur->next;
	}
	return cur;
}

template <typename dataType>
void List<dataType>::printList(){
	for(Node *cur = head; cur != NULL; cur = cur->next){
		cout << cur->data << ' ';
	}
	cout << endl;
}

template <typename dataType>
bool List<dataType>::isEmpty(){
	return (size == 0) ? true : false;
}

template <typename dataType>
int List<dataType>::getLength(){
	return size;
}


int main(int argc, char **argv){
	List<int> list;
	list.insert(0,4);
	list.insert(1,5);
	list.insert(0,6);
	// list.insert(0,6);
	// list.insert(3,6);
	// list.insert(0,4);
	// list.insert(1,5);
	// list.insert(3,6);
	// list.insert(0,4);
	// list.insert(1,5);
	// list.insert(0,6);
	// list.insert(3,6);
	list.printList();
	cout <<  "List size : " << list.getLength() << endl;
	cout <<  "extracted item " << list.extract(0) << endl;

	list.printList();
	cout <<  "List size : " << list.getLength() << endl;

	// list.removeDuplicates();
	// list.printList();
	// cout <<  "List size : " << list.getLength() << endl;

	// list.removeNode(list.find(list.getLength()-1));
	// list.printList();

// here we have segmentation fault
	// List<int> list2(list.find(0));
	// list2.printList();

	//List<int> list2;
	// List<int> list2(list.find(0));
	// list2.printList();
	// List<int> list3(list2.sumDigitsWithCarry(list2.find(0), list.find(0)));
	// list3.printList();
	// cout <<  "List2 size : " << list2.getLength() << endl;
	// cout <<  "List3 size : " << list3.getLength() << endl;

	// list.randomIntFill(100,100);
	// list.printList();

	// list.remove(0);
	// list.remove(2);
	// list.printList();
	// cout <<  "List size : " << list.getLength() << endl;

	// List<int> list2(list);
	// cout <<  "List2 size : " << list2.getLength() << endl;
	return 0;
}



};
*/

/*namespace _v10 {
#ifndef LIST_H
#define LIST_H

#include <assert.h> // for assert
#include <memory>   // for std::unique_ptr

template<typename T>
class List
{
public:
  struct Node // All it's members are public by default.
  {
    Node(T aData, Node* aNext)
      : mData(aData)
      , mNext(aNext)
    {}

    ~Node() {}

    T mData;
    Node* mNext;
  };

  List();
  ~List();

  void Append(T aData);
  void Prepend(T aData);

  typedef void (*Callback)(Node* aNode);
  void Traverse(Callback aCallback);

private:
  // No need to use smart pointer in low-level data structure.
  // It's more efficient for managing memory on our own.
  Node* mCursor;
  Node* mHead;
};

// nullptr is introduced in C++11.
template<typename T>
List<T>::List()
  : mCursor(nullptr)
  , mHead(nullptr)
{
}

template<typename T>
List<T>::~List()
{
  for (mCursor = mHead ; mCursor != nullptr ;) {
    std::unique_ptr<Node> autoRelease(mCursor);
    // Update mCursor here instead of afterthought in for-loop,
    // in case mCursor is already released.
    mCursor = mCursor->mNext;
    // The memory chuck pointed by old mCursor will be destroyed
    // upon leaving the '}'.
  }
}

template<typename T>
void
List<T>::Append(T aData)
{
  Node* n = new Node(aData, nullptr);
  if (!mHead) { // the list is empty.
    assert(!mCursor);
    mHead = n;
  } else {
    assert(mCursor);
    mCursor->mNext = n;
  }
  mCursor = n;
}

template<typename T>
void
List<T>::Prepend(T aData)
{
  Node* n = new Node(aData, mHead);
  mHead = n;
  if (!mCursor) { // The list is empty before inserting value.
    mCursor = n;
  }
}

template<typename T>
void
List<T>::Traverse(Callback aCallback)
{
  for (Node* cur = mHead ; cur != nullptr ; cur = cur->mNext) {
    aCallback(cur);
  }
}

#endif // LIST_H
#include "list.h"
#include <iostream>

template<typename T>
void Print(T aData, bool aBreakline)
{
  std::cout << aData << ((aBreakline)? "->" : "\n");
}

void PrintInt(List<int>::Node* aNode)
{
  Print(aNode->mData, aNode->mNext);
}

void PrintFloat(List<float>::Node* aNode)
{
  Print(aNode->mData, aNode->mNext);
}

int main()
{
  int dataInt[6] = { 11, 22, 33, 44, 55, 66 };
  float dataFloat[6] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f };

  List<int> li;
  li.Prepend(dataInt[0]);
  li.Append(dataInt[1]);
  li.Append(dataInt[2]);
  li.Prepend(dataInt[3]);
  li.Append(dataInt[4]);
  li.Prepend(dataInt[5]);
  li.Traverse(PrintInt);

  List<float> lf;
  lf.Prepend(dataFloat[0]);
  lf.Append(dataFloat[1]);
  lf.Append(dataFloat[2]);
  lf.Prepend(dataFloat[3]);
  lf.Append(dataFloat[4]);
  lf.Prepend(dataFloat[5]);
  lf.Traverse(PrintFloat);

  return 0;
}
};
*/

/*namespace _v11 {
#include "list.h"
#include <assert.h> // for assert
// #include <stddef.h> // for NULL, size_t, they are already included in list.h
#include <stdlib.h> // for calloc, free
#include <string.h> // for memcpy

// Using "static" prevents these functions from being exposed outside.

static void
destroy(struct List* self)
{
  for (struct Node* cur = self->head ; cur != NULL ;) {
    struct Node* next = cur->next;
    free(cur->data);
    free(cur);
    cur = next;
  }
  self->head = self->cursor = NULL;
}

static void
append(struct List* self, void* data, size_t size) {
  struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
  assert(n);

  n->next = NULL;
  n->data = calloc(1, size);
  assert(n->data);
  memcpy(n->data, data, size);

  if (!self->head) { // The list is empty.
    assert(!self->cursor); // cursor = head = NULL now.
    self->head = n;
  } else {
    assert(self->cursor);
    self->cursor->next = n;
  }
  self->cursor = n;
}

static void
prepend(struct List* self, void* data, size_t size) {
  struct Node* n = (struct Node*)calloc(1, sizeof(struct Node));
  assert(n);

  n->next = self->head;
  n->data = calloc(1, size);
  assert(n->data);
  memcpy(n->data, data, size);

  self->head = n;
  if(!self->cursor) { // The list is empty before inserting value.
    self->cursor = n;
  }
}

static void
traverse(struct List* self, Callback func)
{
  for (struct Node* cur = self->head ; cur != NULL ; cur = cur->next) {
    func(cur);
  }
}

static struct List
new()
{
  return (struct List) {
    .head = NULL,
    .cursor = NULL,
    .destroy = (void*) &destroy,
    .append = (void*) &append,
    .prepend = (void*) &prepend,
    .traverse = (void*) &traverse
  };
}

const struct ListClass List = { // "ListProxy"
  .new = &new,
};
};
*/

/*namespace _v12 {
//Mahmoud Sami - HardCode Channel
//https://www.youtube.com/hardcode

class SinglyLinkedList{
private:
	struct Node{
		int data;
		Node* next;
	};
	Node* head = nullptr;
public:
	void append(int val){
		Node* newNode = new Node;
		newNode->data = val;
		newNode->next = nullptr;
		if (head == nullptr){
			head = newNode;
		}
		else{
			Node* temp = head;
			while (temp->next != nullptr){
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	void insert_at_pos(int val, int pos){
		Node* newNode = new Node;
		newNode->data = val;

		if (pos == 0){
			newNode->next = head;
			head = newNode;
			return;
		}

		Node* temp = head;
		for (int i = 0; i < pos - 1 && temp->next != nullptr; i++){
			temp = temp->next;
		}

		newNode->next = temp->next;
		temp->next = newNode;
	}

	void remove(int val){
		if (head == nullptr)
			return;

		Node* prev, *temp;
		prev = temp = head;

		if (temp->data == val){
			head = temp->next;
			delete temp;
			return;
		}

		while (temp != nullptr && temp->data != val){
			prev = temp;
			temp = temp->next;
		}

		if (temp == nullptr){
			return;
		}
		else{
			prev->next = temp->next;
			delete temp;
		}
	}

	void remove_at_pos(int pos){
		if (head == nullptr)
			return;

		if (pos == 0){
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		else{
			Node* temp = head;
			for (int i = 0; i < pos - 1 && temp->next != nullptr; i++){
				temp = temp->next;
			}

			if (temp->next == nullptr) // if the user enter a number bigger than LS size
				return;

			Node* toDeleted = temp->next;
			temp->next = temp->next->next;
			delete toDeleted;

		}
	}

	void reverse(){
		if (head == nullptr)
			return;
		Node* prev = nullptr;
		Node* curr = head;
		Node* next = nullptr;

		while (curr != nullptr){
			next = curr->next;
			curr->next = prev;
			prev = curr;
			curr = next;
		}

		head = prev;
	}

	void display(){
		Node* temp = head;
		while (temp != nullptr){
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		std::cout << std::endl;

	}

	~SinglyLinkedList(){
		Node* temp = head;
		while (head != nullptr){
			head = head->next;
			delete temp;
			temp = head;
		}
	}

};
};
*/

/*namespace _v13 {
#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
	friend class EmployeeList;
	string name;
	int age;
	int yearOfWork;
	Employee *next;
public:
	Employee(const string &, int, int);
	void print() const;
	const string& getName() const { return name; }
	~Employee() { cout << "Destructor of Employee" << endl; }
};

Employee::Employee(const string &newName, int a, int workYear)
{
	name = newName;
	age = a;
	yearOfWork = workYear;
	next = 0;
}

void Employee::print() const
{
	cout << "Name: " << name << ", Age: " << age << ", Year Of Work: " << yearOfWork << endl;
}

class EmployeeList
{
private:
	Employee *head;
public:
	EmployeeList() {	head = 0; };
	bool append(const string &, int, int);
	bool del(const string &);
	void print() const;
	~EmployeeList();
};

bool EmployeeList::append(const string &n, int a, int workYear)
{
	Employee *previous, *current, *newEmployee;
	newEmployee = new Employee(n, a, workYear);
	if (!newEmployee)
		return false;

	if (head)
	{
		previous = head;
		current = head->next;
		while (current)
		{
			previous = current;
			current = current->next;
		}
		previous->next = newEmployee;
	} else {
		head = newEmployee;
	}

	return true;
}

bool EmployeeList::del(const string &n)
{
	Employee *previous, *current;
	if (head)
	{
		if (n == head->getName())
		{
			previous = head;
			head = head->next;
			delete previous;
			return true;
		}
		previous = head;
		current = head->next;
		while ( current && ( n != current->getName() ) )
		{
			previous = current;
			current = current->next;
		}
		if (current == 0)
			return false;

		previous->next = current->next;
		delete current;
		return true;
	}
	else {
		return false;
	}
}

void EmployeeList::print() const
{
	Employee *tempPtr;
	if (head)
	{
		tempPtr = head;
		while (tempPtr)
		{
			tempPtr->print();
			tempPtr = tempPtr->next;
		}
	}
	else {
		cout << "The list is empty" << endl;
	}
}

EmployeeList::~EmployeeList()
{
	Employee *temp;
	while (head)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

int main()
{
	EmployeeList list;

	list.print();
	list.append("Employee 1", 25, 1);
	list.append("Employee 2", 32, 4);
	list.append("Employee 3", 31, 5);
	list.print();

	if (!list.del("Employee 6"))
		cout << "Employee x not found" << endl;

	if (!list.del("Employee 2"))
		cout << "Employee 2 not found" << endl;

	list.print();

	return 0;
}
};
*/

/*namespace _v14 {
// Linkedlist implementation using Classes in C++
#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
};

class LinkedList{
public:
    LinkedList() { // constructor
        head = NULL;
    }
    ~LinkedList() {}; // destructor
    void addNode(int val);
    void reverseList();
    void display();
private:
    Node* head;
};

// function to add node to a list
void LinkedList::addNode(int val) {
    Node* newnode = new Node();
    newnode->data = val;
    newnode->next = NULL;
    if (head == NULL) {
        head = newnode;
    }
    else {
        Node* temp = head; // head is not NULL
        while (temp->next != NULL) {
            temp = temp->next; // go to end of list
        }
        temp->next = newnode; // linking to newnode
    }
}

// reverse Linked List
void LinkedList::reverseList() {
    Node* temp = head;
    Node* nextnode = NULL;
    Node* revnode = NULL;
    while (temp != NULL) {
        head = temp;
        nextnode = temp->next;
        temp->next = revnode;
        revnode = temp;
        temp = nextnode;
    }
}

void LinkedList::display() {
    if (head == NULL) {
        cout << "List is empty!" << endl;
    }
    else {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}

int main() {
    LinkedList* list = new LinkedList();
    list->addNode(100);
    list->addNode(200);
    list->addNode(300);
    list->addNode(400);
    list->addNode(500);
    cout << "Linked List data" << endl;
    list->display();
    list->reverseList();
    cout << "Reversed Linked List data" << endl;
    list->display();
    delete list;
    return 0;
}



};
*/

/*namespace _v15 {
// linkedlist.cpp

#include <iostream>

using namespace std;

struct node {
	int data;
	struct node *next;
};

void insert(struct node **head, int data){
	struct node *n = (struct node*) malloc(sizeof(struct node));
	n->data = data;
	n->next = *head;
	*head = n;
}

void reverse(struct node **head){
	struct node *prev = NULL;
	struct node *curr = *head;
	struct node *next;
	while (curr != NULL){
		next = curr->next;

		curr->next = prev;
		prev = curr;

		curr = next;
	}
	*head = prev;
}

void printList(struct node *head){
	struct node *temp = head;
	while (temp != NULL){
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << endl;
}

int main(int argc, char *argv[]){

	struct node *head = NULL;

	insert(&head, 2);
	insert(&head, 42);
	insert(&head, 69);
	insert(&head, 34);
	insert(&head, 55);

	cout << " ---- Linked List 4 ---- " << endl;

	printList(head);

	cout << "reversed: " << endl;

	reverse(&head);
	printList(head);

	return 0;
}
};
*/

/*namespace _v16 {
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct node
{
    int value;
    struct node* next;
    struct node* prev;
};
struct node* head;
struct node* tail;

void init()
{
    head=NULL;
    tail=NULL;
}

void insertFirst(int element)
{
    struct node* newItem;
    newItem=new node;
    if(head==NULL)
    {
        head=newItem;
        newItem->prev=NULL;
        newItem->value=element;
        newItem->next=NULL;
        tail=newItem;
    }
    else
    {
        newItem->next=head;
        newItem->value=element;
        newItem->prev=NULL;
        head->prev=newItem;
        head=newItem;
    }
}

void insertLast(int element)
{
    struct node* newItem;
    newItem=new node;
    newItem->value=element;
    if(head==NULL)
    {
        head=newItem;
        newItem->prev=NULL;
        newItem->next=NULL;
        tail=newItem;
    }
    else
    {
        newItem->prev=tail;
        tail->next=newItem;
        newItem->next=NULL;
        tail=newItem;
    }
}

void insertAfter(int old, int element)
{
    struct node* newItem;
    newItem=new node;
    struct node* temp;
    temp=head;
    if(head==NULL)
    {
        cout<<"could not insert"<<endl;
        return;
    }
    if(head==tail)
    {
        if(head->value!=old)
        {
            cout<<"could not insert"<<endl;
            return;
        }
        newItem->value=element;
        head->next=newItem;
        newItem->next=NULL;
        head->prev=NULL;
        newItem->prev=head;
        tail=newItem;
        return;
    }
    if(tail->value==element)
    {
        newItem->next=NULL;
        newItem->prev=tail;
        tail->next=newItem;
        tail=newItem;
        return;
    }
    while(temp->value!=old)
    {
        temp=temp->next;
        if(temp==NULL)
        {
            cout<<"Could not insert"<<endl;
            cout<<"element not found"<<endl;
            return;
        }
    }

    newItem->next=temp->next;
    newItem->prev=temp;
    newItem->value=element;
    temp->next->prev=newItem;
    temp->next=newItem;
}

void deleteFirst()
{
    if(head==NULL)
    {
        return;
    }
    if(head==tail)///one element in the list
    {
        struct node* cur;
        cur=head;
        head=NULL;
        tail=NULL;
        delete cur;
        return;
    }
    else
    {
        struct node* cur;
        cur=head;
        head=head->next;
        head->prev=NULL;
        delete cur;
    }
}

void deleteLast()
{
    if(head==NULL) return;
    if(head==tail)
    {
        struct node* cur;
        cur=head;
        head=NULL;
        tail=NULL;
        delete cur;
        return;
    }
    else
    {
        struct node* cur;
        cur=tail;
        tail=tail->prev;
        tail->next=NULL;
        delete cur;
    }
}
void deleteItem(int element)
{
    struct node* temp;
    temp=head;
    if(head==tail)
    {
        if(head->value!=element)
        {
            cout<<"could not delete"<<endl;
            return;
        }
        head=NULL;
        tail=NULL;
        delete temp;
        return;
    }
    if(head->value==element)
    {
        head=head->next;
        head->prev=NULL;
        delete temp;
        return;
    }
    else if(tail->value==element)
    {
        temp=tail;
        tail=tail->prev;
        tail->next=NULL;
        delete temp;
        return;
    }
    while(temp->value!=element)
    {
        temp=temp->next;
        if(temp==NULL)
        {
            cout<<"element not found"<<endl;
            return;
        }
    }
    temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
    delete temp;
}

struct node* searchItem(int element)
{
    struct node* temp;
    temp=head;
    while(temp!=NULL)
    {
        if(temp->value==element)
        {
            return temp;
            break;
        }
        temp=temp->next;
    }
    return NULL;
}

void printList()
{
    struct node* temp;
    temp=head;
    while(temp!=NULL)
    {
        printf("%d->",temp->value);
        temp=temp->next;
    }
    puts("");
}

void printReverse()
{
    struct node* temp;
    temp=tail;
    while(temp!=NULL)
    {
        cout<<temp->value<<"->";
        temp=temp->prev;
    }
    cout<<endl;
}

void makereverse()
{
    struct node* prv=NULL;
    struct node* cur=head;
    struct node* nxt;
    while(cur!=NULL)
    {
        nxt=cur->next;
        cur->next=prv;
        prv=cur;
        cur=nxt;
    }
    head=prv;
}

int dltfrst()
{
    if(head==NULL)
    {
        return 0;
    }
    int prev;
    prev=head->value;
    if(head==tail)///one element in the list
    {
        struct node* cur;
        cur=head;
        head=NULL;
        tail=NULL;
        delete cur;
        return prev;
    }
    else
    {
        struct node* cur;
        cur=head;
        head=head->next;
        head->prev=NULL;
        delete cur;
        return prev;
    }
}
int dltlast()
{
    if(head==NULL) return 0;
    int prev;
    prev=tail->value;
    if(head==tail)
    {
        struct node* cur;
        cur=head;
        head=NULL;
        tail=NULL;
        delete cur;
        return prev;
    }
    else
    {
        struct node* cur;
        cur=tail;
        tail=tail->prev;
        tail->next=NULL;
        delete cur;
        return prev;
    }
}
void leftRotate(int x)
{
    for(int i=0;i<x;i++)
    {
        int a=dltfrst();
        insertLast(a);
    }
}
void rightRotate(int x)
{
    for(int i=0;i<x;i++)
    {
        int a=dltlast();
        insertFirst(a);
    }
}

int main()
{
    init();

    int choice;
    while(1)
    {
        printf("1.InsertFirst 2. InsertLast 3. InsertAfter 4.DeleteFirst 5. DeleteLast\n");
        printf("6.SearchItem 7. PrintList 8. ReversePrint 9. DeleteItem \n");
        printf("10. Left Rotate 11. Right Rotate 12. Exit  13.Make reverse\n");
        cin>>choice;
        if(choice==1)
        {
            int element;
            cout<<"Enter element_";
            cin>>element;
            insertFirst(element);
            printList();
        }
        else if(choice==2)
        {
            int element;
            cout<<"Enter element_";
            cin>>element;
            insertLast(element);
            printList();
        }
        else if(choice==3)
        {
            int old,newitem;
            cout<<"Enter Old Item_";
            cin>>old;
            cout<<"Enter new Item_";
            cin>>newitem;
            insertAfter(old,newitem);
            printList();
        }
        else if(choice==4)
        {
            deleteFirst();
            printList();
        }
        else if(choice==5)
        {
            deleteLast();
            printList();
        }
        else if(choice==6)
        {
            int item;
            cout<<"Enter Item to Search_";
            cin>>item;
            struct node* ans=searchItem(item);
            if(ans!=NULL) cout<<"FOUND "<<ans->value<<endl;
            else cout<<"NOT FOUND"<<endl;
        }
        else if(choice==7)
        {
            printList();
        }
        else if(choice==8)
        {
            printReverse();
        }
        else if(choice==9)
        {
            int element;
            cin>>element;
            deleteItem(element);
            printList();
        }
        else if(choice==10)
        {
            int x;
            cin>>x;
            leftRotate(x);
            printList();
        }
        else if(choice==11)
        {
            int x;
            cin>>x;
            rightRotate(x);
            printList();
        }
        else if(choice==12)
        {
            break;
        }
        else if(choice==13)
        {
            makereverse();
        }
    }
return 0;
}
};
*/

/*namespace _v17 {
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	first = NULL;
	last = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Node<T>* temp = first;
	while(temp != NULL)
	{
		temp = temp->next;
		delete(first);
		first = temp;
	}
}

template <class T>
void LinkedList<T>::insertAtBack(T valueToInsert)
{
	Node<T>* newNode;
	newNode->val = valueToInsert;
	newNode->next = NULL;

	Node<T>* temp = first;

	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = newNode;
	}
	else
	{
		first = newNode;
	}
}

template <class T>
bool LinkedList<T>::removeFromBack()
{
	if (first == NULL && last == NULL) {return false;}

	if (first == last)
	{
		cout<<"First is equal to Last."<<endl;
		delete(first);
		first = last = NULL;
		return true;
	}

	else
	{
		Node<T>* temp = first;
		int nodeCount = 0;

		while (temp != NULL)
		{
			nodeCount = nodeCount + 1;
			temp = temp->next;
		}

		Node<T>* temp2 = first;

		for(int i = 1; i < (nodeCount - 1); i++)
		{
			temp2 = temp2->next;
		}

		cout << temp2->val<<endl;
		delete(temp2->next);

		last = temp2;
		last->next = NULL;

		return true;
	}
}

template <class T>
void LinkedList<T>::print()
{
	Node<T>* temp = first;

	if (temp == NULL)
	{
		cout<<"";
	}

	if (temp->next == NULL)
	{
		cout<<temp->val;
	}
	else
	{
		while (temp != NULL)
		{
			cout<< temp->val;
			temp = temp->next;
			cout<< ",";
		}
	}
}

template <class T>
bool LinkedList<T>::isEmpty()
{
	if (first == NULL && last == NULL) {return true;}
	else {return false;}
}

template <class T>
int LinkedList<T>::size()
{
	if (first == NULL && last == NULL) {return 0;}

	Node<T>* temp = first;
	int nodeCounter = 0;

	while (temp != NULL)
	{
		nodeCounter = nodeCounter + 1;
		temp = temp->next;
	}
	return nodeCounter;
}

template <class T>
void LinkedList<T>::clear()
{
	Node<T>* temp = first;
	while(temp != NULL)
	{
		temp = temp->next;
		first = temp;
		delete(temp);
	}
}

template <class T>
void LinkedList<T>::insertAtFront(T valueToInsert)
{
	Node<T>* newNode;

	newNode->val = valueToInsert;

  	 if(first == NULL)
   	{
   		first = newNode;
   	}
   	else
   	{
   		newNode->next = first;
   		first = newNode;
   	}

}

template <class T>
bool LinkedList<T>::removeFromFront()
{
	if (first == NULL && last == NULL) {return false;}

	else
	{
		Node<T>* temp;

		temp = first;
		first = first->next;

		delete(temp);

		return true;
	}
}

template <class T>
T& LinkedList<T>::firstNum()
{
	return first->val;
}
};
*/

/*namespace _v18 {

//Doubly linked lists
//Doubly linked list is a type of data structure that is made up of so called objects
//that are created using self referential structures. Each of these nodes contain three
//attributes, namely the value and the reference to the next list object and the reference
//to the previous list object.
//
//In this exercise you will create a doubly linked list, which exposes 4 methods:
//
//    push_back(): add values to the end of the list
//    push_front(): add values to the beginning to the list
//    pop_back(): delete values from the end of the list
//    pop_front(): delete values from the front of the list
//
//Also, you will implement a helper function, empty(), which returns whether or not
//the list has any nodes.

#include <iostream>
#include <assert.h>
#include <string>

template<class T>
class Node {
    public:
        Node(T val, Node *prev_node, Node *next_n):
            value(val), previous_node(prev_node),next_node(next_n){}
        T value;
        Node *previous_node;
        Node *next_node;
};

template<class T>
class List{
    public:
        List(): head(nullptr), tail(nullptr){}
        ~List();
        void PushFront(T);
        void PushBack(T);
        T PopFront();
        T PopBack();
        bool Empty() const { return (head == nullptr);}
        int Size() const;
    private:
        Node<T> *head;
        Node<T> *tail;
};

template<class T>
List<T>::~List(){
    while ( head != nullptr ){
        Node<T> *tmp =  head;
        head = head->next_node;
        delete tmp;
    }

}


template<class T>
void List<T>::PushBack(T val){

     tail = new Node<T>(val, tail, nullptr);

     if (head == nullptr){
        head = tail;
     }else{
        tail->previous_node->next_node = tail;
     }

}

template<class T>
void List<T>::PushFront(T val){
    head = new Node<T>(val, nullptr, head);

    if (tail == nullptr){
        tail = head;
    }else{
        head->next_node->previous_node = head;
    }
}

template<class T>
int List<T>::Size() const {
    int count = 0;
    Node<T> *tmp = head; // copy head to tmp
    std::string rst = "";
    while(tmp !=nullptr){
        rst = rst +  std::to_string(tmp->value) +", ";
        tmp = tmp->next_node;
        count++;
    }
    std::cout << rst << std::endl;
    return count;
}



template<class T>
T List<T>::PopFront() {
    if (List::Empty())
        throw("Cannot List::PopBack() when List::Empty()");

    Node<T> *tmp = List<T>::head;
    T value = tmp->value;

    head = head ->next_node;

    if(head != nullptr){
        head->previous_node = nullptr;
    }else{
        tail = nullptr;
    }

    delete tmp;
    return value;

}

template<class T>
T List<T>::PopBack(){

    if (List::Empty())
        throw("Cannot List::PopBack() when List::Empty()");

    Node<T> *tmp = tail;
    T value = tail->value;
    tail = tail->previous_node;

    if (tail != nullptr){
        tail->next_node = nullptr;
    }else{
        head = nullptr;
    }

    delete tmp;
    return value;

}




int main() {
  // Sanity test
  List<int> list1;

  list1.PushBack(9);
  std::cout << "Size() = " << list1.Size() << std::endl;
  assert(list1.Size() == 1);

  // Deeper test
  List<int> list2;
  list2.PushFront(9);
  list2.PushBack(10);
  assert(list2.Size() == 2);

  list2.PushBack(15);
  list2.PushFront(2);
  std::cout << "Size() = " << list2.Size() << std::endl;

  assert(list2.PopFront() == 2);
  std::cout << "list2.PopFront() = " << list2.PopFront() << std::endl;
  std::cout << "Size() = " << list2.Size() << std::endl;


  assert(list2.PopBack() == 15);
  assert(list2.Size() == 1);

}

};
*/

/*namespace _v19 {
// doublelinkedlist.cpp

#include <iostream>

using namespace std;


class LinkedList {
  // Struct inside the class LinkedList
  // This is one node which is not needed by the caller. It is just
  // for internal work.
  struct Node {
    int x;
    Node *succ;
    Node *pred;
  };

public:
  // constructor
  LinkedList(){
    head = NULL; // set head to NULL
  }

  // This prepends a new value at the beginning of the list
  void addValue(int val){
    Node *n = new Node();   // create new Node
    n->x = val;             // set value
    n->succ = head;         // make the node point to the next node.
    n->pred = tail
    //  If the list is empty, this is NULL, so the end of the list --> OK
    head = n;               // last but not least, make the head point at the new node.
  }
  // returns the first element in the list and deletes the Node.
  // caution, no error-checking here!
  int popValue(){
    Node *n = head;
    int ret = n->x;

    head = head->next;
    delete n;
    return ret;
  }

  // private member
private:
  Node *head; // this is the private member variable. It is just a pointer to the first Node


};
};
*/

/*namespace _v20 {
#include<iostream>
#include<stdlib.h>
using namespace std;

struct node
    {
    int info;
    struct node *next;
    struct node *prev;
    }*head=NULL,*tail=NULL;


//create dummy node i.e. empty node with node value n
struct node *create(int n)
    {
    struct node *temp=new struct node;

    temp->info=n;
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
    }


//add node at first with info n
void add_f(int n)
    {
    node *ne;
    ne=create(n);
    if(head==NULL)
        tail=ne;
    ne->prev=NULL;
    ne->next=head;
    head=ne;
    if(ne->next!=NULL)
        ne->next->prev=ne;
    cout << "\t~ node added at first" << endl;
    }


//add node at last with info n
void add_l(int n)
    {
    if(head==NULL)
        {
        add_f(n);
        return;
        }
    node *ne;
    ne=create(n);
    ne->next=NULL;
    ne->prev=tail;
    tail->next=ne;
    tail=ne;
    cout << "\t~ node added at last" << endl;
    }


//add node with info n after node having info x
void add_i(int x,int n)
    {
    if(head==NULL)
        {
        cout << "\t~ list is empty" << endl;
        return;
        }
    node *t=tail;
    node *h=head;
    while(t->info!=x && h->info!=x)
        {
        if(t==h)
            break;
        else if(h->next==t)
            break;
        t=t->prev;
        h=h->next;
        }
    if(t->info==x)
        {
        cout << "\t~ node added after node having info " << x << endl;
        if(t->next==NULL)
            add_l(n);
        else
            {
            node *ne;
            ne=create(n);
            ne->next=t->next;
            ne->prev=t;
            t->next=ne;
            ne->next->prev=ne;
            }
        }
    else if(h->info==x)
        {
        cout << "\t~ node added after node having info " << x << endl;
        node *ne;
        ne=create(n);
        ne->next=h->next;
        ne->prev=h;
        h->next=ne;
        ne->next->prev=ne;
        }
    else
        cout << "\t~ no such node present" << endl;
    }


//delete first node
void del_f()
    {
    if(head==NULL)
        {
        cout << "\t~ list is empty" << endl;
        return;
        }
    head=head->next;
    if(head!=NULL)
        head->prev=NULL;
    cout << "\t~ first node deleted" << endl;
    }


//delete last node
void del_l()
    {
    if(head==NULL)
        {
        cout << "\t~ list is empty" << endl;
        return;
        }
    tail=tail->prev;
    if(tail==NULL)
        head=NULL;
    else
        tail->next=NULL;
    cout << "\t~ last node deleted" << endl;
    }

//delete node with info x
void del_i(int x)
    {
    if(head==NULL)
        {
        cout << "\t~ list is empty" << endl;
        return;
        }
    node *t=tail;
    node *h=head;
    while(t->info!=x && h->info!=x)
        {
        if(t==h)
            break;
        else if(h->next==t)
            break;
        t=t->prev;
        h=h->next;
        }
    if(t->info==x)
        {
        cout << "\t~ node deleted having info " << x << endl;
        if(t->next==NULL)
            del_l();
        else
            {
            t->prev->next=t->next;
            t->next->prev=t->prev;
            }
        }
    else if(h->info==x)
        {
        cout << "\t~ node deleted having info " << x << endl;
        if(h->prev==NULL)
            del_f();
        else
            {
            h->prev->next=h->next;
            h->next->prev=h->prev;
            }
        }
    else
        cout << "\t~ no such node present" << endl;

    }


//print linked list
void print()
    {
    if(head==NULL)
        {
        cout << "\t~ list is empty" << endl;
        return;
        }
        node *n=head;
        cout << "----------------- LIST ------------------" << endl;
        cout << "info\t\tprev.\t\taddress\t\tnext" << endl;
        cout << "-----------------------------------------" << endl;
    while(n->next!=NULL)
        {
        cout << n->info << "\t\t" << n->prev << "\t" << n << "\t" << n->next << endl;
        n=n->next;
        }
    cout << n->info << "\t\t" << n->prev << "\t" << n << "\t" << n->next << endl;
    }

int main()
{
int a,n,x;
while(1)
    {
    cout << "*********** MAIN MENU ***********" << endl;
    cout << "1. insert node" << endl << "2. delete node" << endl << "3. print list" << endl << "4. exit :- ";
    cin >> a;
    switch(a)
        {
        case 1:
            cout << "--------------- INSERT ---------------" << endl;
            cout << "1. at first or create" << endl << "2. at last" << endl << "3. intermediate" << endl << "4. exit to main menu :- ";
            cin >> a;
            switch(a)
                {
                case 1:
                    cout << "\t~ enter info :- ";
                    cin >> n;
                    add_f(n);
                    break;
                case 2:
                    cout << "\t~ enter info :- ";
                    cin >> n;
                    add_l(n);
                    break;
                case 3:
                    cout << "\t~ enter info of node after which u want to add node :- ";
                    cin >> x;
                    cout << "\t~ enter info of new node :- ";
                    cin >> n;
                    add_i(x,n);
                    break;
                case 4:
                    break;
                default:
                    cout << "\t## enter appropriate option ##" << endl;
                }
            break;
        case 2:
            cout << "--------------- DELETE ---------------" << endl;
            cout << "1. first" << endl << "2. last" << endl << "3. intermediate" << endl << "4. exit to main menu :- ";
            cin >> a;
            switch(a)
                {
                case 1:
                    del_f();
                    break;
                case 2:
                    del_l();
                    break;
                case 3:
                    cout << "\t~ enter info of node which u want to delete :- ";
                    cin >> x;
                    del_i(x);
                    break;
                case 4:
                    break;
                default:
                    cout << "\t## enter appropriate option ##" << endl;
                }
            break;
        case 3:
            print();
            break;
        case 4:
            cout << "*********** EXIT ***********" << endl;
            exit(0);
            break;
        default:
            cout << "## enter appropriate option ##" << endl;
        }
    }
}

};
*/

/*namespace _v21 {
// By your BOI : Yahia B
// feel free to take whatever you would like

#ifndef DLL_H
#define DLL_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

template <class T>
struct Node {
 public:
  T key;
  Node<T>* next;
  Node<T>* prev;

  Node(const T& key) {
    this->key = key;
    this->next = nullptr;
    this->prev = nullptr;
  };

  void printData() { cout << key << " "; };
  void print() {
    cout << " * " << key << ": [addr: " << this << " next: " << this->next
         << " prev: " << this->prev << "]  ";
  };
};

template <class T>
class DoubleLinkedList {
 public:
  // Constructor for Doubly Linked List
  DoubleLinkedList();

  // Destructor for Doubly Linked List
  ~DoubleLinkedList();

  // Searches for a node starting at a location and returns node if found, Else:
  // Returns location of where it should be to ensure ascending order
  Node<T>* search(Node<T>* location, T key);

  // Inserts a node at a specific location
  Node<T>* insert(Node<T>* location, T key);

  // Insert Nodes into ordered LL from a vector
  void insert_from_vector(vector<T> v);

  // Insert Node with key N to maintain Ordered Linked List
  void insert(T N);

  // Print all of Linked List Data
  void printData();

  // Delete Node with key N
  void Delete(T N);

  // Returns total number of nodes currently in linked list
  int Count_Nodes();

  Node<T>* head; // Head of Linked List

  int Totalnumberofnodes; // Total number of nodes currently in linked list
};

// Constructor for linked list
template <class T>
DoubleLinkedList<T>::DoubleLinkedList() {
  Totalnumberofnodes = 0;
  head = nullptr;  // construct a linked list with a null head
}

// destructor for linked list
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  Node<T>* temp = head;
  while (temp != nullptr) {  // keep iterating until head is null
    temp = head->next;
    delete head;
    head = temp;
  }
  delete head;  // delete head
}

template <class T>
void DoubleLinkedList<T>::insert_from_vector(vector<T> v) {
  for (int i = 0; i != v.size(); i++) {
    cout << "V [i] is : " << v[i] << endl;
    insert(v[i]);
  }
  return;
}

template <class T>
int DoubleLinkedList<T>::Count_Nodes() {
  return Totalnumberofnodes;
}

template <class T>
void DoubleLinkedList<T>::insert(T data) {
  Totalnumberofnodes++;
  Node<T>* N = new Node<T>(data);
  Node<T>* pt = new Node<T>(data);
  N->next = nullptr;
  N->prev == nullptr;
  pt = head;
  // Case 1 : Empty LL
  if (head == nullptr) {
    head = N;
    return;
  }

  // Case 2 : Insert to Head
  if (N->key < head->key) {
    N->next = head;
    head->prev = N;
    head = N;
    return;
  }

  while (pt->next != nullptr && N->key >= pt->next->key) {
    pt = pt->next;
  }

  // Case 2 : Insert to tail
  if (pt->next == nullptr) {
    pt->next = N;
    N->prev = pt;
    N->next = nullptr;
    return;
  }
  // Case 3 : Insert to somewhere in the middle
  else {
    N->prev = pt;
    N->next = pt->next;
    pt->next = N;
    N->next->prev = N;
    return;
  }
}

// Delete Node From LL
template <class T>
void DoubleLinkedList<T>::Delete(T key) {
  Totalnumberofnodes--;
  Node<T>* temp = new Node<T>(key);
  temp = head;

  // Case 1:Node key is Head
  if (key == head->key) {
    Node<T>* NewHead = head->next;
    NewHead->prev = nullptr;
    delete (head);
    head = NewHead;
    return;
  }

  while (temp != nullptr && temp->key != key) {
    temp = temp->next;
  }

  // Case 2:Node doesn't exist
  if (temp == nullptr) {
    Totalnumberofnodes++;
    cout << " Error: Node " << key << " Does Not Exist, Cannot Be Deleted"
         << endl;
    return;
  }

  Node<T>* Next = temp->next;
  Node<T>* Prev = temp->prev;

  // Case 3: Node is Tail
  if (Next == nullptr) {
    Node<T>* NewTail = Prev;
    delete (Prev->next);
    Prev->next = nullptr;
    return;
  }
  // Case 4: Node is somewhere in between
  else {
    Prev->next = Next;
    delete (Next->prev);
    Next->prev = Prev;
  }
}

bool insertright = false;  // bool to tell whether you have reached end of list
                           // and need to insert right or left
template <class T>
Node<T>* DoubleLinkedList<T>::search(Node<T>* location,
                                     T key) {  // Search for node or correct
                                               // spot to put node by checking
                                               // the location, location prev,
                                               // location next
  Node<T>* temp = new Node<T>(key);
  bool found = false;  // bool to say whether you found right spot or not

  if (location == nullptr) {
    return location;
  }  // if list is empty then return location
  if (location->prev == nullptr && key < location->key) {
    return location;
  }  // if starting at beggining of list and need to append to start return
     // location.
  while (found == false) {  // while not found
    if (location->prev == nullptr && location->next != nullptr &&
        key > location->key) {  // if the previous node is a null and key is
                                // larger than first element, iterate one
                                // element
      location = location->next;
    } else if (location->next == nullptr &&
               key > location->key) {  // if the previous node is a null and key
                                       // is larger than first element, iterate
                                       // one element
      insertright = true;
      return location;
    }  // iterate one element
    else if (key < (location->key) && key < (location->prev->key) &&
             (location->prev) != nullptr) {  // if key is less than the location
                                             // and prev location then iterate
                                             // back
      location = location->prev;
    } else if (key > location->key && key > location->prev->key &&
               location->prev != nullptr &&
               location->next != nullptr) {  // if key is greater than location
                                             // and key is greater than
                                             // location->prev iterate right
      location = location->next;
    } else if (key > location->key && key > location->prev->key &&
               location->prev != nullptr &&
               location->next == nullptr) {  // if key is greater than location
                                             // and key is greater than
                                             // location-> but we are at end of
                                             // list, return location and set
                                             // insertright bool as true
      insertright = true;
      return location;
    } else if (key > location->prev->key && key <= location->key &&
               location->prev != nullptr) {  // if key is greater than
                                             // location-> prev and key is less
                                             // than location key then its in
                                             // the right spot
      found = true;
      return location;
    }
  }
}
// insert function
template <class T>
Node<T>* DoubleLinkedList<T>::insert(Node<T>* location, T key) {
  Totalnumberofnodes++;

  Node<T>* temp = new Node<T>(key);  // make new node with key
  temp->key = key;
  temp->next = nullptr;
  temp->prev = nullptr;

  if (location == nullptr) {  // if location is null, its an empty list and
                              // youre going to create the list with the new
                              // node
    head = temp;
    head->prev = nullptr;
    head->next = nullptr;
    return location;

  } else if (location != nullptr && location->prev != nullptr &&
             insertright == false)  // if its in the middle/end of the list and
                                    // yo dont need to insert right, insert left
  {
    temp->next = location;
    location->prev->next = temp;
    temp->prev = location->prev;
    location->prev = temp;
    return (location);

  } else if (location != nullptr && location->prev != nullptr &&
             insertright == true)  // if its at the end of the list and you need
                                   // to insert right, insert right
  {
    insertright = false;
    temp->next = nullptr;
    temp->prev = location;
    location->next = temp;
    return (location);

  } else if (location != nullptr && location->prev == nullptr &&
             insertright == false)  // if the node you start at exists and the
                                    // previous node is a null then you are at
                                    // the beggining and inserting at the
                                    // beginning
  {
    temp->prev = nullptr;
    temp->next = location;
    location->prev = temp;
    head = temp;
    return location;
  } else if (location != nullptr && location->prev == nullptr &&
             insertright == true)  // if the node you start at exists and the
                                   // previous node is a null then you are at
                                   // the beggining and inserting at the
                                   // beginning
  {
    insertright = false;
    temp->next = nullptr;
    temp->prev = location;
    location->next = temp;
    return location;
  }
}

// Print linked list key
template <class T>
void DoubleLinkedList<T>::printData() {
  cout << "Current Number of Nodes : " << Count_Nodes() << endl;
  if (head == nullptr) {
    cout << "Linked list is empty" << endl;
    ;
    return;
  }

  head->printData();

  if (head->next == nullptr) {
    cout << endl;
    return;
  }

  Node<T>* currNode = head->next;
  Node<T>* prevNode = head;

  while (currNode->next != nullptr) {
    currNode->printData();
    prevNode = currNode;
    currNode = currNode->next;
  }

  currNode->printData();
  cout << endl;
}

#endif

};
*/


#endif // LINKEDLISTDTS_HPP_INCLUDED
