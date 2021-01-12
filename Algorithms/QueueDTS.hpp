#ifndef QUEUEDTS_HPP_INCLUDED
#define QUEUEDTS_HPP_INCLUDED

/*namespace _v4 {

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
using std::strncpy;
using std::strlen;

QueueItem::QueueItem( char *pData, int id)
    : _itemId(id)
{
    strncpy( _data, pData, strlen( pData ) +1 );
    _pNext = NULL;
}   // end QueItem constructor

void QueueItem::setNext( QueueItem *pItem )
{
    _pNext = pItem; // assign param to _pNext member
}   // end function setNext

QueueItem* QueueItem::getNext() const
{
    return _pNext;
}   // end function getNext

int QueueItem::getId() const
{
    return _itemId;
}   // end function getId

const char* QueueItem::getData() const
{
    return _data;
}   // end function getData()
// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: Queue1.h

class QueueItem;    // forward class description

#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
public:
    Queue();                    // ctor inits a new empty Queue
    ~Queue();                   // dtor erases any remaining QueueItems
    void addItem(char *pData);
    void removeItem();
    void print();
    void erase();
private:
    QueueItem *_pHead;      // always points to first QueueItem in the list
    QueueItem *_pTail;      // always points to last QueueItem in the list
    int _itemCounter;       // always increasing for a unique id to assign to each new QueueItem
};   // end definition class Queue

#endif
// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: Queue1.cpp

#include <iostream>
using std::cout;
using std::endl;


// constructor
Queue::Queue()
{
    QueueItem* _pNext = _pHead = _pTail = 0;
    _itemCounter = 0;
} // end ctor

// destructor
Queue::~Queue()
{
    // in text Fig 9.12 this just does some couts, i think it's automatic
}   // end dtor

// add a new item to the Queue
void Queue::addItem(char *pData)
{
    // dynamically create and init a new QueueItem object
    QueueItem *pItem = new QueueItem(pData, ++_itemCounter);

    if ( 0 == _pHead )          // check for empty queue
        _pHead = _pTail = pItem;
    else
    {
        _pTail->setNext(pItem); // set pTail's item to point at the newest item (link it on the end of the queue)
        _pTail = pItem;         // set pTail to point to the newest item on the end
    }
    QueueItem* _pNext = 0;
}   // end function addItem

// removes the head item from the queue, FIFO
void Queue::removeItem()
{
    if ( _pTail == 0 && _pHead == 0 )
    {
        // empty body
    }
    else
    {
        QueueItem* _pItem = _pHead->getNext();
        delete _pHead;
        _pHead = _pItem;
    }

}   // end function removeItem

// Print the entire Queue
void Queue::print()
{
    QueueItem* _pItem = _pHead;
    while ( _pItem != NULL )
    {
    cout << _pItem->getId() << endl;
    cout << _pItem->getData() << endl;
    _pItem = _pItem->getNext();
    }
}   // end function print

void Queue::erase()
{
    while ( _pHead != NULL )
    {
        QueueItem* _pItem = _pHead->getNext();
        delete _pHead;
        _pHead = _pItem;
    }
}   // end function erase
// Alan Derrick
// C++ Fall 2010
// HW2 Queue
// File: main.cpp

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    Queue myQueue;

    myQueue.removeItem();
    myQueue.addItem("red");
    myQueue.addItem("green");
    myQueue.addItem("blue");
    myQueue.addItem("orange");
    cout << "Printing out 4 items: red, green, blue, orange.\n" << endl;
    myQueue.print();            // print contents of queue (item ID and data)

    myQueue.removeItem();
    myQueue.removeItem();
    myQueue.addItem("brown");
    myQueue.addItem("tan");
    myQueue.addItem("purple");
    myQueue.addItem("lavendar");
    cout << "Printing: blue/orange/brown/tan/purple/lavendar.\n" << endl;
    myQueue.print(); // print contents of queue

    myQueue.removeItem();
    myQueue.removeItem();
    myQueue.removeItem();
    myQueue.removeItem();
    cout << "Printing: purple & lavendar.\n" << endl;
    myQueue.print();

    myQueue.erase();

    myQueue.addItem("Blue-32!");
    myQueue.addItem("Blue-22!");
    myQueue.addItem("Hut-Hut!");
    cout << "Printing out a football hike cadence:\n" << endl;
    myQueue.print();

    myQueue.erase();
    cout << "Printing out the newly erased queue, should be empty:\n" << endl;
    myQueue.print();

	return 0;
}
};
*/

