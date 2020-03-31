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

void sortStrings(char * names[])
{
	char *tmp;
	int i = 0, j;
	for (i; names[i]; i++)
	{
		for (j = 0; names[j]; j++)
		{
			if (strcmp(names[i], names[j]) < 0)
			{
				tmp = names[i];
				names[i] = names[j];
				names[j] = tmp;
			}
		}
	}
}