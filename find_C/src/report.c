#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "report.h"

Node* creaPrimoReport(){

	Node *nuovoReport = malloc(sizeof(Node));
	nuovoReport -> WORD = NULL;
	nuovoReport -> FILE = NULL;
	nuovoReport -> OCCURRENCES = NULL;
	nuovoReport -> Posizione = NULL;

	nuovoReport -> next = NULL;

	return nuovoReport;
}

Node* creaNuovoReport(char* word, int* occurrences, Match* posizione,char* filePath, Node* primo)
{
	Node *creaNuovoReport = malloc(sizeof(Node));
	creaNuovoReport -> WORD = strdup(word);
	creaNuovoReport -> FILE = strdup(filePath);
	creaNuovoReport -> OCCURRENCES = occurrences;
	creaNuovoReport -> Posizione = posizione;

	creaNuovoReport -> next = NULL;
	
	if (primo != NULL)
	{
		Node* app = primo;
		while (app -> next != NULL)
			app = app -> next;

		app -> next = creaNuovoReport;
	}
	return creaNuovoReport;
}