/*namespace _v5 { /// has associated article: https://www.semanticscholar.org/paper/Fast-and-Scalable%2C-Lock-Free-k-FIFO-Queues-Kirsch-Lippautz/a8d05854768dd7e336029942694b8040f0627359?p2df
    #include <iostream>
#include <array>
#include <cstdlib>
#include <atomic>
#include <thread>
#include <chrono>

// note - some of this code was inspired by the algorithms located at
// https://github.com/scala/scala
// nothing was directly taken.

using namespace std;
using namespace std::chrono;
struct Item {
    int value;
    int tag;

    Item(int value) {
        this->value = value;
        this->tag = 0;
    }
};


class KQueue {
    public:
    int size;
    int k;

    atomic<int> head;
    atomic<int> tail;

    // TODO Idea:
    // Instead of passing around the big ass array,
    // Can we just pass around the individual segemnts?
    // Not sure if that would help.
    // This is how they do it in the paper, after all.
    array<std::atomic<int>, 10000000> arr = {};

    std::atomic<int> jobs_completed;
    std::atomic<int> failed;

    KQueue(int size, int k) {
        this->size = size;
        this->k = k;

        this->jobs_completed = 0;
        this->failed = 0;

        head.store(0);
        tail.store(0);
    }

    int getSize(void) {
        return size;
    }

    bool is_queue_full(int head_old, int tail_old) {
        // the queue is full when the tail wraps around and meets the head.
        // we also want to make sure the head didn't change in the meantime
        // so a second check on head occurs here as well.
        if (((tail_old + k) % size) == head_old && (head_old == head.load())) {
                return true;
        }
        return false;
     }

    bool findIndex(int start, bool empty, int *item_index, int *old) {

        int i, index, random = rand() % k;
        for(i = 0; i < k; i++) {
            // First find a random index from [0 - k)
            index = (start + ((random + i) % k)) % size;
            // the number that is currently in this index.
            *old = arr[index].load();
            // We assume that the index is empty if the value is 0.
            // empty just specfies if we are looking for an empty spot, or a taken spot.
            if (((empty && *old == 0)) || (!empty && *old != 0)) {
                // both of these are pointers so that when they are changed
                // the changes can be seen in the orignal function.
                *item_index = index;
                return true;
            }
        }
        return false;
    }


     bool segment_has_stuff(int head_old) {
         int i, start = head_old;

         for(i = 0; i < k; i++) {
             if(arr[(start + i) % size].load() != 0) {
                 return true;
             }
         }
         return false;
     }

     bool in_valid_region(int tail_old, int tail_current, int head_current) {
         if(tail_current < head_current) {
             return true;
         } else {
             return false;
         }
     }


     bool not_in_valid_region(int tail_old, int tail_current, int head_current) {
         if(tail_current < head_current) {
             return true;
         } else {
             return false;
         }
     }


     bool committed(int tail_old, int item_new, int index) {
         if(arr[tail_old].load() != item_new) {
             return true;
         }

         int head_curr = head.load();
         int tail_curr = tail.load();

         if (in_valid_region(tail_old, tail_curr, head_curr)) {
             return true;
         } else if (not_in_valid_region(tail_old, tail_curr, head_curr)) {
           if (!arr[index].compare_exchange_strong(item_new, 0)) {
             return true;
           }
         } else {
           if (head.compare_exchange_strong(head_curr, head_curr)) {
             return true;
           }
           if (!arr[index].compare_exchange_strong(item_new, 0)) {
             return true;
           }
         }
         return false;

     }

    void move_tail_forward(int tail_old) {
        // TODO versioning
        tail.compare_exchange_strong(tail_old, (tail_old + k) % size);
    }

    void move_head_forward(int head_old) {
        // TODO versioning
        head.compare_exchange_strong(head_old, (head_old + k) % size);
    }

    bool enqueue(atomic<int> &new_item) {
        while(true) {
            int tail_old = tail.load();
            int head_old = head.load();

            int item_index, old;
            bool found_free_space = findIndex(tail_old, true, &item_index, &old);


            if (tail_old == tail.load()) {
                if (found_free_space) {
                    // TODO - implement version numbering. This would mean using atomic struct pointers.
                    // Not sure what the implications of this would be, need to think about it.
                    // printf("Got call to enqueue. Found free space at %d with value %d\n", item_index, old);

                    if (arr[item_index].compare_exchange_strong(old, new_item)) {
                        if (committed(tail_old, new_item, item_index)) {
                            return true;
                        }
                    }

                } else {
                    if (is_queue_full(head_old, tail_old)) {
                        // If our head segment has stuff, it means we are full.
                        if (segment_has_stuff(head_old) && head_old == head.load()) {
                            return false;
                        }

                        move_head_forward(head_old);

                    }

                    // check if queue is full AND the segemnt
                    move_tail_forward(tail_old);
                }
            }
        }
    }

    bool dequeue(int *item) {
        while (true) {

            int head_old = head.load();

            int item_index, old;
            bool found_index = findIndex(head_old, false, &item_index, &old);

            int tail_old = tail.load();

            if (head_old == head.load()) {
                // we found something!
                if (found_index) {
                    //  we don't want to be enqueing/dequeing from the same segment!
                    if (head_old == tail_old) {
                        move_tail_forward(tail_old);
                    }

                    if(arr[item_index].compare_exchange_strong(old, 0)) {
                        *item = old;
                        return true;
                    }
                } else {
                    if((head_old == tail_old) && (tail_old == tail.load())) {
                        return false;
                    }

                    move_head_forward(head_old);
                }
            }
        }
    }

    void printQueue() {
        int i;
        for(i = head.load(); i <= tail.load() + k - 1; i++) {
            if (i % k == 0) {
                printf(" - ");
            }
            printf("%d, ", arr[i].load());
        }
        printf("\n");
    }


    void do_work(int thread_number, atomic<int> items_to_add[], int length, bool deq, bool enq) {
        int i, dequeued_value;
        int count = 0;

        for(int i = 0; i < length; i++) {
            count += items_to_add[i];
        }


        for(i = 0; i < length; i++) {
            int randy = rand() % 2;
            if(randy == 0 && enq) {
                // printf("#%d    ---------------------enq(%d)----------------------- %d %d\n", thread_number, items_to_add[i].load(), head.load(), tail.load());
                bool s = enqueue(items_to_add[i]);
                this->jobs_completed++;
            }

            if(randy == 1 && deq) {
                // printf("#%d    ---------------------deq()----------------------- %d %d\n", thread_number, head.load(), tail.load());
                bool s = dequeue(&dequeued_value);
                this->jobs_completed++;
            }
        }
    }
};



int main()
{
    // Initialize an array of atomic integers to 0.
    int i, j;

    KQueue *qPointer = new KQueue(10000000, 32);
    int dequeued_value;
    int start_index = 0;

    // This is the only paramater that should be modified!
    int num_threads = 100;

    int total_jobs = 10000000;
    int jobs_per_thread = total_jobs/num_threads;
    int elems = 0;

    std::thread t[num_threads];
    // Create nodes before hand. This queue requires that
    // only unique items are added!
    atomic<int>** pre = new atomic<int>*[num_threads];
    for(i = 0; i < num_threads; i++) {
        pre[i] = new atomic<int>[jobs_per_thread];
        for(j = 0; j < jobs_per_thread; j++) {
            pre[i][j] = start_index + j;
            elems++;
        }
        start_index += jobs_per_thread;
    }


    for(i = 0; i < num_threads; i++) {
        t[i] = std::thread(&KQueue::do_work, qPointer, i, pre[i], jobs_per_thread, true, true);
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for(int i = 0; i < num_threads; i++) {
        t[i].join();
    }

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    printf("\nTime elapsed in ms: %lld\n", duration);

    // qPointer->printQueue();

    return 0;
}

};
*/

