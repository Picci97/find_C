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

void KMP(const char *X, const char *Y, int m, int n);

/*Metodo per la ricorsione del file*/
/*
void listFilesRecursively(char *basePath) /*Non funzia D:*/
/*
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    dp = readdir(dir);

    // Unable to open directory stream
    if (dp != NULL)
    {
        while (dp != NULL)
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
    } /*else {
      perror ( "Word o Input file non trovato!" );
      exit(-1);
    }*/
    /*closedir(dir);
}*/
/*
int *is_regular_file(char *len,int result)
{
    struct stat SBuff;
    stat(len, &SBuff);

    switch(SBuff.st_mode & S_IFMT){
        case S_IFREG:
            printf("%s is a file\n", len);
            result = 1;
            break;
        case S_IFDIR:
            printf("%s is a dir\n", len);
            result = 2; 
            break;
        case S_IFLNK:
            printf("%s is a sys\n", len);
            result = 3;
            break;
        default:
            printf("cocco");
            break;
    }
}*/

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        }
        else
        {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

/* Metodo per la lettura del file Word, parole da cercare */

void executeAlgorithm(char *path, char *word){
    int n = strlen(path);
    int m = strlen(word);
    KMP( path, word, n, m);
}

void *fileOpen(char *words, char *inputs)//, Node* primoReport) //,char *wordSave[]
{
    char *word = (char*)malloc(150*sizeof(char)); //= malloc(sizeof(words));
    char *input = (char*)malloc(150*sizeof(char));

    FILE *fileW = fopen ( words, "r" );
    FILE *fileI = fopen ( inputs, "r");

    if ( fileW != NULL || fileI != NULL)
       {    
            while ( fgets ( word, sizeof(word), fileW ) != NULL ) 
            {
                printf("%s",word);
            }
            while ( fgets ( input, sizeof(input), fileI ) != NULL )
            { 
                char *tempInput = strtok(input,"[r]");
                pathOpen(tempInput);//AAAAAA
                printf("%s",tempInput);
                //executeAlgorithm(input,word);
            }

        } else {
      perror ( "Word o Input file non trovato!" );
      exit(-1);
    }
    fclose ( fileW );
    fclose ( fileI );
}

/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */
void checkName(char* filename)
{
	filename = canPath(filename);
	/* se non è una directory fa l'update della lista passa a updateList il file, se no
	 *  apre la directory, controlla i file e fa l'updateList su ognuno di loro*/
	if(isDirectory(filename)== 0)
	{
		if (isRegular(filename) == 1)
		{
			if (logFile == NULL)
				updateList(filename);
			 /*LOG FILE __exec time*/
			else 
				UpdateListwLog(filename);
		}
	}
	else
		fileInDirUpdate(filename);
}


char *pathOpen(char *path)
{
    char *buffer;
    char *buffInput;

    FILE *paths = fopen(path, "r");
    if (paths != NULL)
    {
        while (fgets(buffer, sizeof(buffer), paths))
            {
                checkName(buffer)/*
                int recursive;
                if (isDirectory(buffer)){
                    if(strchr(buffer, '[r]')){
                        recursive = 1;
                    }else
                    {
                        recursive = 0;
                    }
                    buffInput = strtok(buffer, "[r]");
                    listFilesRecursively(buffer,recursive);*/
                }
                strcpy(buffInput,buffer);
            }
        fclose(paths);
        //fflush( paths );
    } else {
        perror("Errore nel file!");
        exit(-1);
    }
    return buffInput;
}
/*sub is 0 if the dir is a subdir, 1 otherwise
 * 1 -> not recursion*/


/* Metodo per la scrittura? */

void fileWrite(char *output)
{
    FILE *out;
    printf("Output Name: ");
    scanf("%s", output);
    out = fopen(output, "w+");
    if (out != NULL)
    {
        printf("Output salvato nella cartella del Project");
        fclose(out);
    }
    else
    {
        printf("Error!");
        exit(1);
    }
}
void listFilesRecursively(char *basePath, int recursive){
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s\n", dp->d_name);
            if(recursive == 1)// Construct new path from our base path
            {
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);

                listFilesRecursively(path,recursive);
            }
        }
    }
    closedir(dir);
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

int isDirectory(char *path) 
{
   struct stat statbuf;
   
   if (stat(path, &statbuf) != 0)
       return 0;
   
   return S_ISDIR(statbuf.st_mode);
}

int isRegular(char* path)
{
	struct stat path_stat;
    stat(path, &path_stat);
    
    return S_ISREG(path_stat.st_mode);
}

int isLink(char* path)
{
	 struct stat path_stat;
	 lstat(path, &path_stat);
	 
	 return S_ISLNK(path_stat.st_mode);
}