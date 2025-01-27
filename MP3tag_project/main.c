#include<stdio.h>
#include"main.h"

int main(int argc, char *argv[])
{
    
    mp3_fileinfo mp3_finfo;
    mp3_data mp3_metadata;
    
    if(argc > 1)
    {
       Status operation_type = check_operation(argv,&mp3_finfo);
       Status read_mp3_tag;
       
       if(operation_type == success)
       {
           read_mp3_tag = Read_Tag(&mp3_finfo,&mp3_metadata);
           
           if(read_mp3_tag == ID3v1)
           {
                read_Id3v1_metadata(&mp3_finfo,&mp3_metadata);
                display_id3v1(&mp3_finfo,&mp3_metadata);
                free_ptr(&mp3_metadata);
                return 0;
           }
           else if (read_mp3_tag == Id3v2_3)
           {
               read_Id3v2_metadata(&mp3_finfo,&mp3_metadata);
               return 0;
           }
           else if (read_mp3_tag == Id3v2_2)
           {
               read_Id3v2_2_metadata(&mp3_finfo,&mp3_metadata);
               return 0;
           }
           else if (read_mp3_tag == Id3v2_4)
            {
                fprintf(stderr,"This application not support ID3v2.4\n");
                    return 1;
            }
           else
           {
                return 1;
           }
           
       }
       else if(operation_type == _e)
       {
            read_mp3_tag = Read_Tag(&mp3_finfo,&mp3_metadata);
            if(read_mp3_tag == Id3v2_3)
            {
                if(edit_id3v2(&mp3_finfo,&mp3_metadata,argv[1]) == success)
                    return 0;
                else
                    return 1;
            }
            else if (read_mp3_tag == ID3v1)
            {
                if(edit_id3v1(&mp3_finfo,argv[1]) == success)
                    return 0;
                else
                    return 1;
            }
            else if (read_mp3_tag == Id3v2_4)
            {
                fprintf(stderr,"This application not support ID3v2.4\n");
                    return 1;
            }
            
        }
        else
        {
            return 1;
        }
       
    }
    else
    {
       printf("USAGE: REFER THE HELP MENU --> ./a.out --help\n");
       return 1;

    }
}