/*namespace _v6 {
    #include <iostream>
using namespace std;

class Queue { // Class definition
private: //private members can only be accessed in the class
	int queue_size;
protected: // protected members can ba accessed in derived classes
	int* buffer;		// pointer to first element of array
	int front;			// used for removing an element of array
	int rear;			  // user for adding an element into queue
	static int counter; // counter is a STATIC class member -> must be initialized outside the class (using :: operator)
						// counter could have been global, but using static allows to :
						// declare it in the class where it's used (readability) & control it's access (encapsulation)
public: // public members can be accessed by all functions
	Queue(void){		//constructor with no parameters
		front = 0;
		rear = 0;
		queue_size = 10;
		buffer = new int[queue_size];	// create an array in the heap
		if (buffer != NULL) counter++;	//counting objects
	}
	Queue(int n) {			// overloaded constructor with one parameter
		front = 0;
		rear = 0;
		queue_size = n;
		buffer = new int[queue_size]; // same as above, create heap object of type : array of int
		if (buffer != NULL) counter++;
	}
	virtual ~Queue(void) { //destructor
		delete buffer;	// must use "delete [] buffer;" if buffer points to an array of objects, (instead of array of int)
		counter--;		//decrement the # of objects
	}

	void enqueue(int v) { // add element at the end of queue
		if (rear < queue_size) buffer[rear++] = v;
		else if (compact()) buffer[rear++] = v;
	}
	int dequeue(void) { // return and remove 1st element from queue
		if (front < rear) return buffer[front++];
		else { cout << "Error:Queue empty" << endl; return -1; }
	}
private:
	bool compact(void); // implementation is outside class (allowed in C++ using ::, not allowed in Java)
};
//counter initialized to zero, it keeps track of # of Queues created
int Queue::counter = 0;
//End of class definition

class PriQueue: public Queue {//PriQueue derived from Queue
public:
	int getMax(void); // return and remove the max value from priority queue
	PriQueue(int n) : Queue(n) {};	// <- here PriQueue constructor simply calls Queue constructor
	// this is because base class constructor may not be inherited. Has to be explicitly called.

	~PriQueue() { // base class destructor may not be called or inherited.
		delete buffer; //Must explicitly use delete
		buffer = NULL;
		counter--; // decrement counter of objects
	}
};


bool Queue::compact(void) { //compact function implementation, separate from specification ()
	if (front == 0) {
		cout << "Error: Queue overflow" << endl;
		return false;
	}
	else {
		for (int i = 0;i < rear - front;i++)
		{
			buffer[i] = buffer[i + front];
		}
		rear = rear - front;
		front = 0;
		return true;
	}
}

int PriQueue::getMax(void){// get & remove max value from priority queue
	int i, max, imax;
	if (front < rear) {
		max = buffer[front];
		imax = front; // imax is index of current max value
		for (i = front;i < rear;i++) {
			if (max < buffer[i]) {
				max = buffer[i];
				imax = i;
			}
		}
		for (i = imax;i < rear - 1;i++)
			buffer[i] = buffer[i++]; // remove max value
		rear = rear - 1;
		return max;
	}
	else {
		cout << "Error: Queue empty" << endl;
		return -1;
	}
}

//main outside all classes
void main() {
	Queue Q1(5);		// variable/object created using constructor in stack memory (note that buffer will create an array on the heap)
	Q1.enqueue(2);
	Q1.enqueue(8);
	int x = Q1.dequeue();
	int y = Q1.dequeue();
	cout << "x = " << x << endl << "y = " << y << endl;

	Queue* Q2;			// create pointer (in the stack) to a Queue variable/object
	Q2 = new Queue(4);  // call constructor Queue(int) and dynamically allocate memory from heap
	Q2->enqueue(12);	// insert 12
	Q2->enqueue(18);	// insert 18
	x = Q2->dequeue();
	y = Q2->dequeue();
	cout << "x = " << x << endl << "y = " << y << endl;

	PriQueue* Q3 = new PriQueue(4);
	Q3->enqueue(12);
	Q3->enqueue(18);
	Q3->enqueue(14);
	x = Q3->getMax();
	y = Q3->getMax();
	cout << "x = " << x << endl << "y = " << y << endl;

	//Since Q2 & Q3 are in the heap
	delete Q2; Q2 = NULL;
	delete Q3; Q3 = NULL;
	}

};
*/

