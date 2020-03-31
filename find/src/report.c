#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"

#define Max 100

Node *creaPrimoReport()
{

	Node *nuovoReport = malloc(sizeof(Node));
	nuovoReport->WORD = NULL;
	nuovoReport->FILE = NULL;
	nuovoReport->OCCURRENCES = NULL;
	nuovoReport->Posizione = NULL;

	nuovoReport->next = NULL;

	return nuovoReport;
}

Node *creaNuovoReport(char *filePath, char *word, int *occurrences, Match *posizione, Node *primo)
{
	Node *creaNuovoReport = malloc(sizeof(Node));
	creaNuovoReport->WORD = strdup(word);
	creaNuovoReport->FILE = strdup(filePath);
	creaNuovoReport->OCCURRENCES = occurrences;
	creaNuovoReport->Posizione = posizione;

	creaNuovoReport->next = NULL;

	if (primo != NULL)
	{
		Node *app = primo;
		while (app->next != NULL)
			app = app->next;

		app->next = creaNuovoReport;
	}
	return creaNuovoReport;
}

void sortStrings(char arr[][Max], int n) 
{ 
    char temp[Max];
  
    // Sorting strings using bubble sort 
    for (int j=0; j<n-1; j++) 
    { 
        for (int i=j+1; i<n; i++) 
        { 
            if (strcmp(arr[j], arr[i]) > 0) 
            { 
                strcpy(temp, arr[j]); 
                strcpy(arr[j], arr[i]); 
                strcpy(arr[i], temp); 
            } 
        } 
    } 
} 