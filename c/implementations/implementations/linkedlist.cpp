#include "stdafx.h"
#include "linkedlist.h"

/*
Node::Node(int item, Node n) {
	item = item;
	next = n.next;
}

Node::Node(int val) {
	item = val;
}
*/

Node* create(int item, Node* next) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Error creating new node.\n");
		exit(0);
	}
	new_node->item = item;
	new_node->next = next;
	return new_node;
}

LinkedList::LinkedList() {
	head = create(NULL, NULL);
	size = 0;
}

LinkedList::LinkedList(int item) {
	head = create(item, NULL);
	size++;
}

LinkedList::~LinkedList() {
	Node* cursor = head;
	while (cursor != 0) {

	}
}


int LinkedList::Size() {
	return size;
}

bool LinkedList::isEmpty() {
	return size == 0;
	//return size == 0 ? true : false;
	//if (size == 0) return true;
	//else return false;
}

// Returns the item at indexth node
int LinkedList::Access(int index) {
	// TODO
	if (index > size || index < 0) {
		printf("Attempted to access outside of Linked List.");
		exit(0);
	}
	else {
		int count = 0;
		Node* cursor = head;
		while (count != index) {
			cursor = cursor->next;
			count++;
		}
		return cursor->item;
	}
}

int LinkedList::Front() {
	return head->item;
}
int LinkedList::Back() {
	// TODO: Test - no idea if any of this pointer syntax is correct.
	//			Use size to get to back... for i < size?
	return Access(size - 1);
	/*
	Node *cursor = head;
	while (cursor != NULL) {
		cursor = cursor->next;
	}
	return cursor->item;
	*/
}
int LinkedList::AccessFromEnd(int n) {
	// TODO: Implement
	return NULL;
}

void LinkedList::PushFront(int value) {
	head = create(value, head);
	size++;
}
void LinkedList::PushBack(int value) {

}
void LinkedList::Insert(int index, int value) {
	//newNext = Node(item, oldNext);

}

void LinkedList::PopFront() {
	// TODO: Test for memory leak?
	Node* temp = head;
	//delete head;
	head = temp->next;
	
}
void LinkedList::PopBack() {
	
}
void LinkedList::RemoveValue(int value) {

}
void LinkedList::Erase(int index) {

}

void LinkedList::Reverse(int value) {

}