/*namespace _v7 {
    Implementation using C++ programming

#include <iostream>
#define SIZE 5   // Size of Circular Queue

using namespace std;

class Queue {
private:
    int items[SIZE], front, rear;

public:
    Queue(){
        front = -1;
        rear = -1;
    }

    bool isFull(){
        if(front == 0 && rear == SIZE - 1){
            return true;
        }
        if(front == rear + 1) {
            return true;
        }
        return false;
    }

    bool isEmpty(){
        if(front == -1) return true;
        else return false;
    }

    void enQueue(int element){
        if(isFull()){
            cout << "Queue is full";
        } else {
            if(front == -1) front = 0;
            rear = (rear + 1) % SIZE;
            items[rear] = element;
            cout << endl << "Inserted " << element << endl;
        }
    }

    int deQueue(){
        int element;
        if(isEmpty()){
            cout << "Queue is empty" << endl;
            return(-1);
        } else {
            element = items[front];
            if(front == rear){
                front = -1;
                rear = -1;
            } // Q has only one element, so we reset the queue after deleting it.
            else {
                front=(front+1) % SIZE;
            }
            return(element);
        }
    }

    void display()
    {
        // Function to display status of Circular Queue
        int i;
        if(isEmpty()) {
            cout << endl << "Empty Queue" << endl;
        }
        else
        {
            cout << "Front -> " << front;
            cout << endl << "Items -> ";
            for(i=front; i!=rear;i=(i+1)%SIZE)
                cout << items[i];
            cout << items[i];
            cout << endl << "Rear -> " << rear;
        }
    }

};


int main()
{
    Queue q;




    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    q.enQueue(4);
    q.enQueue(5);
    q.enQueue(6);
    q.deQueue();
    q.deQueue();
}
};
*/

