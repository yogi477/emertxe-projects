#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SUCCESS 0
#define FAILURE -1

//file list
typedef struct node
{
    char filename[50];
    struct node *filelink;
}Slist;

//main node list
typedef struct mainnode
{
    int filecount;
    char word[20];
    struct subnode *sublink;
    struct mainnode *mainlink;
}main_node;

//sub node link
typedef struct subnode
{
    int wordcount;
    char filename[30];
    struct subnode *sublink;  
}sub_node;

//hashtable
typedef struct hashtable
{
    int index;
    struct mainnode *link;
}hashtable;

int create_database(Slist **filelist,hashtable hash[],main_node **node,sub_node **subnode);

void create_indexlist(hashtable hash[],Slist **filelist,main_node **node,sub_node **subnode);

void display_output(hashtable *hash);

char* input_from_user(void);

char* string_token (char* input_string);

int openfiles(char *filename);

int validation(int argc,char *argv[],Slist **head);

int insert_at_last(Slist **head, char *data);

void print_list(Slist *head);

void initialize_hashtable(hashtable arr[]);

int create_nodes(Slist *temp,FILE *ptr,char *str,main_node **hash_link);

void write_databasefile(hashtable *hash);

int search (hashtable *hash);

int sl_delete_list(Slist **head);

int create_nodes_update(char *str,char *filename,main_node **hash_link);

#endif