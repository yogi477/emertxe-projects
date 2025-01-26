#include"main.h"

void update_tag_size(char *header, int new_size) {
    // Ensure header is at least 10 bytes
    if (!header) return;

    // Convert the new size to a synchsafe integer
    header[6] = (new_size >> 21) & 0x7F;
    header[7] = (new_size >> 14) & 0x7F;
    header[8] = (new_size >> 7) & 0x7F;
    header[9] = new_size & 0x7F;
}
void update_frame_size(char *frame_header, int new_size) {
    // Ensure frame header is at least 10 bytes
    if (!frame_header) return;

    // Write the new size in big-endian format
    frame_header[4] = (new_size >> 24) & 0xFF;
    frame_header[5] = (new_size >> 16) & 0xFF;
    frame_header[6] = (new_size >> 8) & 0xFF;
    frame_header[7] = new_size & 0xFF;
}
int edit_frames(unsigned const char *buffer_metadata,Frame **frames,size_t tag_size)
{
   int offset = 0;
   int framecount = 0;
   
   *frames = NULL;
   while(offset  < tag_size)
   {
        unsigned const char *header = buffer_metadata + offset;  
        // Stop parsing at padding (frame ID is 0)
        if(header[0] == 0)
        {
            break;
        }
        Frame frame;
        strncpy(frame.id,buffer_metadata + offset,4);
        frame.id[4] = '\0';
        frame.size = ((buffer_metadata[offset + 4] << 24) | (buffer_metadata[offset + 5] << 16) | (buffer_metadata[offset + 6] << 8) | buffer_metadata[offset + 7]);
        frame.content = (char*)malloc(frame.size);
        memcpy(frame.content,buffer_metadata + offset + HEADERSIZE,frame.size);
        
    
        *frames = realloc(*frames,sizeof(Frame) * (framecount + 1));
        if(frames == NULL)
        {
            printf("Memory allocation failed\n");
             free(frame.content);
        }
        (*frames)[framecount++] = frame;

        offset += FRAMEHEADER + frame.size;
   }
    return framecount;
   

}
size_t reconstruct_tag(char **buffer_metadata,Frame *frames,int framecount,size_t tag_size)
{
    size_t newtag_size = 0;
    int offset = 0;
    for (int i = 0; i < framecount; i++)
    {
        newtag_size += frames[i].size + FRAMEHEADER;
    }
    size_t padding = 1024; 
    if(tag_size > newtag_size)  
    {
        padding = tag_size - newtag_size; //padding
    }
    newtag_size += padding; 
    
    *buffer_metadata = calloc(newtag_size,1);
    if(*buffer_metadata == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < framecount; i++)
    {
       memcpy(*buffer_metadata + offset,frames[i].id,4);
       (*buffer_metadata)[offset + 4] = (frames[i].size >> 21) & 0xFF;
       (*buffer_metadata)[offset + 5] = (frames[i].size >> 16) & 0xFF;
       (*buffer_metadata)[offset + 6] = (frames[i].size >> 8) & 0xFF;
       (*buffer_metadata)[offset + 7] = (frames[i].size & 0xFF);
       memcpy(*buffer_metadata + offset + FRAMEHEADER,frames[i].content,frames[i].size);

        offset += FRAMEHEADER + frames[i].size;
    }
    
    return newtag_size;
}

Status edit_id3v2(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata,char str[])
{
    char *frames_str[] = {"TIT2","TALB","TPE1","COMM","TCON","TYER","TCOM","TRCK"};
    char *edit_str[] = {"-t","-a","-A","-c","-g","-y","-m","-T"};
    char *frame_id_names[] = {"Title","Album","Artist","Comment","Genre","Year","Composer","Track"};
    unsigned char new_str[100];
    char frame_id[5];
    
    int new_str_len = strlen(str);
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_SET);
    int offset = 0;
    unsigned char header[10];
    size_t tag_size = 0;
    if(fread(header,sizeof(char),HEADERSIZE,mp3_finfo->mp3_file_ptr) != 10)
    {
        printf("Unable to read data\n");
    }
    tag_size = ((header[6] & 0x7F) << 21) | ((header[7] & 0x7F) << 14)| ((header[8] & 0x7F) << 7)| (header[9] & 0x7F);
    //printf("tag size -> %zu\n",tag_size);
    
    //fseek(mp3_finfo->mp3_file_ptr,0,SEEK_SET);
    char *buffer_metadata = (char *)malloc(sizeof(char) * (tag_size)); //metadata frames
    if(fread(buffer_metadata,sizeof(char),tag_size,mp3_finfo->mp3_file_ptr) != tag_size)
    {
        printf("Unable to read data\n");
    }
    

    Frame *frame;
    int framecount = edit_frames(buffer_metadata,&frame,tag_size);
    
        int flag = 0;
        for (int i = 0; i < 8; i++)
        {
            if (strcmp(str,edit_str[i]) == 0)
            {
                for (int j = 0; j < framecount; j++)
                {
                    if (strcmp(frames_str[i],frame[j].id) == 0)
                    {
                        flag = 1;
                    }
                    
                }
                
            }
            
        }
        if (flag == 0)
        {
            printf("The Tag you need to edit is not present\n");
            return failure;
        }
        
    for (int  i = 0; i < 8; i++)
    {
        if(strcmp(str,edit_str[i]) == 0)
        {
            strcpy(frame_id,frames_str[i]);
            printf("Enter new %s\n",frame_id_names[i]);
            scanf(" %[^\n]",new_str);
            break;
        }
    }
        
    //printf("framecount --> %d\n",framecount);
    for (int i = 0; i < framecount; i++)
    {
        if(strcmp(frame[i].id,frame_id) == 0)
        {
            printf("%s Tag found updating ...\n",frame_id);
            frame[i].size = strlen(new_str) + 1;
            frame[i].content = realloc(frame[i].content,frame[i].size);
            frame[i].content[0] = 0x00; //encoding
            strncpy(frame[i].content + 1, new_str, frame[i].size);
            break;
        }
        
    }
    size_t newtag_size = reconstruct_tag(&buffer_metadata,frame,framecount,tag_size);
    update_tag_size(header,newtag_size);


    if(open_files_write(mp3_finfo) != success)
        return failure; 
    
    fwrite(header,1,10,mp3_finfo->mp3_file_ptr);
    fwrite(buffer_metadata,1,newtag_size,mp3_finfo->mp3_file_ptr);

    for (int i = 0; i < framecount; i++)
    {
        free(frame[i].content);
    }
    
    free(buffer_metadata);
    fclose(mp3_finfo->mp3_file_ptr);
    
    printf("Update successful...\n");
    
    return success;
   
}