/*namespace _v8 {
    //
//  main.cpp
//  Lab
//
//  Created by Nermin Sehic on 10/30/16.
//  Copyright © 2016 Nermin Sehic. All rights reserved.
//
#include<iostream>

using namespace std;

// Define node pointer
struct node {
    int data;
    node* next;
};

// Head and tail pointers
node* head;
node* tail;

// Functions
int menu();
void enqueue(node *& head, node *&tail, int data);
void dequeue(node *&head, node *& tail);
void front(node *& head);
bool isEmpty(node *& head);
int randomNumber(int min, int max);

//Main function
int main() {

    node* head;
    node* tail;

    head = NULL;
    tail = NULL;
    int choice;
    printf("Number is %d", randomNumber(0, 10));
    do {
        choice = menu();

        switch(choice) {
            case 1:
                int data;
                cout<<"Enter value to be stored in queue: ";
                cin>>data;
                enqueue(head,tail,data);
                break;
            case 2:
                dequeue(head,tail);
                break;
            case 3:
                front(head);
                break;
            case 4:
                printf("Not implemented");
                break;
            case 5:
                isEmpty(head);
                break;
            case -1:
                choice = -1;
                break;

            default: printf("\nEnter a valid choice!!");
        }
    } while(choice != -1);

    return 0;
}

//Menu function
int menu() {
    int ch;
    printf("\nStack");
    printf("\n1.Enqueue\n2.Dequeue\n3.Front element\n4.Is Full\n5.Is Empty\n6.Exit");
    printf("\nEnter your Choice:");
    scanf("%d",&ch);
    return ch;
}

//Enqueue element in stack
void enqueue(node *& head, node *&tail, int data) {
    if (head == NULL) {
        node* n= new node;

        n->data = data;
        n->next = NULL;

        head = n;
        tail = n;

    } else {
        node* n = new node;
        n->data = data;
        n->next = head;
        head = n;
    }
}

// Dequeue first element in a queue
void dequeue(node *&head, node *& tail) {
    if (head == NULL) {
        printf("\nThe queue is empty.");

    } else if (head == tail) {
        // Case when there is only 1 element in the stack
        printf("The value %d was dequeude", head->data);
        delete head;
        head = NULL;
        tail = NULL;

    } else {
        node* n = new node;
        n = tail;
        if(tail->next == NULL) {
            tail = head;
        } else {
            tail = tail->next;
        }

        printf("\nThe value %d was dequeued", n->data);
        delete n;
    }
}

//Show top-most element in stack
void front(node *& head) {
    if (head == NULL) {
        printf("\nThe queue if empty");

    } else {
        printf("\nFront number is %d", head->data);
    }
}

// Shows if the stack is empty
bool isEmpty(node *& head) {
    if(head == NULL) {
        printf("\nThe queue is empty");
        return true;

    } else {
        printf("\nThe queue is not empty");
        return false;
    }
}

int randomNumber(int min, int max) {
    static bool first = true;
    if ( first )
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % (max - min);
}

};
*/

