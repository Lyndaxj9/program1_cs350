#ifndef NODE_H
#define NODE_H

class Node{
	private:
		int value;
		Node * next;
	public:
		Node();
		Node(int value, Node* next);
		Node(int value);
		int getValue();
		Node* getNext();
		void setValue(int val);
		void setNext(Node * tmp);
};

#endif

