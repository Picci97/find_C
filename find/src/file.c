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
#include <stdbool.h>
#include "report.h"
#include "file.h"

#define BUFFER_SZ 100

KMP(path, word, n, m);
int fileExtension(char *filename);

int fileInDir(char *path)
{
    DIR *dp;
    struct dirent *ep;
    dp = opendir(path);

    if (dp != NULL)
    {
        while ((ep = readdir(dp)))
        {
            if (ep->d_name[0] != '.')
            {
                int sizePath = strlen(path) + strlen(ep->d_name) + 1;
                char filename[sizePath];

                strcpy(filename, path);
                strcat(filename, "/");
                strcat(filename, ep->d_name);
                //printf("%s\n", filename);

                if (isRegular(filename) == 1)
                {
                    if (fileExtension(filename) == 1) //== 1) // leggere file txt o exclude
                    {
                        printf("Nop");
                    }
                    else
                    {
                        pathExtract(filename, 1);
                    }
                }
                else
                {
                    /*RECURSIVE*/

                    if (recursive_flag == 1)
                    {
                        if (!isLink(filename))
                        {
                            if (isDirectory(filename))
                                fileInDir(filename);
                        }
                    }
                }
            }
        }
        (void)closedir(dp);
    }
    else
    {
        perror("Couldn't open the directory");
    }
    return 0;
}

void executeAlgorithm(char *path, char *word)
{ //, Match* posizione){

    int n = strlen(path);
    int m = strlen(word);

    KMP(path, word, n, m);
}

void Analize(char *file)
{
    if (strchr(file, '[r]'))
    // se nell'input immesso e' presente il parametro di ricorsione setta il flag ad 1;
    {
        // se presente setta il flag ad 1
        recursive_flag = 1;
        char *buf;
        buf = strtok(file, " ");

        checkName(buf);
    }
    else
    {
        checkName(file);
    }
}

void *initialize(char *wordFile, char *inputFile)
{

    char *word = malloc(sizeof(int) * 25);
    char *input;

    int i;

    if (wordFile == NULL || inputFile == NULL)
    {
        printf("Parametri necessari non inseriti");
        perror(-1);
    }

    //strcpy(word,pathExtract(wordFile,0));

    word = pathExtract(wordFile, 0);
    input = pathExtract(inputFile, 1);

}


char *pathExtract(char *file, int tmp) //, Node* primoReport) //,char *wordSave[]
{

    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SZ];
    char(*text)[sizeof buffer] = NULL;
    char(*temp)[sizeof buffer] = NULL;

    char * word;
    char * path;

    size_t numlines = 0;

    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        ++numlines;
        /* Allocate space for next line */
        temp = realloc(text, sizeof(*text) * numlines);
        if (temp == NULL)
        {
            fprintf(stderr, "Error in realloc()\n");
            exit(EXIT_FAILURE);
        }
        text = temp;

        /* Copy buffer to text, removing carriage returns and newlines */
        char *c = buffer;
        char *line = text[numlines - 1];
        while (*c != '\n' && *c != '\0')
        {
            if (*c != '\r')
            {
                *line++ = *c;
            }
            ++c;
        }
        *c = '\0';
    }

    if (fclose(fp) != 0)
    {
        fprintf(stderr, "Unable to close file\n");
    }

    for (size_t i = 0; i < numlines; i++)
    {
        //return strdup(text[1]);
        if (tmp == 0)
        {
            if ((text[i][0] >= 'a' && text[i][0] <= 'z') || (text[i][0] >= 'A' && text[i][0] <= 'Z'))
            {
                word = text[i];
                printf("%s", text[i]);
            }
        }
        if (tmp == 1)
        {
            if (text[i][0] == '/')
            {
                path = text[i];
                Analize(text[i]);
                //printf("%s",text[i]);
            }
            else
            {
                printf("%s", text[i]);
            }
        }
        else
        {
            continue;
        }
    }
    return strdup(*text);
    free(text);
}

/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */

char *checkName(char *file)
{
    // Se l'input che viene immesso non e' una directory ma un file esegue la funzione di lettura del file
    // Le funzioni che si occupano di cio' fanno parte delle libc
    //printf("Input_%s",file);
    if (isDirectory(file) == 0)
    {
        if (isRegular(file) == 1)
        {
            pathExtract(file, 1);
        }
    } // Se l'input e' una directory esegue la funzione fileInDir che si occupa di leggere il contenuto di essa
    else if (isDirectory(file) == 1)
    {
        fileInDir(file);
    }
    // Se l'input non viene riconosciuto restituisce un errore di lettura
    else
    {
        printf("error reading!");
        error(1);
    }
}

/* Metodo per la scrittura? */

void fileWrite(char *output, Node *creaPrimoReport)
{
    FILE *out;
    printf("Output Name: ");
    scanf("%s", output);
    out = fopen(output, "w+");
    if (out != NULL)
    {
        Node *app = creaPrimoReport;
        while (app != NULL)
        {
            fprintf(out, "%s ", app->WORD);
            fprintf(out, "%d ", app->FILE);
            fprintf(out, "%d ", app->OCCURRENCES);
            app = (app->next);
        }
    }
    else
    {
        printf("Error!");
        exit(1);
    }
    fclose(out);
}

int isDirectory(char *path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
        return 0;

    return S_ISDIR(statbuf.st_mode);
}

int isRegular(char *path)
{
    struct stat path_stat;

    stat(path, &path_stat);

    return S_ISREG(path_stat.st_mode);
}

int isLink(char *path)
{
    struct stat path_stat;
    lstat(path, &path_stat);

    return S_ISLNK(path_stat.st_mode);
}

void readReport(char *read)
{
    /* FILE *in;
    printf("Report to read: ");
    scanf("%s", read);
    in = fopen(read, "r");
    if (in != NULL)
    {
        Node *app = creaPrimoReport;
        while (app != NULL)
        {
            fprintf(out, "%s ", app->WORD);
            fprintf(out, "%d ", app->FILE);
            fprintf(out, "%d ", app->OCCURRENCES);
            app = (app->next);
        }
    }
    else
    {
        printf("Error!");
        exit(1);
    }
    fclose(in); */
}
//Controlla il tipo di estensione e se necessario la salta

void support(char *exclude)
{
    FILE *fex = fopen("test/exclude.txt", "w");
    fprintf(fex, "%s", exclude);
    fclose(fex);
}

int fileExtension(char *filename)
{
    char *point;
    point = filename + strlen(filename);

    FILE *fe = fopen("test/exclude.txt", "r");
    char buffer[6];

    while (fgets(buffer, sizeof buffer, fe) != NULL)
        buffer[strlen(buffer) - 1] = '\0';

    //printf("%s",buffer);
    if ((point = strrchr(filename, '.')) != NULL)
    {
        if (strcmp(point, buffer) == 0)
        {
            printf("test\n");
            return 1;
        }
    }
}

/* void searchInDirectory(char *dirname)
{
    DIR *dir;
    struct dirent *dirp;
    dir = opendir(dirname);
    chdir(dirname);
    while ((dirp = readdir(dir)) != NULL)
    {
        if (dirp->d_type == 4)
        {

            if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            {
                continue;
            }
            printf("%s %s\n", "FOLDER", dirp->d_name);

            if (recursive_flag == 1)
            {
                searchInDirectory(dirp->d_name);
            }
        }
        else
        {
            if (fileExtension(dirp->d_name) == true)
            {
                return;
            }
            else
            {
                pathExtract(dirp->d_name);
            }
        }
    }
    chdir("..");
    closedir(dir);
} */