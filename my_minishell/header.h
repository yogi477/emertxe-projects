#ifndef MAIN_H
#define MAIN_H
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include<ctype.h>
#include <pwd.h> 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct node 
{
    pid_t pid;
    char command[100];
    struct node *next;
}Cmd_list;

extern Cmd_list *cmd_list_head;
extern pid_t pid;
extern int sig_flag;
extern int stop_cnt;
void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void execute_internal_commands(char *input);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);
int execute_external_commands(char *input);
int pipe_fun(int argc,char *argv[]);

int insert_at_last();
Cmd_list* get_last();
void print_cmd_list();
void sig_handler2(int sig_num);
void sig_handler1(int sig_num);
#endif
