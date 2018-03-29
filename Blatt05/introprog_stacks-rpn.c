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
#include <math.h>   //definiert den speziellen Wert NaN für floats
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

/* Füge Element am Anfang des Stacks ein
 *
 * astack    - Ein Pointer auf den Stack.
 * value     - Zahl die als neues Element auf den Stack gelegt werden soll.
 */
void stack_push(stack* astack, float value)
{
    stack_element* new = malloc(sizeof(stack_element));
    
    new->value = value;
    new->next = astack->top;
    astack->top = new;
}

/* Nehme das letzte eingefügte Element vom Anfang des Stack
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * astack    - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* astack)
{
    if(astack->top == NULL) {
        return NAN;
    }
    
    stack_element* top = astack->top;
    float value = top->value;
    
    astack->top= top->next;
    free(top);
    
    return value;
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf dem Stacks aus.
 * Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann case die Zahl mithilfe von atof zu einem float
 *     und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack, führe die
 *     Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * astack    - Ein Pointer auf den Stack
 * token     - Eine Zeichenkette
 */
void process(stack* astack, char* token)
{
    if(is_number(token)) {
        stack_push(astack, atof(token));
    } else if(is_add(token) || is_sub(token) || is_mult(token)) {
        float right = stack_pop(astack);
        float left = stack_pop(astack);
        
        if(is_add(token)) {
            stack_push(astack, left + right);
        } else if(is_sub(token)) {
            stack_push(astack, left - right);
        } else if(is_mult(token)) {
            stack_push(astack, left * right);
        }
        
    }
}

/* Debugausgabe des Stack
 * Diese Funktion kannst du zum debugging des Stack verwenden.
 *
 * astack    - Ein Pointer auf den Stack
 */
void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}

/* Kreiere einen Stack mit dynamischen Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
    stack* astack = malloc(sizeof(stack));
    astack->top = NULL;
    return astack;
}

int main(int argc, char** args)
{
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;
    
    intro();
    while (taschenrechner_input(zeile) == 0) {
        // Erstes Token einlesen
        token = strtok(zeile, " ");
        
        while (token != NULL) {
            printf("Token: %s\n", token);
            // Stackoperationen durchführen
            process(astack, token);
            // Nächstes Token einlesen
            token = strtok(NULL, " ");
            print_stack(astack);
        }
        
        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);
        
        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);   //Räume Stack auf
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}