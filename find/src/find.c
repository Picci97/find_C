#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "report.h"
#include "file.h"
#include "kmp.h"

void printHelp();

int main(int argc, char *argv[])
{
  //char *outputFile = "find.out";

  // char *wordFile = "test/word.txt";
  // char *inputFile = "test/input.txt";

  char exclude;
  
  char * i;
  char * w;
  int c;

  if (argc < 1)
  {
    printf("Non sono presenti i parametri necessari\n");
    abort();
  }
  while ((c = getopt(argc, argv, "iowvreh")) != -1)
  {
    switch (c)
    {
    case 'i':
      i = "test/input.txt";
      // printf("Inserisci Input Path:\n");
      // scanf("%s",&i);
      break;

    case 'w':
      w = "test/word.txt";
      // printf("Inserisci Word Path:\n");
      // scanf("%s",&w);
      break;

    case 'o':
      //metodo da implementare si occupa dell'output del file
      //  fileWrite();
      break;

    case 'e':
      //metodo da implementare si occupa dell'esclusione del file con specifiche estensioni
      
      printf("Quali estensioni escludere? (aggiungere l'estensione con il (.)) \n");
      scanf("%s",&exclude);
      support(&exclude);
      break;

    case 'v':
      //metodo da implementare che permette di visionare il processo di analisi(?)

      break;
    case 'r':
      //metodo che si occupa del report del file, da revisionare
      //readReport();
      break;

    case 'h':
      printHelp();
      break;

    default:
      abort();
    }
  }
  initialize (w, i);
  
  return 0;
}

void printHelp()
{
  printf("\nfind [words] [inputs]\n");
  printf("\tfind counts the occurrencies of each word input files and print them into a new output file.\n");
  printf("\n");
  printf("\t[inputs]\n");
  printf("\t\t files or Directory to read\n");
  printf("\t[words]\n");
  printf("\t\t Word to read\n");
  printf("\t\t -h | -help : print help message \n");
  printf("\t\t -o <file> | -output <file> : write the result in the <file> (find.out by default)\n");
  //printf("\t\t -e <file> | -exclude <file> : exclude <file> with specific extension \n");
  printf("\t\t -r | -report : consider alphabetic characters only \n");
  printf("\t\t -v <file> | -verbose <file> : write log informations in <file> \n");
  printf("\t\t\t\t time : file processing time \n");
  printf("\n");
}