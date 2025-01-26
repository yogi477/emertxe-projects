#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include<string.h>
#include<stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    EncodeInfo encInfo;
    uint img_size;

    DecodeInfo decInfo;
    //CLA -> check CLA count
    if ( argc >= 3)
    {
        //check operation type(-e or -d or other)
        
        //if encode(printf("encode started"))
        //if decode(printf("decode started"))
        if (check_operation_type(argv) == e_encode)
        {
            if(read_and_validate_encode_args(argv,&encInfo) == e_failure)
            {
                return 1;
            }
            if (do_encoding(&encInfo) == e_success)
            {
                printf("\e[32m-------------------------------------\n\e[0m");
                printf("\e[3;33m    Encoding Done Successfully\e[0m\n");
                printf("\e[32m-------------------------------------\n\e[0m");
            }
            else
            {
                return 1;
            }
            
        }
        else if (check_operation_type(argv) == e_decode)
        {
            if (read_and_validate_decode_args(argv,&decInfo) == e_failure)
            {
                return 1;
            }
            if (do_decoding(&decInfo) == e_success)
            {
                printf("\e[32m-------------------------------------\n\e[0m");
                printf("\e[3;33m    Decoding Done Successfully\e[0m\n");
                printf("\e[32m-------------------------------------\n\e[0m");
            }
            else
            {
                return 1;
            }
            
            
        }
        else
        {
            printf("\e[31mERROR : enter '-e' or '-d' for encoding or decoding\n");
        }
        
    }
    else
    {
        printf("\e[31mERROR: insufficient agruments\e[0m\n");
        return e_failure;
    }
    
   return 0;
}

OperationType check_operation_type(char *argv[])
{
    //check the argv[1]
    //if(-e)
    //return e_encode
    //else
    //return e_supported 
    if (strcmp(argv[1],"-e") == 0)
    {
        return e_encode;
    }
    else if (strcmp(argv[1],"-d") == 0)
    {
        return e_decode;
    }
    else
    {
        return e_unsupported;
    }
    
}