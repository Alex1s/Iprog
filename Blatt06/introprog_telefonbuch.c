/* === INTROPROG ABGABE ===
 * Blatt 6, Aufgabe 2
 * Tutorium: t25
 * Gruppe: g01
 * Gruppenmitglieder:
 *  - Robert Jaschek
 *  - Alexis Victor Nicolas Bagia
 * ========================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

// Fügt einen Knoten mit der Telefonnummer phone und dem Namen name in den
// Binären Suchbaum bst ein.  Für den Suchbaum soll die Eigenschaft gelten, dass
// alle linken Kinder einen Wert kleiner gleich (<=) und alle rechten Kinder
// einen Wert größer (>) haben.
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
	// copy name
	long name_copy_length = strlen(name) + 1;
	char* name_copy = malloc(name_copy_length * sizeof(char));
	strncpy(name_copy, name, name_copy_length);
	name_copy[name_copy_length - 1] = '\0';
	
	// create a new node
	bst_node* new = malloc(sizeof(bst_node));
	new->phone= phone;
	new->name = name_copy;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	
	
	bst_node* parent = NULL;
	bst_node* current = bst->root;
	
	while (current) {
		parent = current;
		
		if (current->phone == new->phone) {
			perror("Telefonnummer existiert bereits.");
			return;
		}
		
		if (new->phone < current->phone) {
			current = current->left;
		} else {
			current= current->right;
		}
	}
	
	new->parent = parent;
	
	if (!parent) {
		bst->root = new;
	} else if (new->phone <= parent->phone) {
		parent->left = new;
	} else {
		parent->right = new;
	}
}

// Diese Funktion liefert einen Zeiger auf einen Knoten im Baum
// mit dem Wert phone zurück, falls dieser existiert. Ansonsten wird
// NULL zurückgegeben.
bst_node* find_node(bstree* bst, unsigned long phone) {
	bst_node* current = bst->root;
	
	while (current && current->phone != phone) {
		if (phone <= current->phone) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	
	return current;
}

// Gibt den Unterbaum von node in "in-order" Reihenfolge aus
void bst_in_order_walk_node(bst_node* node) {
	if (node) {
		bst_in_order_walk_node(node->left);
		print_node(node);
		bst_in_order_walk_node(node->right);
	}
}

// Gibt den gesamten Baum bst in "in-order" Reihenfolge aus. Die Ausgabe
// dieser Funktion muss aufsteigend soriert sein.
void bst_in_order_walk(bstree* bst) {
	if (bst != NULL) {
		bst_in_order_walk_node(bst->root);
	}
}

// Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
// "post-order" Traversierung, d.h. zurerst wird der linke und dann
// der rechte Teilbaum gelöscht. Anschließend wird der übergebene Knoten
// gelöscht.
void bst_free_subtree(bst_node* node) {
	if (node) {
		bst_free_subtree(node->left);
		bst_free_subtree(node->right);
		free(node->name);
		free(node);
	}
}

// Löscht den gesamten Baum bst und gibt den entsprechenden Speicher frei.
void bst_free_tree(bstree* bst) {
	if(bst != NULL && bst->root != NULL) {
		bst_free_subtree(bst->root);
		bst->root = NULL;
	}
}
