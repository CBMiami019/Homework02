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

