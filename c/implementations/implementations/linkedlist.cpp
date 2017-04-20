#include "stdafx.h"
#include "linkedlist.h"


Node* create(int item, Node* next) {
	Node* new_node = new Node();
	/* Malloc Version
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Error creating new node.\n");
		exit(0);
	}
	*/
	new_node->item = item;
	new_node->next = next;
	return new_node;
}

LinkedList::LinkedList() {
	head = NULL;
	tail = head;
	size = 0;
}

LinkedList::LinkedList(int item) {
	//head = new Node();
	//head->item = item;
	head = create(item, NULL);
	tail = head;
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
	if (index < 0 || index > (size - 1)) {
		throw std::out_of_range("Tried to Access() invalid index.");
	}
	// TAIL: Access()ing the end is O(1) with a tail pointer.
	else if (index == (size - 1)) {
		return tail->item;
	}
	else {
		Node *curr = head;
		for (int i = 0; i < index; i++) {
			curr = curr->next;
		}
		return curr->item;
		/* THIS WORKS BUT I REWROTE AS A FOR LOOP
		int count = 0;
		Node* current = head;
		while (count != index) {
			current = current->next;
			count++;
		}
		return current->item;
		*/
	}
}

int LinkedList::Front() {
	if ( !isEmpty() )
		return head->item;
	else
		throw std::out_of_range("Attempted to Access() empty list.");
}

int LinkedList::Back() {
	// O(1) with tail pointer.
	if (!isEmpty())
		return tail->item;
		//return Access(size - 1);
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
	if (n > 0 && n < size)
		return Access(size - 1 - n);
	else
		throw std::out_of_range(
			"AccessFromEnd(int n), n must be a positive integer, less than sizeof(List)");
}

void LinkedList::PushFront(int value) {
	// TAIL: PushFront() must adjust tail in single-item list
	//			w/o tail pointer, only need the else condition.
	if (head == NULL) {
		head = create(value, head);
		tail = head;
	}
	else
		head = create(value, head);
	size++;
}

void LinkedList::PushBack(int value) {
	// TAIL: PushBack() is O(1) with tail pointer
	if (isEmpty()) {
		head = create(value, NULL);
		tail = head;
	}
	else {
		tail->next = create(value, NULL);
		tail = tail->next;
	}

	/* TAIL: PushBack() code pre-tail pointer
	if (isEmpty()) {
		head = create(value, NULL);
	}
	else {
		Node * current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = create(value, NULL);
	} */
	size++;
}

void LinkedList::Insert(int index, int value) {
	if (index <= 0 || index >= size) {
		throw std::out_of_range("Attempted to Insert() outside of list range.");
	}
	else if (index == (size - 1)) {
		tail->next = create(value, NULL);
		tail = tail->next;
		size++;
	}
	else {
		Node* current = head;
		int i = 0;
		while (i < index) {
			current = current->next;
			i++;
		}

		Node* temp = create(value, current->next);
		current->next = temp;
		size++;
	}
}

void LinkedList::PopFront() {
	Node* temp = head->next;
	delete head;
	head = temp;
	// TAIL: PopFront() adjust tail for single item list.
	if (head == NULL)
		tail = head;
	size--;	
}

void LinkedList::PopBack() {
	// TAIL: PopBack() time doesn't decrease w/ a tail pointer
	//			in a singly-linked list because we still need to adjust it.
	if (size <= 0) {
		throw std::out_of_range("Nothing to Pop().");
	}
	else {
		Node *cursor = head;
		while (cursor->next != tail) {
			cursor = cursor->next;
		}

		delete tail;
		tail = NULL;  // Unnecessary?
		tail = cursor;
		tail->next = NULL;
		size--;

		/*
		for (int i = 0; i < size - 1; i++) {
			cursor = cursor->next;
		} */

	}
	/* pre *tail pointer
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
	*/
	
}

void LinkedList::RemoveValue(int value) {
	// For reference: https://www.cs.bu.edu/teaching/c/linked-list/delete/
	//printf("Attempting to RemoveValue(%d)...\n", value);

	Node *current = head;
	Node *previous = NULL;
	while (current->item != value && current->next != NULL) 
	{
		previous = current;
		current = current->next;
	}

	if (current->item == value) {
		if (previous == NULL) {
			head = current->next;
			// Account for tail in case of removing item from one item list
			// this fixes case where list = [0]
			// without breaking case where list = [0, 1, 2, 3, 4] remove 3.
			if (head == NULL)
				tail = NULL;
		}
		else {
			if (current == tail) 
				tail = previous;
			previous->next = current->next;
		}
		delete current;
		size--;
	}
	else {
		throw std::runtime_error("Value not found in list, cannot remove!");
		//printf("%d not found, cannot remove!\n", value);
	}
}

void LinkedList::Erase(int value) {
	printf("Removing all items with value %d...\n", value);
	int count = 0;	
	Node *current = head;
	Node *previous = NULL;
	for (int i = 0; i < size; i++) {
		// handle front case
		if (current->item == value) {
			if (previous == NULL) {
				head = current->next;
				delete current;			
				current = head;
			}
			// handle middle case
			else {
				previous->next = current->next;
				delete current;
				current = previous->next;
			}
			// TAIL: Adjust tail when erasing end item or from single item list
			if (current == NULL) {
				tail = previous;
			}
			count++;		
		}
		// handle non-case
		else {
			previous = current;
			current = current->next;
		}
	}
	size -= count;
	printf("Removed %d items.\n", count);
}

void LinkedList::Reverse() {
	// TODO, TAIL: Check that this works.
	tail = head;
	// TODO: Study this cause it works and I wrote it but it hasn't really sunk in yet.

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
		delete current;
		current = head;
	}
	delete head;
	// TAIL: Don't need to free tail because head == tail?

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