/*namespace _v9 {
    #include<iostream>
#define MAX_SIZE 6
#define MINUS_INF -999999

using namespace std;

class Queue
{
    int arr[MAX_SIZE];
    int frnt;
    int rear;
    int cnt;
public:
    Queue()
    {
        frnt=0;
        rear=0;
        cnt=0;
    }
    void enqueue(int element);
    int dequeue();
    bool isEmpty();
    int queueSize();
    bool isFull();
    int top();
    int bottom();
    void display_queue(Queue q);
};

void Queue::enqueue(int element)
{
    if(isFull())
    {
        cout<<"overflow"<<endl;
    }
    else
    {
        if(rear==MAX_SIZE)
            rear=0;
        arr[rear++]=element;
        cnt++;
    }
}
int Queue::dequeue()
{
    if(isEmpty())
    {
        cout<<"underflow"<<endl;
        return MINUS_INF;
    }
    int a=arr[frnt++];
    if(frnt==MAX_SIZE) frnt=0;
    cnt--;
    return a;
}
int Queue::top()
{
    return arr[frnt];
}
int Queue::bottom()
{
    return arr[rear-1];
}
bool Queue::isEmpty()
{
    if(cnt==0) return true;
    else return false;
}
bool Queue::isFull()
{
    if(cnt==MAX_SIZE) return true;
    else return false;
}
int Queue::queueSize()
{
    return cnt;
}
void Queue::display_queue(Queue q)
{
    Queue q1;
    q1=q;
    while(!q.isEmpty())
    {
        cout<<q.dequeue()<<" "<<endl;
    }
    cout<<endl;
    q=q1;
}
void push(Queue *q1,Queue *q2,int x)
{
    if(q1->isEmpty())
    {
        q2->enqueue(x);
    }
    else
    {
        q1->enqueue(x);
    }
}
int pop(Queue *q1, Queue *q2)
{
    if(q1->isEmpty())
    {
        if(q2->isEmpty())
        {
            cout<<"underflow"<<endl;
            return MINUS_INF;
        }
        else
        {
            while(q2->queueSize()>1)
            {
                int x=q2->dequeue();
                q1->enqueue(x);
            }
            return q2->dequeue();
        }
    }
    else
    {
        while(q1->queueSize()>1)
        {
            int x=q1->dequeue();
            q2->enqueue(x);
        }
        return q1->dequeue();
    }
}
void print(Queue *q1,Queue *q2)
{
    if(q1->isEmpty())
    {
        q2->display_queue(*q2);
    }
    else
    {
        q1->display_queue(*q1);
    }
}
int size(Queue *q1, Queue *q2)
{
    if(q1->isEmpty()) return q2->queueSize();
    else return q1->queueSize();
}
int top1(Queue *q1, Queue *q2)
{
    if(q1->isEmpty()) return q2->bottom();
    else return q1->bottom();
}
int main()
{
    Queue q1,q2;
    int choice, result, element;
	do{
		cout << "\n1. Push  2. Pop  3. Top  4. Is Empty  5. Is Full 6. Size  7. Print  8. Quit\n";
		cout << "Enter Choice: ";
		cin >> choice;
		switch(choice){
			case 1:
				cout << "\nEnter Element: " ;
				cin >> element;
				push(&q1,&q2,element);
				print(&q1,&q2);
				break;
			case 2:
				cout<<"popped element: "<<pop(&q1,&q2)<<endl;
				print(&q1,&q2);
				break;
			case 3:
				cout << "Top of the stack is: " << top1(&q1,&q2);
				break;
			case 6:
				cout << "\n Stack size is: " << size(&q1,&q2) << endl;
				break;
			case 7:
				print(&q1,&q2);
		}
	}while(choice!=8);
}
};
*/

/*namespace _v10 {

// * Queue.h
// *
// * By Steven de Salas
// *
// * Defines a templated (generic) class for a queue of things.
// * Used for Arduino projects, just #include "Queue.h" and add this file via the IDE.
// *
// * Examples:
// *
// * Queue<char> queue(10); // Max 10 chars in this queue
// * queue.push('H');
// * queue.push('e');
// * queue.count(); // 2
// * queue.push('l');
// * queue.push('l');
// * queue.count(); // 4
// * Serial.print(queue.pop()); // H
// * Serial.print(queue.pop()); // e
// * queue.count(); // 2
// * queue.push('o');
// * queue.count(); // 3
// * Serial.print(queue.pop()); // l
// * Serial.print(queue.pop()); // l
// * Serial.print(queue.pop()); // o
// *
// * struct Point { int x; int y; }
// * Queue<Point> points(5);
// * points.push(Point{2,4});
// * points.push(Point{5,0});
// * points.count(); // 2
// *


#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>

template<class T>
class Queue {
  private:
    int _front, _back, _count;
    T *_data;
    int _maxitems;
  public:
    Queue(int maxitems = 256) {
      _front = 0;
      _back = 0;
      _count = 0;
      _maxitems = maxitems;
      _data = new T[maxitems + 1];
    }
    ~Queue() {
      delete[] _data;
    }
    inline int count();
    inline int front();
    inline int back();
    void push(const T &item);
    T peek();
    T pop();
    void clear();
};

template<class T>
inline int Queue<T>::count()
{
  return _count;
}

template<class T>
inline int Queue<T>::front()
{
  return _front;
}

template<class T>
inline int Queue<T>::back()
{
  return _back;
}

template<class T>
void Queue<T>::push(const T &item)
{
  if(_count < _maxitems) { // Drops out when full
    _data[_back++]=item;
    ++_count;
    // Check wrap around
    if (_back > _maxitems)
      _back -= (_maxitems + 1);
  }
}

template<class T>
T Queue<T>::pop() {
  if(_count <= 0) return T(); // Returns empty
  else {
    T result = _data[_front];
    _front++;
    --_count;
    // Check wrap around
    if (_front > _maxitems)
      _front -= (_maxitems + 1);
    return result;
  }
}

template<class T>
T Queue<T>::peek() {
  if(_count <= 0) return T(); // Returns empty
  else return _data[_front];
}

template<class T>
void Queue<T>::clear()
{
  _front = _back;
  _count = 0;
}

#endif

};
*/

