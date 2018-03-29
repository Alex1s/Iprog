/* === INTROPROG ABGABE ===
 * Blatt 11, Aufgabe 2
 * Tutorium: t25
 * Gruppe: g01
 * Gruppenmitglieder:
 *  - Robert Jaschek
 *  - Alexis Victor Nicolas Bagia
 * ========================
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "avl.h"

// Berechnet die höhe eines Knotens.
int AVL_node_height(AVLNode* node)
{
	int height_left = node->left ? node->left->height : 0;
	int height_right = node->right ? node->right->height : 0;
	return 1 + (height_left > height_right ? height_left : height_right);
}

// Berechnet den balance-Wert eines Knotens.
int AVL_node_balance(AVLNode* node) {
	return (node->left ? AVL_node_height(node->left) : 0) - (node->right ? AVL_node_height(node->right) : 0);
}

// Durchläuft den AVL-Baum rekursiv in-order.
void AVL_in_order_walk_recursive(AVLNode* node) {
	if (!node) {
		return;
	}
	AVL_in_order_walk_recursive(node->left);
	printf("%d ", node->value);
	AVL_in_order_walk_recursive(node->right);
}

// Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus.
void AVL_in_order_walk(AVLTree* avlt)
{
	AVL_in_order_walk_recursive(avlt->root);
	printf("\n");
}

// Diese Funktion führt eine Linksrotation auf dem angegebenen Knoten aus.
// Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
// angepasst werden.
void AVL_rotate_left(AVLTree* avlt, AVLNode* x)
{
	AVLNode* right = x->right;
	x->right = right->left;
	if (right->left) {
		right->left->parent = x;
	}
	right->parent = x->parent;
	if (!x->parent) {
		avlt->root = right;
	} else if (x == x->parent->left) {
		x->parent->left = right;
	} else {
		x->parent->right = right;
	}
	right->left = x;
	x->parent = right;
	
	x->height = AVL_node_height(x);
	right->height = AVL_node_height(right);
}

// Diese Funktion führt eine Rechtsrotation auf dem angegebenen Knoten aus.
// Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
// angepasst werden.
void AVL_rotate_right(AVLTree* avlt, AVLNode* y)
{
	AVLNode* left = y->left;
	y->left = left->right;
	if (left->right) {
		left->right->parent = y;
	}
	left->parent = y->parent;
	if (!y->parent) {
		avlt->root = left;
	} else if (y == y->parent->left) {
		y->parent->left = left;
	} else {
		y->parent->right = left;
	}
	left->right = y;
	y->parent = left;
	
	y->height = AVL_node_height(y);
	left->height = AVL_node_height(left);
}

//Balanciere den Teilbaum unterhalb von node.
void AVL_balance(AVLTree* avlt, AVLNode* node)
{
	int balance = AVL_node_balance(node);
	
	if (balance == 2) {
		if (AVL_node_balance(node->left) < 0) {
			AVL_rotate_left(avlt, node->left);
		}
		AVL_rotate_right(avlt, node);
	} else if (balance == -2) {
		if (AVL_node_balance(node->right) > 0) {
			AVL_rotate_right(avlt, node->right);
		}
		AVL_rotate_left(avlt, node);
	}
}

// Fügt ein neues Element rekursiv in den AVL-Baum ein.
void AVL_insert_value_recursive(AVLTree* avlt, AVLNode* node, AVLNode* new)
{
	if (!node) {
		node = new;
		
		if (new->parent) {
			if (new->value < new->parent->value) {
				new->parent->left = new;
			} else {
				new->parent->right = new;
			}
		} else {
			avlt->root = new;
		}
	} else if (new->value < node->value) {
		new->parent = node;
		AVL_insert_value_recursive(avlt, node->left, new);
	} else if (new->value > node->value) {
		new->parent = node;
		AVL_insert_value_recursive(avlt, node->right, new);
	} else {
		free(new);
		return;
	}
	node->height = AVL_node_height(node);
	
	AVL_balance(avlt, node);
}

// Fügt der Wert value in den Baum ein.
// Die Implementierung muss sicherstellen, dass der Baum nach dem Einfügen
// immer noch balanciert ist!
void AVL_insert_value(AVLTree* avlt, int value)
{
	avlt->numberOfNodes++;
	
	AVLNode* new = malloc(sizeof(AVLNode));
	new->parent = new->left = new->right = NULL;
	new->value = value;
	
	AVL_insert_value_recursive(avlt, avlt->root, new);
}

// Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten rekursiv frei.
void AVL_remove_all_elements_recursive(AVLNode* node) {
	if (!node) {
		return;
	}
	AVL_remove_all_elements_recursive(node->left);
	AVL_remove_all_elements_recursive(node->right);
	free(node);
}

// Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten frei.
void AVL_remove_all_elements(AVLTree* avlt)
{
	AVL_remove_all_elements_recursive(avlt->root);
}
