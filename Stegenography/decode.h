#ifndef DECODE_H
#define DECODE_H
#include<stdio.h>
#include "types.h" // Contains user defined types
/* 
 * Structure to store information required for
 * encoding secret file to source Image
 * Info about output and intermediate data is
 * also stored
 */

#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4

typedef struct _DecodeInfo
{
    /* Secret File Info */
    char *secret_fname;                // secret file name
    FILE *fptr_secret;                 //file pointer address
    
    /* Stego Image Info */
    char *stego_image_fname;   //file name
    FILE *fptr_stego_image;    //file pointer
} DecodeInfo;


/* Decoding function prototype */

/* Read and validate Decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the encoding */
Status do_decoding(DecodeInfo *decInfo);

/* Get File pointers for i/p and o/p files */
Status open_decfiles(DecodeInfo *decInfo);

/*open output file*/
Status open_output_file(DecodeInfo *decInfo);

/* Decode Magic String */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);

/* Decode secret file extenstion size*/
Status decode_secret_file_extn_size(DecodeInfo *decInfo);

/* Decode secret file extenstion */
Status decode_secret_file_extn(int file_extn, DecodeInfo *decInfo);

/* Decode secret file size */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* Decode secret file data*/
Status decode_secret_file_data(int secret_file_size,DecodeInfo *decInfo);

/* Decode a byte into LSB of image data array */
char decode_byte_to_lsb(char *image_buffer);

Status decode_size_to_lsb(char *image_buffer);


#endif

