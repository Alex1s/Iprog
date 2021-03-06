/* === INTROPROG ABGABE ===
 * Blatt 2, Aufgabe 3
 * Tutorium: t25
 * Abgabe von: Alexis Victor Nicolas Bagia
 * ========================
 */

#include <stdio.h>
#include "introprog_complexity_steps_input.h"

long for_linear(int n, int* befehle)
{
	// Variablendeklaration
	(*befehle)++;	
	long sum = 0;

	// Variablendeklaration (i)
	(*befehle)++;	
	for(int i = 1; i <= n; ++i){
		// Vergleich (i <= n)
		(*befehle)++;

		// Variablenzuweisung (++i)
		(*befehle)++;

		// Variablenzuweisung
		(*befehle)++;
		sum += get_value_one();
	}
	// letzter Vergleich (i > n)
	(*befehle)++;
	
	// return
	(*befehle)++;
	return sum;
}

long for_quadratisch(int n, int* befehle){
	// Variablendeklaration
	(*befehle)++;	
	long sum = 0;

	// Variablendeklaration (i)
	(*befehle)++;	
	for(int i = 1; i <= n; ++i){
		// Vergleich (i <= n)
		(*befehle)++;

		// Variablenzuweisung (++i)
		(*befehle)++;

		// Variablendeklaration (j)
		(*befehle)++;	
		for(int j = 1; j <= n; ++j){
			// Vergleich (j <= n)
			(*befehle)++;
			
			// Variablenzuweisung (++j)
			(*befehle)++;

			// Variablenzuweisung
			(*befehle)++;
			sum += get_value_one();
		}
		// letzter Vergleich (j > n)
		(*befehle)++;
	}
	// letzter Vergleich (i > n)
	(*befehle)++;

	// return
	(*befehle)++;
	return sum;
}

long for_kubisch(int n, int* befehle)
{
	// Variablendeklaration
	(*befehle)++;
	long sum = 0;

	// Variablendeklaration (i)
	(*befehle)++;
	for(int i = 1; i <= n; ++i){
		// Vergleich (i <= n)
		(*befehle)++;
		
		// Variablenzuweisung (++i)
		(*befehle)++;

		// Variablendeklaration (j)
		(*befehle)++;
		for(int j = 1; j <= n; ++j){
			// Vergleich (j <= n)
			(*befehle)++;

			// Variablenzuweisung (++j)
			(*befehle)++;

			// Variablendeklaration (k)
			(*befehle)++;
			for(int k = 1; k <= n; ++k){
				// Vergleich (k <= n)
				(*befehle)++;

				// Variablenzuweisung (++k)
				(*befehle)++;

				// Variablenzuweisung
				(*befehle)++;
				sum += get_value_one();
			}
			// letzter Vergleich (k > n)
			(*befehle)++;
		}
		// letzter Vergleich (j > n)
		(*befehle)++;
	}
	// letzter Vergleich (i > n)
	(*befehle)++;

	// return
	(*befehle)++;
	return sum;
}


int main(int argc, char *argv[]) {

	const int WERTE[] = {5,6,7,8,9,10};
	const int LEN_WERTE = 6;
	const int LEN_ALGORITHMEN = 3;

	long befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
	long werte_array[LEN_ALGORITHMEN][LEN_WERTE];
	double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

	for(int j = 0; j < LEN_WERTE; ++j)
	{
		int n = WERTE[j];
		for(int i = 0; i < LEN_ALGORITHMEN; ++i)
		{
			printf("Starte Algorithmus %d mit Wert %d\n", (i+1), n);
			int anzahl_befehle = 0;
			int wert = 0;

			//Starte den Timer
			start_timer();

			//Aufruf der entsprechenden Funktion
			if(i==0)
			{
				wert = for_linear(n, &anzahl_befehle);
			}
			else if(i==1)
			{
				wert = for_quadratisch(n, &anzahl_befehle);
			}
			else if(i==2)
			{
				wert = for_kubisch(n, &anzahl_befehle);
			}

			//speichere Laufzeit, Rückgabewert und Anzahl ausgeführter Befehle ab
			laufzeit_array[i][j] = end_timer();
			werte_array[i][j] = wert;
			befehle_array[i][j] = anzahl_befehle;
		}
		printf("\n");
	}

	//Ausgabe der Rückgabewerte, Anzahl ausgeführter Befehle sowie der gemessenen Laufzeiten (in Millisekunden)
	printf("%3s \t%-28s \t%-28s \t%-28s\n", "","linear", "quadratisch", "kubisch");
	printf("%3s \t %5s %10s %10s\t %5s %10s %10s\t %5s %10s %10s\n", "n","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit");

	for(int j = 0; j < LEN_WERTE; ++j)
	{
		printf("%3d \t ",WERTE[j]);
		for(int i = 0; i < LEN_ALGORITHMEN; ++i)
		{
			printf("%5ld %10ld %10.4f \t ", werte_array[i][j], befehle_array[i][j], laufzeit_array[i][j]);
		}
		printf("\n");
	}

	return 0;
}
