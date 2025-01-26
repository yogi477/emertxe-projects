#include"main.h"

char *frames_str[] = {"TIT2","TALB","TPE1","COMM","TCON","TYER","TCOM","TRCK"};
unsigned int frm_cnt_size = 0;
int image_flag;
char frame_id(char str[])
{
    char *frame_id_names[] = {"Title","Album","Artist","Comment","Genre","Year","Composer","Track"};

    for (int i = 0; i < 8; i++)
    {
        if(strcmp(str,frames_str[i]) == 0)
        {
            printf("%s --> ",frame_id_names[i]);
            break;
        }
    }

}
Status read_frames(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata)
{
    unsigned char data[10];
    char frames[4];
    int flag = 0;
    fread(data,sizeof(char),FRAMEHEADER,mp3_finfo->mp3_file_ptr);
    strncpy(frames,data,4);
    frames[4] = '\0';

    frm_cnt_size = read_frame_size(data);
    for (int i = 0; i < 8; i++)
    {
       if (strcmp(frames_str[i],frames) == 0)
       {
           flag = 1;
           break;
       }
    }
    if(flag == 1)
    {
        //printf("%s\n",frames);
        char title[frm_cnt_size];
        fread(title,sizeof(char),frm_cnt_size,mp3_finfo->mp3_file_ptr);
        for (int i = 0; i < frm_cnt_size; i++)
        {
            if (title[i] == '\0')
            {
                title[i] = ' ';
            }
            
        }
        title[frm_cnt_size] = '\0';
        //mp3_metadata->Title = (char *)malloc(sizeof(char) * title_size);
        //strcpy(mp3_metadata->Title,title);
        frame_id(frames);
        printf("%s\n",title);
    }
    else
    {
        if(strcmp(frames,"APIC") == 0)
        {
            read_image(frm_cnt_size,mp3_finfo);  // function To read image
            image_flag = 1;
        }
        int skip = ftell(mp3_finfo->mp3_file_ptr) + frm_cnt_size;
        fseek(mp3_finfo->mp3_file_ptr,skip,SEEK_SET);
        
    }
}
Status read_Id3v2_metadata(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata)
{
    unsigned char header[10];
    int tag_size = 0;
    size_t total_size = 0;
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_SET);
    
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_END);
    total_size = ftell(mp3_finfo->mp3_file_ptr);
    mp3_finfo->file_size = total_size;
    
    printf("\n");
    printf("Song:%s",mp3_finfo->file_name);
    printf("     [ %.2f mb]\n",(float)mp3_finfo->file_size/MB);
    printf("--------------------------------------------------------------------------\n");
    
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_SET);

    fread(header,sizeof(char),HEADERSIZE,mp3_finfo->mp3_file_ptr);
    tag_size = ((header[6] & 0x7F) << 21) | ((header[7] & 0x7F) << 14)| ((header[8] & 0x7F) << 7)| (header[9] & 0x7F);
    //printf("%d\n",tag_size);
    //printf("Total size -> %zu mb\n",total_size);
    
    fseek(mp3_finfo->mp3_file_ptr,tag_size + HEADERSIZE,SEEK_SET);
    //printf("%ld\n",ftell(mp3_finfo->mp3_file_ptr));
    read_Id3tag_head(mp3_finfo,mp3_metadata,tag_size);
    
    //printf("Time: %02d:%02d",mp3_metadata->time[0],mp3_metadata->time[1]);
    printf("Tag:%s",mp3_metadata->Tag);
    printf("     %s,",mp3_metadata->mpeg);
    printf(" %s",mp3_metadata->layer);
    printf("     [ %d Hz - %s]\n",mp3_metadata->sampling,mp3_metadata->mode);
    printf("--------------------------------------------------------------------------\n");

    //printf("%s:\n",mp3_metadata->Tag);
    
    fseek(mp3_finfo->mp3_file_ptr,10,SEEK_SET);
    
    while (ftell(mp3_finfo->mp3_file_ptr) < tag_size)
    {
        read_frames(mp3_finfo,mp3_metadata);
    }
    if(image_flag)
        printf("----------------------- \e[36mImage present extracted\e[0m --------------------------\n");
    else
        printf("--------------------------------------------------------------------------\n");

    printf("\n");

    free(mp3_metadata->Tag);
}
