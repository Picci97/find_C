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

int main(int argc, char *argv[]){
  char word [110];
  char input [110];
  printf("word: ");
  scanf("%s",word);
  printf("input: ");
  scanf("%s",input);

  fileOpen(word,input);
  return 0;
}
    

    //KMP(text, pattern, n, m);

    /*
  int c;
  if(argc==1){
      printf("Non sono presenti i parametri necessari\n"); 
      abort();
  }
  while ((c = getopt(argc, argv, "iowevrh:"))!= -1) {
      switch (c)
      {
      case 'i':

        break;
      
      case 'w':

        break;

      case 'o':
      printf("ebbe");
      //metodo da implementare si occupa dell'output del file
      //  fileWrite();
        break;
      case 'e':
        //metodo da implementare si occupa dell'esclusione del file con specifiche estensioni

        break;
      case 'v':
        //metodo da implementare che permette di visionare il processo di analis(?)

        break;
      case 'r':
        //metodo che si occupa del report del file, da revisionare
        break;

      case 'h':
      printHelp();

      default:
      abort();
      }
    }*/
/*
void printHelp()
{
    printf("find [words] [inputs]\n");
    printf("\tswordx counts the occurrencies of each word input files and print them into a new output file.\n");
    printf("\n");
    printf("\t[inputs]\n");
    printf("\t\t files or Directory to read\n");
    printf("\t[words]\n");
    printf("\t\t Word to read\n");
    printf("\t\t -h | -help : print help message \n");
    printf("\t\t -o <file> | -output <file> : write the result in the <file> (find.out by default)\n");
    printf("\t\t -e <file> | -exclude <file> : exclude <file> from the statistic \n");
    printf("\t\t -r | -report : consider alphabetic characters only \n");
    printf("\t\t -v <file> | -verbose <file> : write log informations in <file> \n");
    printf("\t\t\t\t time : file processing time \n");
    printf("\t\t -u <file> | -update <file> : if swordx.out (or another output file specified) is present, write on file <file>,\n");
    printf("\t\t  with the same output file format , the word list with the related changes respect the previous program execution.\n");
    printf("\n");
}*/