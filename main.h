#ifndef MAIN_H
#define MAIN_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct ShellVar
{
char *n;
char*val;
struct ShellVar *next;
} ShellVar;

typedef struct HistList
{
char *cmd;
struct HistList *next;
} HistList;

typedef struct AliasData
{
char *n;
char *val;
struct AliasData *next;
} AliasData;

extern char **environ;

int _atoi(char *s);
char **getallenv();
int setallenv(char **envin, char *newval);
char *_getenv(char *n);
int _setenv(char *n, char *val);
int _unsetenv(char *n);
int _getline(char **lineptr, int fd);
int _putchar(char c);
int _printenv(void);
void *_realloc(void *ptr, unsigned int o_size, unsigned int n_size);
char *_strtok(char *str, char *delim);
char *strtokqe(char *str, char *delim, int escflags);
AliasData **getalist();
char *getalias(char *n);
int setalias(char *n, char *val);
int unsetalias(char *n);
int aliascmd(char *av[]);
int _cd(char *av[]);
int checkpath(char *av[]);
int cmdcall(char *av[], char *cmd);
int builtincall(char *av[]);
void exitcleanup(char **av);
char ***getenviron();
char *_getpid();
ShellVar **getspecial();
ShellVar **getvars();
int help(char *cmd);
HistList **gethistory();
int sethist(char *cmd);
int print_hist(void);
int exit_hist(void);
int inputvalidator(char **buf, int fd);
int shintmode(void);
int scriptmode(char *av[]);
char *parsesetsvar(char *buf);
char *subsvars(char **buf);
char *cleanarg(char *arg);
char *tildeexpand(char *buf);
int parseargs(char **buf);
int initsvars(int ac, char **av);
char *getsvar(char *n);
int setsvar(char *n, char *val);
int unsetsvar(char *n);
int _strcmp(char *s1, char *s2);
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int linecounter(int increment);
char *itos(int digits);
int printerr(char *str);
int fprintstrs(int fd, char *str, ...);
char *_strchr(char *s, char c);
int main(int ac, char *av[], char **environ);

#endif
