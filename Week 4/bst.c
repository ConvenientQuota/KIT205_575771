#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

// create an empty bst
BST new_bst() {
	BST temp;
	temp.root = NULL;
	return temp;
}

// recursive function to find a value and return the containing node
BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
	if (self == NULL || (n == self->data_item)) { /* not present, or here */
		return self;
	}
	else if (n < self->data_item) {
		return find_bst_node(self->left, n);
	}
	else {
		return find_bst_node(self->right, n);
	}
}

// find a value in the tree and return the node
BSTNodePtr find_bst(BST* self, int n) {
	return find_bst_node(self->root, n);
}

// recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
	if (self == NULL) { /* found where to put it*/
		self = malloc(sizeof * self);
		self->data_item = n;
		self->left = self->right = NULL;
	}
	else if (n < self->data_item) {
		self->left = insert_bst_node(self->left, n);
	}
	else if (n > self->data_item) {
		self->right = insert_bst_node(self->right, n);
	}
	return self;
}

// insert a value into the tree
void insert_bst(BST* self, int n) {
	self->root = insert_bst_node(self->root, n);
}

// helper function for delete
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// recursive function to delete a value
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
	if (self != NULL) {
		if (n == self->data_item) { // found item 
			if (self->left != NULL && self->right != NULL) {
				// two child case 
				BSTNodePtr successor = min_node(self->right);
				self->data_item = successor->data_item;
				self->right = delete_bst_node(self->right, self->data_item);
			}
			else { // one or zero child case 
				BSTNodePtr to_free = self;
				if (self->left) {
					self = self->left;
				}
				else {
					self = self->right;
				}
				free(to_free);
			}
		}
		else if (n < self->data_item) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
	}
	return self;
}

// delete a value from the tree
void delete_bst(BST* self, int n) {
	self->root = delete_bst_node(self->root, n);
}

// recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %d ", self->data_item);
		print_in_order_bst_node(self->right);
		printf(")");
	}
}

// print the tree in order
void print_in_order_bst(BST* self) {
	print_in_order_bst_node(self->root);
}

// recursive function to detroy all node
void destroy_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		destroy_bst_node(self->left);
		self->left = NULL;
		destroy_bst_node(self->right);
		self->right = NULL;
		free(self);
	}
}

// destroy the tree
void destroy_bst(BST* self) {
	destroy_bst_node(self->root);
	self->root = NULL;
}

void bst_adhoc_test() {
	BST tree = new_bst();
	int quit = 0;
	int data;
	while (quit == 0) {
		printf("Insert a value or 0 to stop:\n");
		scanf("%d", &data);
		if (data != 0) {
			insert_bst(&tree, data);
		}
		else {
			quit = 1;
		}
	}

	printf("In-order: ", print_in_order_bst(&tree) );
	printf("Pre-order: ", pre_order_tree(&tree) );
	printf("Post-order: ", post_order_tree(&tree) );

	destroy_bst(&tree);
}

/* recursively printing the tree in pre order*/
void pre_order_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_ "); // print underscore to indicate a null node
	}
	else {
		printf("%d ", self->data_item); // printing data of current node
		pre_order_node(self->left); // print left subtree
		pre_order_node(self->right); // print right subtree
	}
}

// Print the tree pre-order
void pre_order_tree(BST* self) {
	pre_order_node(self->root); // start the traversal from the root
	printf("\n"); // printing newline at the end
}

// Recursive function to print post-order
void post_order_node(BSTNodePtr self) {
	if (self == NULL) { // if node is null
		printf("_ "); // printing underscore to determine if its a null node
	}
	else {
		post_order_node(self->left); // recursively printing the left subtree
		post_order_node(self->right); // printing right subtree
		printf("%d ", self->data_item); // pritnig the current data of the node
	}
}

// Print the tree post-order
void post_order_tree(BST* self) {
	post_order_node(self->root); // starting traversal from root node
	printf("\n"); //printng newline at the end
}

int tree_height_bst(BSTNodePtr self) {
	if (self == NULL) {
		return -1;
	}
	else {
		int left_height = tree_height_bst(self->left);
		int right_height = tree_height_bst(self->right);
		return (left_height > right_height && left_height : right_height);
	}
}

void tree_test() {
	BST tree = new_bst();

	insert_bst(&tree, 7);
	insert_bst(&tree, 2);
	insert_bst(&tree, 4);
	insert_bst(&tree, 9);
	insert_bst(&tree, 1);
	insert_bst(&tree, 5);

	printf("Tree's height:\n", tree_height(&tree));
}

int tree_height(BST* self) {
	return tree_height_bst(self->root);
}