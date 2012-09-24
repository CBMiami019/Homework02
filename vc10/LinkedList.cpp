//I've had a lot of problems with my ".h" header files recently
//Mostly I've been running into the problem of my .cpp files not recognizing certain
//functions unless I open my .h file via Windows Explorer and edit it directly
//from there, not from within Visual C++


#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Resources.h"
#include "LinkedList.h"

using namespace ci;
using namespace ci::app;
using namespace std;


//Credited to AJDUBERSTEIN
LinkedList::~LinkedList(){
	if (sentinel_){
		Node* tmp = sentinel_;
		while (tmp->next!=sentinel_){
			Node* t = tmp;
			tmp = tmp->next;
			delete(t);
		}
		delete tmp;
		sentinel_ = NULL;
	}
}


/**
 * Appends a node to the circular list with the given data. AJDUBERSTEIN
 */
void LinkedList::addNode(int number){
	if (num_items_ < 0)
		num_items_ = 0;
	num_items_++;
	Node* t = new Node(number, NULL);
	if (sentinel_ == NULL){
		t->next = t;
		sentinel_ = t;
		return;
	}
	Node* tmp = sentinel_;
	while(tmp->next != sentinel_){
		tmp = tmp->next;
	}
	tmp->next = t;
	t->next = sentinel_;
}

/**
 * Moves all nodes one space forward (tail becomes head). AJDUBERSTEIN
 */
void LinkedList::next_in_list(){
	if (sentinel_ != NULL){
		Node* old_root = sentinel_;
		//Traverse the list to find the last node
		Node* tmp = sentinel_;
		Node* last;
		while (true){
			tmp = tmp->next;
			if (tmp->next == sentinel_){
				last = tmp;
				break;
			}
		}
		//Swap the first and last node
		Node* temp = sentinel_;
		sentinel_ = last;
		last = temp;
	}
}

//AJDUBERSTEIN
void LinkedList::reverse_list(){
  Node* tmp = NULL;
  Node* cur = sentinel_;
  Node* next;
  while (cur != NULL)
  {
    next = cur->next; 
    cur->next = tmp;
    tmp = cur;
    cur = next;
    if (cur == sentinel_)
    {
      break;
    }
  }
  sentinel_->next = tmp;
  sentinel_ = tmp;
}


Node* LinkedList::at(int index){
		int i = 0;
		Node* tmp = sentinel_;
		while (tmp->next!=sentinel_ && i < index){
			Node* t = tmp;
			tmp = tmp->next;
			i++;
		}
		return tmp;
}



