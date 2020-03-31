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
#include "kmp.h"

#define BUFFER 1000
#define BFSZ 10000

struct node *addList(struct node *list, char *n);

struct node
{
    char value[BFSZ];
    struct node *next;
};

struct node *first = NULL;
struct node *second = NULL;

struct node *addList(struct node *list, char *n)
{
    struct node *new_node;

    new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("Error: malloc failed in add_to_list\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->value, n);
    new_node->next = list;
    return new_node;
}

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
        exit(EXIT_FAILURE);
    }
    return 0;
}

void executeAlgorithm(char *path, char *word)
{ //, Match* posizione){

    char *shift;

    int n = strlen(path);
    int m = strlen(word);

    shift = KMP(path, word, n, m);
    if (shift != 0)
        printf("%s Pattern occurs with shift %d\n", word, shift);
}

void Analize(char *file)
{
    //const char str2[] = "[r]";
    int str2 = '[r]';

    //if (ret != 0) //strchr(file, '[r]')
    // se nell'input immesso e' presente il parametro di ricorsione setta il flag ad 1;
    if (strchr(file, str2) != NULL)
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

void initialize(char *wordFile, char *inputFile)
{
    struct node *new_node;

    if (wordFile == NULL || inputFile == NULL)
    {
        printf("Parametri necessari non inseriti");
        exit(EXIT_FAILURE);
    }

    pathExtract(wordFile, 0);
    pathExtract(inputFile, 1);

    // for (new_node = first; new_node != NULL; new_node = new_node->next)
    // {
    //     if ((isDirectory(new_node->value)) == 1 || (isRegular(new_node->value) == 1))
    //     {
    //         printf("%s\n", new_node->value);
    //     }
    //     else if ((new_node->value[0] >= 'a' && new_node->value[0] <= 'z') || (new_node->value[0] >= 'A' && new_node->value[0] <= 'Z'))
    //     {
    //         printf("False%s\n", new_node->value);
    //     }
    //     else
    //     {
    //         continue;
    //     }
    // }

    for (new_node = second; new_node != NULL; new_node = new_node->next)
    {
        if ((isDirectory(new_node->value)) == 1 || (isRegular(new_node->value) == 1))
        {
            printf("%s\n", new_node->value);
            Analize(new_node->value);
        }
        else
        {
            continue;
        }
    }
}

char *pathExtract(char *file, int tmp) //, Node* primoReport) //,char *wordSave[]
{
    struct node *new_node;

    FILE *fp = fopen(file, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Unable to open file\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER];
    char(*text)[sizeof buffer] = NULL;
    char(*temp)[sizeof buffer] = NULL;

    int position = 0;
    char *txt[50];

    //static char * str[BUFFER_SZ][BUFFER_SZ];

    size_t numlines = 0;

    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        ++numlines;
        /* Allocate space for next line */
        temp = realloc(text, sizeof(*text) * numlines); //
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
                //position++;
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
        if (tmp == 0)
        {
            first = addList(first, text[i]);
        }
        if (tmp == 1)
        {
            if ((isDirectory(text[i])) == 1 || (isRegular(file) == 1)) //(text[i][0] == '/')
            {
                second = addList(second, text[i]);
            }
            //if ((text[i][0] >= 'a' && text[i][0] <= 'z') || (text[i][0] >= 'A' && text[i][0] <= 'Z'))
            if ((text[i][0] >= 'a' && text[i][0] <= 'z') || (text[i][0] >= 'A' && text[i][0] <= 'Z'))
            {
                for (new_node = first; new_node != NULL; new_node = new_node->next)
                {
                    txt[i] = strtok(new_node->value, "\r\n");
                    bubblesort(txt[i]);
                    executeAlgorithm(text[i], txt[i]);
                }
                position++;
            }    
        }
        if (position != 0)
            printf("%d\n", position);
    }
    free(text);
    return 0;
}

/* controlla che il nome sia un file o una directory, nel caso in cui fosse una directory */

void checkName(char *file)
{

    // Se l'input che viene immesso non e' una directory ma un file esegue la funzione di lettura del file
    // Le funzioni che si occupano di cio' fanno parte delle libc
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
}

/* Metodo per la scrittura? */

void fileWrite(char *output, Node *creaPrimoReport)
{
    //     FILE *out;
    //     printf("Output Name: ");
    //     scanf("%s", output);
    //     out = fopen(output, "w+");
    //     if (out != NULL)
    //     {
    //         Node *app = creaPrimoReport;
    //         while (app != NULL)
    //         {
    //             fprintf(out, "%s ", app->WORD);
    //             fprintf(out, "%d ", app->FILE);
    //             fprintf(out, "%d ", app->OCCURRENCES);
    //             app = (app->next);
    //         }
    //     }
    //     else
    //     {
    //         printf("Error!");
    //         exit(1);
    //     }
    //     fclose(out);
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
    return 0;
}