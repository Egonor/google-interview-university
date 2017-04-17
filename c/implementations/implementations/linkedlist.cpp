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

int LinkedList::Access(int index) {
	// TODO
	if (index < 0 || index > (size - 1)) {
		throw std::out_of_range("Tried to Access() invalid index.");
	}
	else {
		int count = 0;
		Node* current = head;
		while (count != index) {
			current = current->next;
			count++;
		}
		return current->item;
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
	Node * current = head;
	while (current->next != NULL) {
		current = current->next;
	}
	return current->item;	
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
		Node * current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = create(value, NULL);
	}
	size++;
}

void LinkedList::Insert(int index, int value) {
	if (index <= 0 || index >= size) {
		throw std::out_of_range("Attempted to Insert() outside of list range.");
	}
	else {
		Node* current = head;
		int i = 0;
		while (i < index) {
			printf("current at %p...\n", current);
			current = current->next;
			i++;
		}

		Node* temp = create(value, current->next);
		current->next = temp;
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

	Node *current = head;
	int i = 0;
	while (i < (size - 2)) {
		current = current->next;
		i++;
	}
	Node *temp = current;
	current->next = NULL;
	delete temp;
	size--;
	
}

void LinkedList::RemoveValue(int value) {
	// For reference: https://www.cs.bu.edu/teaching/c/linked-list/delete/
	printf("Attempting to RemoveValue(%d)...\n", value);
	
	Node *current = head;
	Node *previous = NULL;
	while (current->item != value && current->next != NULL) 
	{
		previous = current;
		current = current->next;
	}

	if (current->item == value) {
		if (previous == NULL)
			head = current->next;
		else {
			previous->next = current->next;
		}

		free(current);
		size--;
	}
	else
		printf("%d not found, cannot remove!\n", value);
}

void LinkedList::Erase(int value) {
	printf("Removing all items with value %d...\n", value);
	int count = 0;	
	Node *current = head;
	Node *previous = NULL;
	// Doesn't hand end case, neither does do{} while; loop.
	// while (current->next != NULL)
	for (int i = 0; i < size; i++) {
		if (current->item == value) {
			if (previous == NULL) {
				head = current->next;
				free(current);			
				current = head;
			}
			else {
				previous->next = current->next;
				free(current);
				current = previous->next;
			}
			count++;		}
		else {
			previous = current;
			current = current->next;
		}
	}
	size -= count;
	printf("Removed %d items.\n", count);
}

void LinkedList::Reverse() {
	// TODO: Study this cause it works and I wrote it but it hasn't
	//		 really sunk in yet.
	Node *prev = NULL;
	Node *curr = head;
	Node *n;
	
	for (int i = 0; i < size; i++) {
		n = curr->next;				// Save Next node, include NULL
		curr->next = prev;			// Point Current node to Previous node
		prev = curr;				// Make Current node new Previous node

		if (n != NULL)				// if Next was set NULL above, we're done...
			curr = n;				// Make Next node new Current node
		else
			head = curr;			// At end, set Current node as Head
	}
}

LinkedList::~LinkedList() {
	//	PrintList(LinkedList) calls this destructor - doesn't copy value for some reason?

	//	Mine
	Node *current = head;
	while (current->next != NULL) {
		head = head->next;
		free(current);
		current = head;
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