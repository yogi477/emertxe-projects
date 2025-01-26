#include <stdio.h>
#include "decode.h"
#include "types.h"
#include<string.h>
#include<stdlib.h>
#include "common.h"
/* Function Definitions */

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
int flag = 0;
Status open_decfiles(DecodeInfo *decInfo)
{
    // Src Image file
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    // Do Error handling
    if ( decInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "\e[31mERROR : Unable to open file %s\n\e[0m]", decInfo->stego_image_fname);

    	return e_failure;
    }
    return e_success;
}
Status open_output_file(DecodeInfo *decInfo)
{
    // Secret file
    decInfo->fptr_secret = fopen(decInfo->secret_fname, "w");
    // Do Error handling
    if (decInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "\e[31mERROR : Unable to open file %s\e[0m\n", decInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file

    // No failure return e_success
    return e_success;
}
int extn_size = 0;
Status read_and_validate_decode_args(char *argv[],DecodeInfo *decInfo)
    //1. argv[2] is .bmp or not
{
        //store filename to the struct members
        //2. argv[3] s text file or not
        //store file name to the struct members
        //3.argv[4] is empty or not
        //if argv[4] == null
        //output.bmp
        // store the filename to struct members
        //not a null
        //if argv[4] is .bmp or not
        //store the filename to struct members
    if(strstr(argv[2],".bmp") != NULL)
    {
        //strcpy(encinfo->stego_image_fname,argv[2]);
        int len = strlen(argv[2]);
        decInfo->stego_image_fname = (char*)malloc(sizeof(char) * len);
        strcpy(decInfo->stego_image_fname,argv[2]);
    }
    else
    {
        printf("\e[31mERROR : Input image file must be a .bmp file\e[0m\n");
        return e_failure;
    }
    //secret file
    if (argv[3] != NULL)
    {
        
        decInfo->secret_fname = (char *)malloc(sizeof(char) * 15);
        strcpy(decInfo->secret_fname,argv[3]);
        
    }
    else
    {
        //printf("No secret message\n");
        flag = 1;
        decInfo->secret_fname = (char *)malloc(sizeof(char) * 15);
        strcpy(decInfo->secret_fname,"output");
        //decInfo->secret_fname = "decode";
        
    }

    return e_success;
}
Status do_decoding(DecodeInfo *decInfo)
{
    
    if (open_decfiles(decInfo) == e_success)
    {
        printf("\n\e[3;33mINFO : Decoding Procedure Started...\e[0m\n");
        printf("INFO : Opening required files\n");
        printf("INFO : Opened \e[32m%s\e[0m\n",decInfo->stego_image_fname);
    }
    else
    {
        return e_failure;
    }
    if (decode_magic_string(MAGIC_STRING,decInfo) == e_success)
    {
        printf("INFO : Done\n");
    }
    else
    {
        return e_failure;
    }
    
    if (decode_secret_file_extn_size(decInfo) == e_success)
    {
        printf("INFO : Done\n");
    }
    if (decode_secret_file_extn(extn_size,decInfo) == e_success)
    {
        printf("INFO : Done\n");
        if (flag == 1)
        {
            printf("\nINFO : output file not mentioned. Creating \e[32moutput.txt\e[0m as default\n\n");
        }
        
    }
    if (decode_secret_file_size(decInfo) == e_success)
    {
        printf("INFO : Done\n");
    }
    if (decode_secret_file_data(extn_size,decInfo) == e_success)
    {
        printf("INFO : Done\n");
    }
    return e_success;   
}
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    int len = strlen(MAGIC_STRING);
    char buffer[8] = {0};
    char *data = (char *)malloc(sizeof(char)*len);
    int i;
    fseek(decInfo->fptr_stego_image,54,SEEK_SET);
    for (i = 0; i < len; i++)
    {
        fread(buffer,sizeof(char),8,decInfo->fptr_stego_image);
        data[i] = decode_byte_to_lsb(buffer);
    }
    if (strcmp(MAGIC_STRING,data) == 0)
    {
        printf("\n\e[34mDecoded magic string:\e[0m\e[32m %s\n\e[0m",data);
        free(data);
        return e_success;
    }
    else
    {
        printf("\e[31mERROR : Magic string not matching\n");
        return e_failure;
    }
    
    
}
Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    char buffer[32] = {0};
    fread(buffer,sizeof(char),32,decInfo->fptr_stego_image);
    decode_size_to_lsb(buffer);
    printf("\e[34mDecoded secret file extn size =\e[0m \e[32m%d\n\e[0m",extn_size);
    return e_success;
}
Status decode_secret_file_extn(int file_extn, DecodeInfo *decInfo)
{
    char buffer[8] ={0};
    char *data = (char *)malloc(sizeof(char)*(file_extn));
    int i;
    for (i = 0; i < file_extn; i++)
    {
        fread(buffer,sizeof(char),8,decInfo->fptr_stego_image);
        data[i] = decode_byte_to_lsb(buffer);
    }
    data[i] = '\0';
    if (strstr(decInfo->secret_fname,".") == NULL)
    {
        strcat(decInfo->secret_fname,data);
    }
    open_output_file(decInfo);
    //printf("=====%s====\n",decInfo->secret_fname);
    printf("\e[34mDecoded secret file extension:\e[0m \e[32m%s\n\e[0m",data);
    free(data);
    return e_success;
}
Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char buffer[32] = {0};
    fread(buffer,sizeof(char),32,decInfo->fptr_stego_image);
    decode_size_to_lsb(buffer);
    printf("\e[34mDecoded secret file data size =\e[0m \e[32m%d\n\e[0m",extn_size);
    return e_success;
}
Status decode_secret_file_data(int secret_file_size,DecodeInfo *decInfo)
{
    char buffer[8] ={0};
    char *data = (char *)malloc(sizeof(char)*secret_file_size);
    for (int i = 0; i < secret_file_size; i++)
    {
        fread(buffer,sizeof(char),8,decInfo->fptr_stego_image);
        data[i] = decode_byte_to_lsb(buffer);
    }
    fprintf(decInfo->fptr_secret,"%s",data);
    printf("\e[34mDecoded secret file data:\e[32m %s\n\e[0m",data);
    free(data);
    return e_success;
}
char decode_byte_to_lsb(char *image_buffer)
{
    char data = 0;
    for (int i = 0; i < 8; i++)
    {
        image_buffer[i] = image_buffer[i] & (0x01);
        data = data | (image_buffer[i] << i);
    }
    return data;
}
Status decode_size_to_lsb(char *image_buffer)
{
    int data = 0;
    for (int i = 0; i < 32; i++)
    {
        int bits = image_buffer[i] & (0x01);
        data = data | (bits << i);
    }
    extn_size = data;
    
    return e_success;
}
