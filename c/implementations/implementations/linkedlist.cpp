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
	Node* new_node = new Node();
	//Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Error creating new node.\n");
		exit(0);
	}
	new_node->item = item;
	new_node->next = next;
	return new_node;
}

LinkedList::LinkedList() {
	head = NULL;
	size = 0;
}

LinkedList::LinkedList(int item) {
	//head = new Node();
	//head->item = item;
	head = create(item, NULL);
	size = 1;
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
	if (index < 0 || index > (size - 1)) {
		throw std::out_of_range("Tried to Access() invalid index.");
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
	if (!isEmpty())
		return head->item;
	else
		throw std::out_of_range("Attempted to Access() empty list.");
}

int LinkedList::Back() {
	if (!isEmpty())
		return Access(size - 1);
	else
		throw std::out_of_range("Attempted to Access() empty list.");
	/*
	Node * cursor = head;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}
	return cursor->item;	
	*/
}

int LinkedList::AccessFromEnd(int n) {
	// TODO: Implement
	if (n > 0 && n < size)
		return Access(size - 1 - n);
	else
		throw std::out_of_range(
			"AccessFromEnd(int n), n must be a positive integer, less than sizeof(List)");
}

void LinkedList::PushFront(int value) {
	head = create(value, head);
	size++;
}

void LinkedList::PushBack(int value) {
	// TODO: Less hacky solution?
	if (isEmpty())
		head = create(value, NULL);
	else {
		Node * cursor = head;
		while (cursor->next != NULL) {
			cursor = cursor->next;
		}
		cursor->next = create(value, NULL);
	}
	size++;
}

void LinkedList::Insert(int index, int value) {
	if (index <= 0 || index >= size) {
		throw std::out_of_range("Attempted to Insert() outside of list range.");
	}
	else {
		Node* cursor = head;
		int i = 0;
		while (i < index) {
			printf("Cursor at %p...\n", cursor);
			cursor = cursor->next;
			i++;
		}

		Node* temp = create(value, cursor->next);
		cursor->next = temp;
		size++;
	}
}

void LinkedList::PopFront() {
	// TODO: Test for memory leak?
	Node* temp = head->next;
	free(head);
	head = temp;
	size--;	
}

void LinkedList::PopBack() {
	if (size <= 0) {
		throw std::out_of_range("Nothing to Pop().");
	}

	Node *cursor = head;
	int i = 0;
	while (i < (size - 2)) {
		cursor = cursor->next;
		i++;
	}
	Node * temp = cursor;
	cursor->next = NULL;
	delete temp;
	size--;
	
}
void LinkedList::RemoveValue(int value) {

}
void LinkedList::Erase(int index) {

}

void LinkedList::Reverse(int value) {

}

//	PrintList(LinkedList) calls this destructor but it destroys the list...
LinkedList::~LinkedList() {
	//	Mine
	Node* cursor = head;
	while (cursor->next != NULL) {
		head = head->next;
		free(cursor);
		cursor = head;
	}
	free(head);
	

	/*	StackOverflow's
	Node *current = head;
	while (current != 0) {
		Node *next = current->next;
		delete current;
		current = next;
	}
	head = 0;
	*/

	size = 0;	
}