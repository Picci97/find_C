#ifndef REPORT_H
#define REPORT_H


typedef struct Node { 
    char WORD;
    char FILE;
    //int TOTAL;
    //struct file;
    int *OCCURRENCES;
    struct Match* Posizione;

    struct Node* next; 
}Node;
/*
typedef struct file {
    char path;
    int occurrences;
    struct posizione;

    struct file *next;
}file;
*/
typedef struct Match {
    int RIGA;
    int COLONNA;

    struct Match *next;
}Match;

Node* creaPrimoReport();
Node* creaNuovoReport(char* word, int* occurrences, Match* posizione,char* filePath, Node* primo);
#endif