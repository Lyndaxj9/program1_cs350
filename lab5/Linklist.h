#ifndef LINKLIST_H
#define LINKLIST_H

#include "Node.h"

class Linklist{
	private:
		Node * head;
		Node * tail;
		int length;

	public:
		Linklist();
		Linklist(Node* head);
		Node * getHead();
		Node * getTail();
		int getLength();
		void setHead(Node * tmp);
		void setTail(Node * tmp);
		void addFront(Node * tmp);
		void addBack(Node * tmp);
		int Find(int value);
		void eraseAndAddFront(Node * tmp);
};
#endif
