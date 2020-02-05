#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "kmp.h"
#include "report.h"

#define MAX 512000

//void dirOpen(char *basePath, const int root);
//FILE *writeFile(char *output);
void listFilesRecursively();
void kmp();
void printHelp();

//void fileOpen(char *words, char *inputs);
//typedef parole;

/*Metodo per la ricorsione del file*/
void listFilesRecursively(char *basePath)/*Non funzia D:*/
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    dp = readdir ( dir );

    // Unable to open directory stream
    if (dp != NULL){
        while (dp != NULL )
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {
            printf("%s\n", dp->d_name);

            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
            }
        }
    }else {
      perror ( "Word o Input file non trovato!" );
      exit(-1);
    }
    closedir(dir);
}
/* Metodo per la lettura del file Word, parole da cercare */
void fileOpen(char *words,char *wordSave[])
{
    char word[500]; //= malloc(sizeof(words));
  
    printf("Enter word: ");
    scanf("%s",words);

    wordSave[MAX];

    FILE *file = fopen ( words, "r" );
    
    if ( file != NULL )
       {    
            while ( fgets ( word, sizeof(word), file ) != NULL ) { /* leggi la linea */
                
                int size = 0;                                
                wordSave[size] = malloc(2000);
                strcpy(wordSave[size],word);
                //printf("%s", wordSave[size]);
                size++;
                }
            fclose ( file );
        }
    else
    {
      perror ( "Word o Input file non trovato!" );
      exit(-1);
    }
}
/* Metodo per la lettura del file di Input, path da verificare */
void fileOpenInput(char *inputs){
    char input;
    
    printf("Enter input file Path: ");
    scanf("%s",inputs);
    /*
    char *inputIndirizzo[MAX];
    char actualpath[500];
    char *path[MAX];
    //char filename[MAX];*/
    char *ch;

   FILE *file2 = fopen ( inputs,"r");
   if ( file2 != NULL)
   {
       
       while ( fgets (input, sizeof input, file2) != NULL)
       {/*
           if(ch = strchr(input, '[r]'))
            {/*
                *path = strtok(input," ");
                strcpy(actualpath,path);
                //path = realpath(input, actualpath);
                listFilesRecursively(actualpath);
                printf("true");
                printf("%s",input);*/
            
       }
       fclose(file2);
   } else {
       perror ( "Input file non trovato!" );
       exit(-1);
   }
}

/* Metodo per la scrittura? */

void fileWrite (char *output) {
    FILE *out;

    printf("Output Name: ");
    scanf("%s",output);

    out = fopen(output, "w+");
    if(out != NULL){

    printf("Output salvato nella cartella del Project");
//    fputs(reports,fp);

    fclose(out);
    } else {
      printf("Error!");
      exit(1);
    }
    
}

void openDir(char *fileInput){
    DIR *dir;
    struct dirent *dp;
    if ((dir = opendir (fileInput)) == NULL) // Non Cartella
    {
    
    }
    while ((dp = readdir (dir)) != NULL) { // Legge cartella
    }
{
    //1
    FILE *filePointer;
    char ch;
    //2
    filePointer = fopen(fileInput, "r");
    //3
    if (filePointer == NULL)
    {
        printf("File is not available \n");
    }
    else
    {
        //4
        while ((ch = fgetc(filePointer)) != EOF)
        {
            if(ch = strchr(input, '[r]')){
                printf("true");
                listFilesRecursively(ch);
            }
        }
    }
    //5
    fclose(filePointer);
    return 0;
}
}
    

int main(int argc, char *argv[]){
    char word[200]; 
    char input[200];
//    char *wordSave[5200];
//    char *wordpippo[5200];

    //fileOpen(word,wordSave);
    //fileOpen(word,wordpippo);
    printf("Enter input file Path: ");
    scanf("%s",input);
    fileOpenInput(input);
    listFilesRecursively(input);
    //printf("%s,word");
    //printf("%s", wordSave[1]);
    //printf("%s",wordpippo[1]);
//  char path[100];
//  char inputs[100];
}/*
    // Input path from user
    printf("Enter path to list files: ");
    scanf("%s", path);

    listFilesRecursively(path);*/

//    kmp(words,inputs);
    //printf("%s",words);
    
  int c; 

//  printf("Program Name Is: %s",argv[0]); 
/*

  if(argc==1){
      printf("Non sono presenti i parametri necessari\n"); 
      abort();
  }
  while ((c = getopt(argc, argv, "iowevrh:"))!= -1) {
      switch (c)
      {
      case 'i':

        fileOpenInput(inputs);
        break;
      
      case 'w':
        printf("Enter word file Path: ");
        fileOpenWord(words);
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
      };
    }

}
void printHelp(){
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
}
//    char *symlinkpath = argv[1];
/*
    char *symlinkpath = ("../../Pubblici");
    char actualpath [PATH_MAX];
    char *ptr;
    ptr = realpath(symlinkpath, actualpath);
    printf("%s",ptr);
    

/*
  char *realpath(const char *path, char *resolved_path);
  printf("%s",resolved_path)
  */