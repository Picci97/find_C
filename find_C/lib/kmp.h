#define MAX_LENGTH 512

struct node {
   char data[MAX_LENGTH];
   struct node *next;
} strNode;


void kmp(char* cerca, char* frase);

void search(char *cerca, int dimC, int *controllo);