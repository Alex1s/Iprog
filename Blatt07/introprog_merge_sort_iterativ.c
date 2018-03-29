/* === INTROPROG ABGABE ===
 * Blatt 7, Aufgabe 1
 * Tutorium: t25
 * Gruppe: g01
 * Gruppenmitglieder:
 *  - Robert Jaschek
 *  - Alexis Victor Nicolas Bagia
 * ========================
 */

#include <stdio.h>
#include <stdlib.h>
#include "introprog_input_merge_sort.h"

/*
 Diese Funktion fügt zwei bereits sortierte Arrays 
 zu einem sortierten Array zusammen
 
 array : Pointer auf das Array
 first : Index des ersten Elements (Beginn) des (Teil-)Array
 middle: Index des mittleren Elements des (Teil-)Array
 last  : Index des letzten Elements(Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
	int sorted_count = (last - first) + 1;
	int* sorted = malloc(sorted_count * sizeof(int));
	
	int index_left = first;
	int index_right = middle + 1;
	int index_sorted = 0;
	
	while (index_left <= middle && index_right <= last) {
		if (array[index_left] <= array[index_right]) {
			sorted[index_sorted++] = array[index_left++];
		} else {
			sorted[index_sorted++] = array[index_right++];
		}
	}
	
	while (index_left <= middle) {
		sorted[index_sorted++] = array[index_left++];
	}
	
	while (index_right <= last) {
		sorted[index_sorted++] = array[index_right++];
	}
	
	int index_array = first;
	for (int i = 0; i < sorted_count; i++) {
		array[index_array++] = sorted[i];
	}
	
	free(sorted);
}

/*
 Diese Funktion implementiert den rekursiven Mergesort 
 Algorithmus  auf einem Array. Sie soll analog zum Pseudocode
 in Listing 1 implementiert werden.
 
 array: Pointer auf das Array
 first: Index des ersten Elements des (Teil-)Array
 last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last)
{
	int step = 1;
	while (step <= last) {
		int left = 0;
		while (left <= last - step) {
			int middle = left + step - 1;
			if (middle > last) {
				middle = last;
			}
			
			int right = left + 2 * step - 1;
			if (right > last) {
				right = last;
			}
			
			merge(array, left, middle, right);
			
			left += 2 * step;
		}
		step *= 2;
	}
}

/*
 Hauptprogramm.
 
 Liest Integerwerte aus einer Datei und gibt diese sortiert 
 im selben Format über die Standardausgabe wieder aus.
 
 Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl>  <dateipfad>
 */
int main (int argc, char *argv[])
{
	if (argc!=3) {
		printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
		exit(2);
	}
	
	int max_count = atoi(argv[1]);
	char *filename = argv[2];
	
	int* array = malloc(max_count * sizeof(int));
	
	int len = read_array_from_file(array, max_count, filename);
	
	printf("Eingabe:\n");
	print_array(array, len);
	
	merge_sort(array, 0, len - 1);
	
	printf("Sortiert:\n");
	print_array(array, len);
	
	free(array);
	
	return EXIT_SUCCESS;
}
