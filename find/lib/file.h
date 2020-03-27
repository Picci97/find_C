//void *fileOpen(char *words, char *inputs);//, Node* primoReport);

#define length 2048

static int recursive_flag = NULL;
static char *logFile;
static Node *firstNode;

//char *pathFile(char *file);
void * initialize (char * wordFile, char * inputFile);
char *pathExtract(char *file, int temp);
char *pathFile(char *fileInput, char *fileWord);
void executeAlgorithm(char *path, char *word); //, Match* posizione);
char *checkName(char *file);
int isRegular(char *path);
int isDirectory(char *path);
void support (char * exclude);