/*namespace _v11 {
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Priority_Queue{

private:

	typedef struct _node{
		int item;
		struct _node *next;  //NEED TO USE STRUCT IN DEFINITION
	}node;

	int nodeCount;  //KEEP COUNT
	node *head;     //POINTER TO HEAD
	node *tail;     //POINTER TO TAIL

	void sort(void);

public:

	Priority_Queue();   //CONSTRUCTOR
	bool empty();       //TEST IF LIST IS EMPTY
	int size();         //RETURN SIZE
	int front();        //ACCESS FIRST NODE (head pointer)
	int back();         //ACCESS LAST NODE  (tail pointer)
	void enqueue(int);  //ADD
	void dequeue();     //REMOVE
	void printQueue();  //PRINT
	void deleteQueue(); //DELETE CORRECTLY
};

Priority_Queue::Priority_Queue()
{
	head = NULL;    //INITIALIZE TO NULL
	tail = NULL;    //???
	nodeCount = 0;  //NO NODES TO START
}

bool Priority_Queue::empty()
{
	return (head == NULL);  // IF NULL RETURN TRUE
}

int Priority_Queue::size()
{
	return nodeCount;
}

int Priority_Queue::front()
{
	return ( head->item);  //COULD BE SEG FAULT
	//NEED USER TO CHECK IF STACK IS EMPTY
}

int Priority_Queue::back()
{
	return ( tail->item);
}

void Priority_Queue::enqueue(int addItem)
{
	if( head == NULL )
	{
		head = (node*)calloc( 0, sizeof( node ) );

		if(head != NULL) //CHECK FOR NULL
		{
			head->item = addItem;
			tail=head;    //ONE ITEM- HEAD AND TAIL ARE THE SAME

			nodeCount++;  //ADD COUNT TO QUEUE
		}
		else
		{
			cout <<"Memory Error";
		}
	}
	else
	{
		//node *nodePtr = (node*)malloc( sizeof( node ) );
		node *newNode = (node*)calloc( 0, sizeof( node ) );
		node *nodePtr;

		if( newNode != NULL && nodePtr != NULL )
		{
			newNode->item = addItem;

			nodePtr = head;

			while (nodePtr->next != NULL)
			{
				nodePtr = nodePtr->next;
			}

			nodePtr->next = newNode;
			tail = newNode;

			nodeCount++;
		}
		else
		{
			cout <<"Memory Error";
		}
	}

	sort();

}//END ENQUEUE()

void Priority_Queue::dequeue()
{
	if( head != NULL)
	{
		node *temp = head; //POINTING TO WHAT HEAD IS POINTING AT
		head = head->next; //HEAD JUMPS ONE BACK

		free( temp );      //THE FIRST NODE IS FREED
		temp = NULL;       //REINITIALIZED TO NULL

		nodeCount--;
	}
}

void Priority_Queue::printQueue()
{
	node *temp = head;
	int i = 1;

	cout << "=========LIST OUTPUT===========" << endl;
	while( temp != NULL  )
	{
		cout << "Value at position " << i <<": "<< temp->item << endl;
		temp = temp->next;
		i++;
	}
	cout << "===============================" << endl;
	cout << "Node Count: " << size() << endl;
	cout << "The last value in the list is: " << back() << endl << endl;
	cout << "The first value in the list is: " << front() << endl << endl;

}

void Priority_Queue::deleteQueue() //CORRECT WAY TO DELETE A LIST
{
	node *temp;

	while( head != NULL)
	{
		temp = head; //PLACEHOLDER
		head = head->next;
		free( temp );
	}
	temp = NULL;
	nodeCount = 0; //RE-INITIALIZE
}

void Priority_Queue::sort(void)
{
	node *i;
	node *j;
	node *max;
	int temp; //INT TO HOLD VARIABLE


	for(i = head ; i != NULL && i->next != NULL ; i = i->next)
	{
		max = i;

		for(j = i->next ; j != NULL ; j = j->next)
		{
			if(  (j->item) > (max->item)  ) //GREATER THAN
			{
				max = j;
			}
		}

		if( max != i )
		{
			temp = max->item;
			max->item = i->item;
			i->item = temp;
		}
	}

	i = NULL;
	j = NULL;
	max = NULL;
}

int main( int argc, char **argv)
{

	Priority_Queue myQueue = Priority_Queue();

	cout << endl << "*******PLEASE ENTER A LIST OF RANDOM NUMBERS BETWEEN 1 AND 100********" << endl;

	int exit = 0;  // variable for while loop
	int j = 1;     // counter for user input
	int input = 0; // int to receive user input

	while(exit == 0){

		cout << "Please enter a whole number for queue[" << j << "] :";
		cin >> input;

		if((input >= 1) && (input <= 100)){

			cout << "Your Input Was : " << input << endl;
			myQueue.enqueue(input); //ADD TO QUEUE

			j++; //INCREMENT TO SHOW NEXT NUMBER FOR USER INPUT
			input = 0; // RESET
		}
		else{

			cout << "Please Enter a Number Between 1 and 100" << endl;
		}

		cout << "Press 0 to continue entering numbers, or 1 to exit:";
		cin >> exit;
	}

	myQueue.printQueue();
	myQueue.deleteQueue();

}
};
*/

