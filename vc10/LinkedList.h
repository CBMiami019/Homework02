//I've had a lot of problems with my ".h" header files recently
//Mostly I've been running into the problem of my .cpp files not recognizing certain
//functions unless I open my .h file via Windows Explorer and edit it directly
//from there, not from within Visual C++

#ifndef LINKEDLIST_H

#define LINKEDLIST_H

struct Node{
	int data;
	Node* next;
	Node(int x, Node* y) : data(x), next(y){}
};

class Homework02App;

class LinkedList{
private:

	Node *sentinel_;
	int num_items_;

public:

	LinkedList(): sentinel_() {}
	~LinkedList();
	Node* at(int index);
	int getLength();
	void Length(int length);
	void next_in_list();
	void addNode(int number);
	void reverse_list();	
};




#endif
