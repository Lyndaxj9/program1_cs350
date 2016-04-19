#include "Linklist.h"
#include <stdlib.h>

Linklist::Linklist()
{
	head = NULL;
	tail = NULL;
	length = 0;
}

Linklist::Linklist(Node * head)
{
	this->head = head;
	this->tail = head;
	length = 1;
}

Node * Linklist::getHead()
{
	return this->head;
}

Node * Linklist::getTail()
{
	return this->tail;
}

int Linklist::getLength()
{
	return this->length;
}

void Linklist::setHead(Node * tmp)
{
	this->head = tmp;
}

void Linklist::setTail(Node * tmp)
{
	this->tail = tmp;
}

void Linklist::addFront(Node * tmp)
{
	tmp->setNext(getHead());
	setHead(tmp);
	length++;
}

void Linklist::addBack(Node * tmp)
{
	Node * newNode = getHead();
	while(newNode->getNext() != NULL)
	{
		newNode = newNode->getNext();
	}
	newNode->setNext(tmp);
	setTail(tmp);
	length++;
}

int Linklist::Find(int value)
{
	int counter = -1;
	Node * newNode = getHead();
	while(newNode != NULL)
	{
		counter++;
		if(newNode->getValue() == value)
		{
			return counter;
		}
		newNode = newNode->getNext();
	}
	return -1;
}


void Linklist::eraseAndAddFront(Node * tmp)
{
	Node * iter = getHead();
	while(iter != NULL)
	{
		if(iter->getNext()==NULL)
		{
			break;
		}
		if(iter->getNext()->getValue() == tmp->getValue())
		{
			if(iter->getNext()->getValue() == getTail()->getValue())
			{
				setTail(iter);	
			}
			iter->setNext(iter->getNext()->getNext());
			break;
		}
	}
	addFront(tmp);
}