/*namespace _v12 {
    //
//  main.cpp
//  Lab
//
//  Created by Nermin Sehic on 10/30/16.
//  Copyright © 2016 Nermin Sehic. All rights reserved.
//

// Stack using array
#include <iostream>

using namespace std;

// Constants
#define max 20

// Functions
int menu();

// Stack functions
void enqueue();
void dequeue();
int front();
bool isFull();
bool isEmpty();

// Variables
int queue[max];
int frontElement = 0;
int rearElement = 0;

int main(int argc, const char * argv[]) {

    int choice;

    do {
        choice = menu();

        switch(choice) {
            case 1: enqueue();
                break;
            case 2: dequeue();
                break;
            case 3: front();
                break;
            case 4: isFull();
                break;
            case 5: isEmpty();
                break;
            case -1:
                choice = -1;
                break;

            default: printf("\nEnter a valid choice!!");
        }
    } while(choice != -1);
}

int menu() {
    int ch;
    printf("\nQueue");
    printf("\n1.Enqueue\n2.Dequeue\n3.Front element\n4.Is Full\n5.Is Empty\n6.Exit");
    printf("\nEnter your Choice:");
    scanf("%d",&ch);
    return ch;
}

void enqueue() {
    if(rearElement == max) {
        printf("\nOverflow");

    } else {
        int element;
        printf("\nEnter Element:");
        scanf("%d",&element);
        printf("\nElement(%d) has been pushed at %d", element, rearElement);
        queue[rearElement] = element;
        rearElement++;
    }
}

void dequeue() {
    if(rearElement == 0) {
        printf("Queue is empty.");

    } else {
        if(frontElement == rearElement)
        {
            frontElement = 0;
            rearElement = 0;
        }

        printf("Dequeued element is %d", queue[frontElement]);
        frontElement ++;
    }
}

int front() {
    printf("\nTop number is %d", queue[frontElement]);
    return queue[frontElement];
}

bool isFull() {
    if(rearElement == max -1) {
        printf("\n%d", true);
        return true;

    } else {
        printf("\n%d", false);
        return false;
    }
}

bool isEmpty() {
    if(rearElement == 0) {
        printf("\n%d", true);
        return true;

    } else {
        printf("\n%d", false);
        return false;
    }
}

};
*/

namespace literal_macros {
    // (*?) macros for literals
    // (*!?) numeric literal values having specific widths
    uint32_t a = UINT32_C(123);
    //uint32_t b = UINT18_C(1234);  // not all widths are defined
    uint32_t b = UINT16_C(1234);

    uint64_t c = UINT32_C(10'006'721);
    constexpr float pi = 3.1415926535'8979323846f;
};

#endif // QUEUEDTS_HPP_INCLUDED
