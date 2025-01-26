#include"main.h"
Status edit_content(mp3_fileinfo *mp3_finfo,int offset,char name[],int size)
{
    if(open_files_write(mp3_finfo) == failure)
    {
        return failure;
    }
    if(fseek(mp3_finfo->mp3_file_ptr,offset,SEEK_END) != 0)
    {
        printf("Error while seeking\n");
        return failure;
    }
    char buffer[size];
    
    printf("Enter new %s\n",name);
    
    memset(buffer,0,size);
    scanf(" %[^\n]",buffer);
    if(fwrite(buffer,sizeof(char),size,mp3_finfo->mp3_file_ptr) != size)
    {
        printf("unable to write data\n");
        return failure;
    }
    
    return success;

}
Status edit_id3v1(mp3_fileinfo *mp3_finfo,char str[])
{
    
    char *frames_str[] = {"Title","Artist","Album","year","Comment","Genre"};
    char *edit_str[] = {"-t","-a","-A","-y","-c","-g"};
    int metadata_size[] = {30,30,30,4,30,1};
    
    int offset[] = {-125,  //title
                    -95, //artist
                    -65, //album
                    -35, //year
                    -31, //comment
                    -1,}; //genre

    int flag = 0;
        for (int i = 0; i < 6; i++)
        {
            if (strcmp(str,edit_str[i]) == 0)
            {
                flag = 1;
                
            }
            
        }
        if (flag == 0)
        {
            printf("The Tag you need to edit is not present\n");
            return failure;
        }
        
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(str,edit_str[i]) == 0)
        {
            if(edit_content(mp3_finfo,offset[i],frames_str[i],metadata_size[i]) == success)
            {
                printf("Update successful\n");
                fclose(mp3_finfo->mp3_file_ptr);
                return success;
            }
            else
                return failure;
        }

    }
    
    return success;

    
}
