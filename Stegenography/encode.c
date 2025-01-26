#include <stdio.h>
#include "encode.h"
#include "types.h"
#include<string.h>
#include<stdlib.h>
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    //printf("width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    //printf("height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "\e[31mERROR: Unable to open file %s\n\e[0m", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "\e[31mERROR: Unable to open file %s\n\e[0m", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "\e[31mERROR: Unable to open file %s\n\e[0m", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}
Status read_and_validate_encode_args(char *argv[],EncodeInfo *encinfo)
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
        encinfo->src_image_fname = (char*)malloc(sizeof(char) * len);
        strcpy(encinfo->src_image_fname,argv[2]);
    }
    else
    {
        printf("\e[31mERROR : Input image file must be a .bmp file\n\e[0m");
        return e_failure;
    }
    //secret file
    if(argv[3] == NULL)
    {
        printf("\e[31mERROR : Enter the secret file name\n\e[0m");
        return e_failure;
    }
    if(strstr(argv[3],".") != NULL)
    {
        int len1 = strlen(argv[3]);
        //printf("size of secret file old %d\n",len1);
        encinfo->secret_fname = (char *)malloc(sizeof(char) * len1);
        //encinfo->secret_fname = argv[3];

        strcpy( encinfo->secret_fname,argv[3]);
        char *str1 = strstr(argv[3],".");
        strcpy(encinfo->extn_secret_file,str1);
    } 
    // else if(strstr(argv[3],".c") != NULL)
    // {
    //     int len2 = strlen(argv[3]);
    //     encinfo->secret_fname = (char *)malloc(sizeof(char) * len2);
    //     strcpy(encinfo->secret_fname,argv[3]);
        
    //     char *str1 = strstr(argv[3],".");
    //     strcpy(encinfo->extn_secret_file,str1);
    // } 
    else
    {
        printf("\e[31mERROR : Enter the correct secret file format\n\e[0m");
        return e_failure;
    }
    
    
    if (argv[4] != NULL)
    {
        
        int len3 = strlen(argv[4]);
        encinfo->stego_image_fname = (char *)malloc(sizeof(char) * len3);
        strcpy(encinfo->stego_image_fname,argv[4]);
        
    }
    else
    {
        //printf("No secret message\n");
        printf("\nINFO : \e[32mOutput file not mentioned.\e[0m Creating \e[32moutput.bmp\e[0m as default\n");
        
        encinfo->stego_image_fname = "output.bmp";
    }
    
    // printf("%s\n",encinfo->src_image_fname);
    // printf("%s\n",encinfo->secret_fname); 
    // printf("%s\n",encinfo->extn_secret_file);

    
    // printf("size of seceret file = %zu\n",strlen(encinfo->secret_fname));
    // printf("size of secret file extension = %zu\n",strlen(encinfo->extn_secret_file));


    return e_success;
}
Status do_encoding(EncodeInfo *encInfo)
{
    //opening files
    if ((open_files(encInfo)) == e_success)
    {
        printf("\e[3;33mEncoding started....\e[0m\n");
        printf("INFO : opened requried files\n");
        printf("INFO : opened skeletoncode/\e[32m%s\e[0m\n",encInfo->src_image_fname);
        printf("INFO : opened \e[32m%s\e[0m\n",encInfo->secret_fname);
        printf("INFO : opened \e[32m%s\e[0m\n",encInfo->stego_image_fname);
        printf("INFO : Done\n");
        printf("\e[3;33mProceeding with encoding...\e[0m\n");
    }
    else
    {
        return e_failure;
    }
    
    //check file capacity
    if ( check_capacity(encInfo) == e_success)
    {
        printf("INFO : Checking for SkeletonCode/\e[32m%s\e[0m capacity to handle \e[32m%s\n\e[0m",encInfo->src_image_fname,encInfo->secret_fname);
        printf("INFO : Done. Found Ok\n");
    }
    else
    {
        //printf("\e[31mERROR : %s size is less can't encode\n\e[0m",encInfo->src_image_fname);
        return e_failure;
    }

    if (copy_bmp_header(encInfo->fptr_src_image,encInfo->fptr_stego_image) == e_success)
    {
        printf("INFO : Copying Image Header\n");
        printf("INFO : Done\n");
    }
    else
    {
        return e_failure;
    }
    
    if (encode_magic_string(MAGIC_STRING,encInfo) == e_success)
    {
        printf("INFO : Encoding \e[32mMagic String\e[0m Signature\n");
        printf("INFO : Done\n");
    }
    if (encode_secret_file_extn_size(strlen(encInfo->extn_secret_file),encInfo) == e_success)
    {
        printf("INFO : Encoding \e[32m%s\e[0m File Extenstion size\n",encInfo->secret_fname);
        printf("INFO : Done\n");
    }
    if (encode_secret_file_extn(encInfo->extn_secret_file,encInfo) == e_success)
    {
        printf("INFO : Encoding \e[32m%s\e[0m File Extenstion\n",encInfo->secret_fname);
        printf("INFO : Done\n");
    }
    if (encode_secret_file_size(encInfo->size_secret_file,encInfo) == e_success)
    {
        printf("INFO : Encoding \e[32m%s\e[0m File Size\n",encInfo->secret_fname);
        printf("INFO : Done\n");
    }
    if (encode_secret_file_data(encInfo) == e_success)
    {
        printf("INFO : Encoding \e[32m%s\e[0m File Data\n",encInfo->secret_fname);
        printf("INFO : Done\n");
    }
    if (copy_remaining_img_data(encInfo->fptr_src_image,encInfo->fptr_stego_image) == e_success)
    {
        printf("INFO : Copying Left Over Data\n");
        printf("INFO : Done\n");
    }
    else
    {
        printf("\e[31mERROR : unable to copy remaining file data\n");
        return e_failure;
    }
    

    return e_success;
}
uint get_file_size(FILE *fptr)
{
    /*
    -> find the file size
    use fseek to move the file pointer to the last position
    use ftell to find the size
    */
   if (fptr == NULL)
   {
        perror("\e[31mERROR : opening file\e[0m");
        return 1;
   }

   fseek(fptr,0,SEEK_END);
   long size = ftell(fptr);
   return size;
   
}
Status check_capacity(EncodeInfo *encInfo)
{
    long size = get_image_size_for_bmp(encInfo->fptr_src_image);
    encInfo->size_secret_file = get_file_size(encInfo->fptr_secret);
    //printf("file size %ld\n",encInfo->size_secret_file);
    if (encInfo->size_secret_file > 0)
    {
        printf("INFO : Checking for \e[32m%s\e[0m size\n",encInfo->secret_fname);
        printf("INFO : Not Empty\n");
    }
    else
    {
        printf("INFO : Checking for \e[32m%s\e[0m size\n",encInfo->secret_fname);
        printf("\e[31mINFO : Secret file is Empty\e[0m\n");
        return e_failure;
    }
    
    
    if(size >= 54+((long)strlen(MAGIC_STRING))*8+32+((long)strlen(encInfo->extn_secret_file))*8+32+((long)(encInfo->size_secret_file))*8)
    {
        //printf("size = %ld\n",size);
        return e_success;
    }
    else
    {
        return e_unsupported;
    }
}   
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char buffer[54];
    rewind(fptr_src_image);
    int dataread = fread(buffer,sizeof(char),54,fptr_src_image);
    if (dataread != 54)
    {
        printf("ERROR : While reading header file\n");
        return e_failure;
    }
    
   int datawrite = fwrite(buffer,sizeof(char),54,fptr_dest_image);
   if (datawrite != 54)
    {
        printf("ERROR : While copying header file\n");
        return e_failure;
    }
    return e_success;
}
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char buffer[8];
    for (int i = 0; i < strlen(MAGIC_STRING); i++)
    {
        fread(buffer,sizeof(char),8,encInfo->fptr_src_image);
        encode_byte_to_lsb(magic_string[i],buffer);
        fwrite(buffer,sizeof(char),8,encInfo->fptr_stego_image);
    }
    
    return e_success;
}
Status encode_secret_file_extn_size(int file_extn_size, EncodeInfo *encInfo)
{
    //printf("secret file extension size = %d\n",file_extn_size);
    char buffer[32];
    
    fread(buffer,sizeof(char),32,encInfo->fptr_src_image);
    encode_size_to_lsb(file_extn_size,buffer);
    fwrite(buffer,sizeof(char),32,encInfo->fptr_stego_image);

    return e_success;

}
Status encode_secret_file_extn(const char *file_extn, EncodeInfo *encInfo)
{
    char buffer[8];
    for (int i = 0; i < strlen(file_extn); i++)
    {
        fread(buffer,sizeof(char),8,encInfo->fptr_src_image);
        encode_byte_to_lsb(file_extn[i],buffer);
        fwrite(buffer,sizeof(char),8,encInfo->fptr_stego_image);
    }
    return e_success;
}
Status encode_secret_file_size(long file_size, EncodeInfo *encInfo)
{
    char buffer[32];
    
    fread(buffer,sizeof(char),32,encInfo->fptr_src_image);
    encode_size_to_lsb(file_size,buffer);
    fwrite(buffer,sizeof(char),32,encInfo->fptr_stego_image);

    return e_success;
}
Status encode_secret_file_data(EncodeInfo *encInfo)
{
   char buffer[100] = {0};
   int i = 0;
   char arr[8];
   fseek(encInfo->fptr_secret,0,SEEK_SET);
   while ((buffer[i++] = fgetc(encInfo->fptr_secret)) != EOF);
   
   for (int i = 0; i < encInfo->size_secret_file; i++)
   {
      fread(arr,sizeof(char),8,encInfo->fptr_src_image);
      encode_byte_to_lsb(buffer[i],arr);
      fwrite(arr,sizeof(char),8,encInfo->fptr_stego_image);
    }
    return e_success;
}
Status copy_remaining_img_data(FILE *fptr_src, FILE *fptr_dest)
{
    char arr[1];
    while ((fread(arr,sizeof(char),1,fptr_src)) > 0)
    {
        fwrite(arr,sizeof(char),1,fptr_dest);
    }
    while (getc(fptr_src) == EOF)
    {
        return e_success;
    }
    return e_failure;
}
Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for (int i = 0; i < 8; i++)
    {
        image_buffer[i] = image_buffer[i] & ~(0x01);
        char get = (data >> i) & (0x01);
        image_buffer[i] = image_buffer[i] | get;
    }
    return e_success;
}
Status encode_size_to_lsb(int size, char *image_buffer)
{
    for (int i = 0; i < 32; i++)
    {
        image_buffer[i] = image_buffer[i] & ~(0x01);
        char get = (size >> i) & 1;
        image_buffer[i] = image_buffer[i] | get;
    }
   return e_success; 
}


