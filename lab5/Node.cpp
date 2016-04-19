#include "Node.h"
#include <stdlib.h>

Node::Node()
{
	value = 0;
	next = NULL;
}

Node::Node(int value, Node * next)
{
	this->value = value;
	this->next = next;
}

Node::Node(int value)
{
	this->value = value;
	this->next = NULL;
}

int Node::getValue()
{
	return this->value;
}

Node * Node::getNext()
{
	return this->next;
}

void Node::setValue(int val)
{
	this->value = val;
}

void Node::setNext(Node * tmp)
{
	this->next = tmp;
}


