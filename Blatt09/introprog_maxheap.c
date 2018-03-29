/* === INTROPROG ABGABE ===
 * Blatt 9, Aufgabe 2
 * Tutorium: t25
 * Gruppe: g01
 * Gruppenmitglieder:
 *  - Robert Jaschek
 *  - Alexis Victor Nicolas Bagia
 * ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"

/* Reserviere Speicher für einen Heap
 *
 * Der Heap soll dabei Platz für capacity Elemente bieten.
 *
 * Um konsistent mit den Parametern für malloc zu sein, ist capacity
 * als size_t (entspricht unsigned long auf x86/64) deklariert.
 * Da es sauberer ist, sind auch alle Indizes in dieser Aufgabe als
 * size_t deklariert. Ob man size_t oder int als Index für ein Array
 * verwendet, macht in der Praxis (auf x86/64) nur bei Arrays
 * mit mehr als 2.147.483.647 Elementen einen Unterschied.
 */
heap* heap_create(size_t capacity) {
	heap* h = malloc(sizeof(heap));
	
	h->capacity = capacity;
	h->elements = malloc(h->capacity * sizeof(int));
	h->size = 0;
	
	return h;
}

/* Stellt die Heap Bedingung an Index i wieder her
 *
 * Vorraussetzung: Der linke und rechte Unterbaum von i
 * erfüllen die Heap-Bedingung bereits.
 */
void heapify(heap* h, size_t i) {
	size_t left = 2 * i + 1;
	size_t right = left + 1;
	
	size_t largest = i;
	if (left < h->size && h->elements[left] > h->elements[largest]) {
		largest = left;
	}
	if (right < h->size && h->elements[right] > h->elements[largest]) {
		largest = right;
	}
	
	if (largest != i) {
		int i_value = h->elements[i];
		
		h->elements[i] = h->elements[largest];
		h->elements[largest] = i_value;
		
		heapify(h, largest);
	}
}

/* Holt einen Wert aus dem Heap
 *
 * Wenn der Heap nicht leer ist, wird die größte Zahl zurückgegeben.
 * Wenn der Heap leer ist, wird -1 zurückgegeben.
 */
int heap_extract_max(heap* h) {
	if (!h->size) {
		return -1;
	}
	
	int max = h->elements[0];
	h->elements[0] = h->elements[h->size -1];
	h->size--;
	
	heapify(h, 0);
	
	return max;
}

/* Fügt einen Wert in den Heap ein
 *
 * Wenn der Heap bereits voll ist, wird -1 zurückgegeben,
 */
int heap_insert(heap* h, int key) {
	if (h->size == h->capacity) {
		return -1;
	}
	
	h->size++;
	
	size_t i = h->size - 1;
	size_t parent = (i - 1) / 2;
	while (i > 0 && h->elements[parent] < key) {
		h->elements[i] = h->elements[parent];
		
		i = parent;
		parent = (i - 1) / 2;
	}
	h->elements[i] = key;
	
	return 0;
}

/* Gibt den Speicher von einem Heap wieder frei
 */
void heap_free(heap* h) {
	free(h->elements);
	free(h);
}
