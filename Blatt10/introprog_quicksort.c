/* === INTROPROG ABGABE ===
 * Blatt 10, Aufgabe 1
 * Tutorium: t25
 * Gruppe: g01
 * Gruppenmitglieder:
 *  - Robert Jaschek
 *  - Alexis Victor Nicolas Bagia
 * ========================
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

/*****************************************************
 * Die benoetigten structs findet Ihr in quicksort.h *
 *****************************************************/

void init_list(list* mylist)
{
	mylist->first = NULL;
	mylist->last = NULL;
}

// Diese Funktion fügt Listenelemente an die Liste an
void insert_list(list_element* le, list* mylist)
{
	if (!mylist->last) {
		mylist->first = le;
	} else {
		mylist->last->next = le;
	}
	mylist->last = le;
}

// Speicher für Listenelemente wieder freigeben
void free_list(list* mylist)
{
	list_element* current = mylist->first;
	while (current) {
		list_element* next = current->next;
		free(current->password);
		free(current);
		
		current = next;
	}
}


// Namen, Zahlen Paare in Liste einlesen
void read_data(char* filename, list* mylist)
{
	FILE* file = fopen(filename, "r");
	
	int max_line_length = 255;
	char* line = malloc((max_line_length + 1) * sizeof(char));
	line[max_line_length] = '\0';
	
	int delimiter_index = -30000;
	while (fgets(line, max_line_length, file)) {
		int line_legth = strlen(line);
		
		for (int i = line_legth; i >= 0; i--) {
			if (line[i] == ' ') {
				delimiter_index = i;
				break;
			}
		}
		
		list_element* le = malloc(sizeof(list_element));
		
		le->next = NULL;

		le->count = atoi(line + delimiter_index);
		
		le->password = malloc(delimiter_index + 1);
		le->password[delimiter_index] = '\0';
		strncpy(le->password, line, delimiter_index);
		
		insert_list(le, mylist);
	}
	
	free(line);
	fclose(file);
}

// Liste teilen. Teillisten werden in left und right zurück gegeben
list_element* partition( list* input, list* left, list* right )
{
	list_element* pivot = input->first;
	
	list_element* current = pivot->next;
	while (current) {
		if (current->count < pivot->count) {
			insert_list(current, left);
		} else {
			insert_list(current, right);
		}
		current = current->next;
	}
	
	if (left->last) {
		left->last->next = NULL;
	}
	if (right->last) {
		right->last->next = NULL;
	}
	
	return pivot;
}

// Hauptfunktion des quicksort Algorithmus
void qsort_list(list* mylist)
{
	if (mylist->first == mylist->last) {
		return;
	}
	
	list left;
	init_list(&left);
	list right;
	init_list(&right);
	
	list_element* pivot = partition(mylist, &left, &right);
	
	qsort_list(&left);
	qsort_list(&right);
	
	if (!left.first) {
		mylist->first = pivot;
	} else {
		mylist->first = left.first;
		left.last->next = pivot;
	}
	
	if (!right.first) {
		pivot->next = NULL;
		mylist->last = pivot;
	} else {
		pivot->next = right.first;
		mylist->last = right.last;
	}
}

// Liste ausgeben
void print_list(list* mylist)
{
	list_element* current = mylist->first;
	while (current) {
		printf("%s %d\n", current->password, current->count);
		current = current->next;
	}
}
