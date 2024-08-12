#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// Function to create and return a new empty list.
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Function to print the contents of a list.
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%d", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
	ListNodePtr new_node = malloc(sizeof * new_node);

	new_node->data = data;
	new_node->next = self->head;
	self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = data;
	new_node->next = NULL;

	while (current != NULL && current->data < data) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // at front
		new_node->next = current;
		self->head = new_node;
	}
	else {                     // middle
		new_node->next = current;
		prev->next = new_node;
	}
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (current->data == data) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}

// Function to test the Linked List
void list_test() {
	List newList = new_list(); //creating new list

	printf("Testing insert_at_front... \n");

	int numbers[] = { 5, 3, 7, 2, 0 };
	for (int i = 0; i < 5; i++) {
		insert_at_front(&newList, numbers[i]);
	}
	printf("Expected: 0, 2, 7, 3, 5 \n");
	printf(" Result:");

	print_list(&newList);
}

void list_adhoc_test(List* self) {
	List newList = new_list();
	int quit;

	while (!quit) {
		int value;
		printf("\nMenu\n");
		printf("0. Exit\n");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Print\n");
		printf("\nEnter choice\n");
		scanf("%d", &value);

		switch (value) {
		case 0:
			quit = 1;
			break;
		case 1:
			option_insert(&newList);
			break;
		case 2:
			option_delete(&newList);
			break;
		case 3:
			option_print(&newList);
			break;
		default:
			printf("Please enter a different number. \n");
		}
	}
}

// A Function that will allow for the user to insert a value into the list
void option_insert(List* self) {
	int input;
	printf("Enter a value to insert: ");
	scanf("%d");
	insert_at_front(self, input);
}

// Function that will allow the user to delete a value of their choosing from the list using the delete_list function
void option_delete(List* self) {
	int input;
	printf("Enter a vaule to delete: ");
	scanf("%d");
	delete_list(self, input);
}

void option_print(List* self) {
	printf("Current List: ");
	print_list(self);
}

// New Function 1. Reversing a list
List reverse(List(*self) {
	// Creating a new list thats empty and will be used to store the reversed values
	List reversedList = new_List();
	// Going over original list and adding each value to the from of the new list
	for (ListNodePtr current = self->head; current != NULL; current = current = current->next) {
		insert_at_front(&reversedList, current->data);
	}
	// returning the reversed new list
	return reversedList;
}

// New Function 2. Merging two ordered lists into a single ordered list
List merge(List* list1, List* list2) {
	// Creating a empty list that'll hold the merged values
	List mergedList = new_list();
	// initializing pointers that'll traverse the input lists
	ListNodePtr current1 = list1->head, current2 = list2->head);
	// While loop that will merge untill both lists are empty
	while(current1 != NULL || current2 != NULL) {
		// if current2 is Null or current 1 has a smaller value
		if (current2 == NULL || (current1 != NULL && current1->data < current2->data)) {
			// put current list 1 into the merged list then move onto the next node in list 1
			insert_in_order(&mergedList, current1->data);
			current1 = current1->next;
		} else 
	{   // insert the current list 2 into the merged list then moveont the next node in list 2
		insert_in_order(&mergedList, current2->data);
		current2 = current2->next;
	}
		// return the merged list
	return mergedList;
}
