#ifndef MAIN_H
#define MAIN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MB (1024*1024)
#define HEADERSIZE 10
#define FRAMEHEADER 10
#define MAX_SIZE 20

typedef struct 
{
    char id[5];
    int size;
    char *content;
}Frame;

typedef struct
{
    char *Tag;
    char *Title;
    char *Artist;
    char *Album;
    char *Year;
    char *Comment;
    char Genere;
    char track;
    short time[2];
    char mpeg[10];
    char layer[10];
    int bitrate;
    int sampling;
    char mode[15];
} mp3_data;

typedef struct 
{
    FILE *mp3_file_ptr;
    size_t file_size;
    char file_name[MAX_SIZE];
} mp3_fileinfo;

typedef enum
{
    success,
    failure,
    ID3v1,
    Id3v2,
    _e


} Status;

//Function declarations
Status open_files(mp3_fileinfo *mp3_fileinfo);
Status open_files_write(mp3_fileinfo *mp3_fileinfo);
void help_menu(void);
Status check_operation(char *argv[],mp3_fileinfo *mp3_fileinfo);
Status Read_Tag(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);

Status read_Id3v1_metadata(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);
Status read_Id3v1_1_metadata(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);
void free_ptr(mp3_data *mp3_metadata);
Status read_Id3tag_head(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata,size_t tag_size);
double round_alternative(double x);
Status display_id3v1(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);
Status read_frames(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);

Status read_Id3v2_metadata(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);
Status read_Id3v2_2_metadata(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);
Status read_frames_2_2(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata);

Status edit_id3v2(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata,char str[]);
int edit_frames(unsigned const char *buffer_metadata,Frame **frames,size_t tag_size);
size_t reconstruct_tag(char **buffer_metadata,Frame *frames,int framecount,size_t tag_size);
Status edit_id3v1(mp3_fileinfo *mp3_finfo,char str[]);
Status edit_content(mp3_fileinfo *mp3_finfo,int offset,char name[],int index);
int read_frame_size(unsigned char *frame_header);
unsigned int read_header_size(unsigned char *header);
void read_image(int size,mp3_fileinfo *mp3finfo);

#endif
