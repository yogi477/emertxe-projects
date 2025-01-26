#include"main.h"

Status open_files(mp3_fileinfo *mp3_finfo)
{
    mp3_finfo->mp3_file_ptr = fopen(mp3_finfo->file_name,"r");
    if (mp3_finfo->mp3_file_ptr == NULL)
    {
       fprintf(stderr,"Unable to open file %s\n",mp3_finfo->file_name);
       return failure;
    }
    return success;
}
Status open_files_write(mp3_fileinfo *mp3_finfo)
{
    mp3_finfo->mp3_file_ptr = fopen(mp3_finfo->file_name,"rb+");
    if (mp3_finfo->mp3_file_ptr == NULL)
    {
       //fprintf(stderr,"Unable to open file %s\n",mp3_finfo->dup_ptr);
       return failure;
    }
    return success;
}

void help_menu(void)
{
    printf("USAGE: \n   [mp3filename] --> To view the details of mp3\n");
    printf("To EDIT:\n");
    printf("   [usages][mp3filename] --> To edit the details\n");
    printf("Usages:\n");
    printf("        -t --> Modifies a Title tag\n");
    printf("        -a --> Modifies a Artist tag\n");
    printf("        -A --> Modifies a Album tag\n");
    printf("        -y --> Modifies a Year tag\n");
    printf("        -c --> Modifies a Comment tag\n");
    printf("        -g --> Modifies a Genere tag\n");
    printf("        -m --> Modifies a Composer tag only in ID3v2\n");
}
Status check_operation(char *argv[],mp3_fileinfo *mp3_fileinfo)
{
    if (strcmp(argv[1],"--help") == 0)
    {
        help_menu();
    }
    else if (argv[1] != NULL)
    {
            if (strstr(argv[1],".mp3") != NULL)
            {
                strcpy(mp3_fileinfo->file_name,argv[1]);
                if(open_files(mp3_fileinfo) == success)
                    return success;
                else
                    return failure;
            }
            else if(strcmp(argv[1],"-v") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return success;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
                
            }
            else if(strcmp(argv[1],"-t") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }

            }
            else if(strcmp(argv[1],"-T") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }

            }
            else if(strcmp(argv[1],"-a") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
                
            }
            else if(strcmp(argv[1],"-A") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
                
            }
            else if(strcmp(argv[1],"-y") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
                
            }
            else if(strcmp(argv[1],"-c") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
                
            }
            else if(strcmp(argv[1],"-g") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
                
            }
            else if(strcmp(argv[1],"-m") == 0)
            {
                if (argv[2] == NULL)
                {
                    fprintf(stderr,"Enter the mp3 file name\n");
                    return failure;
                }
                else if (strstr(argv[2],".mp3") != NULL)
                {
                    strcpy(mp3_fileinfo->file_name,argv[2]);
                    if(open_files(mp3_fileinfo) == success)
                        return _e;
                    else
                    {
                        return failure;
                    }
                
                }
                else
                {
                    fprintf(stderr,"Invalid file name give name as 'name.mp3'\n");
                    return failure;
                }
            }
            else
            {
                printf("USAGE: REFER THE HELP MENU --> ./a.out --help\n");
                return failure;

            }
            
    }
    else
    {
        printf("USAGE: REFER THE HELP MENU --> ./a.out --help\n");

    }
    
    
}
Status Read_Tag(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata)
{
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_SET);
    char data[4] = {0};
    fread(data,sizeof(char),4,mp3_finfo->mp3_file_ptr);
    if(strncmp(data,"ID3",3) == 0)
    {
        if(data[3] == 0x00)
        {                           
            mp3_metadata->Tag = (char*)malloc(sizeof(char) * strlen("ID3v2")); 
            strcpy(mp3_metadata->Tag,"ID3v2");
            return Id3v2;
        }
        else if(data[3] == 0x02)
        {
             mp3_metadata->Tag = (char*)malloc(sizeof(char) * strlen("ID3v2.2"));
             strcpy(mp3_metadata->Tag,"ID3v2.2");
             return Id3v2_2;
        }
        else if(data[3] == 0x03)
        {
             mp3_metadata->Tag = (char*)malloc(sizeof(char) * strlen("ID3v2.3"));
             strcpy(mp3_metadata->Tag,"ID3v2.3");
             return Id3v2_3;
        }
        else if(data[3] == 0x04)
        {
            mp3_metadata->Tag = (char*)malloc(sizeof(char) * strlen("ID3v2.4"));
            strcpy(mp3_metadata->Tag,"ID3v2.4");
            return Id3v2_4;
        }
    }
    else if (strncmp(data,"TAG",3) != 0)
    {
        fseek(mp3_finfo->mp3_file_ptr,-128,SEEK_END);
        fread(data,sizeof(char),4,mp3_finfo->mp3_file_ptr);
        if(strncmp(data,"TAG",3) == 0)
        {
            if(data[3] == 0x00)
            {
                mp3_metadata->Tag = (char*)malloc(sizeof(char) * strlen("ID3v1.1"));
                strcpy(mp3_metadata->Tag,"ID3v1.1");
            }
            else if(data[3] != 0x00)
            {
                mp3_metadata->Tag = (char*)malloc(sizeof(char) * strlen("ID3v1"));
                strcpy(mp3_metadata->Tag,"ID3v1");
            }
            
        }
        else
        {
            fprintf(stderr,"No Tag found in this mp3\n");
            return failure;
        }
        
        
        return ID3v1;
    }
    
}
void free_ptr(mp3_data *mp3_metadata)
{
    free(mp3_metadata->Album);
    free(mp3_metadata->Artist);
    free(mp3_metadata->Comment);
    free(mp3_metadata->Tag);
    free(mp3_metadata->Title);
    free(mp3_metadata->Year);
}
int read_frame_size(unsigned char *frame_header) 
{
    int size = (frame_header[4] << 24) |
               (frame_header[5] << 16) |
               (frame_header[6] << 8)  |
               frame_header[7];
    return size;
}
unsigned int read_header_size(unsigned char *header)
{
    int data[4];
    for (int i = 0; i < 4; i++)
    {
        data[i] = header[i+6];
    }
    unsigned int size = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    return size;

}
void read_image(int size,mp3_fileinfo *mp3finfo)
{
    //reads from after header
    char image_data[size];
    fread(image_data,1,size,mp3finfo->mp3_file_ptr);
    
    int offset = 1; // starts after one byte

    int MIME_length = 0;
    while (image_data[offset + MIME_length] != 0x00)
    {
        MIME_length++;  
    }
    offset += MIME_length + 1 + 1;  //MIMElength + null + 1 byte for picture type

    int descrpn_length = 0;
    while (image_data[offset + descrpn_length] != 0x00)
    {
        descrpn_length++;
    }
    
    offset += descrpn_length;
    
    //int len = strlen(mp3finfo->file_name);
    //char *image_name = (char*)malloc(sizeof(char) * len);
    //strncpy(image_name,mp3finfo->file_name,len-4);
    //printf("%s\n",image_name);
    //strcat(image_name,".jpg");
    FILE *image_file = fopen("MP3_IMAGE.jpeg","wb");
    //printf("image -- %x\n",image_data[offset+1]);
    offset = offset + 1;
    if(image_file)
    {
        fwrite(&image_data[offset],1,size - offset,image_file);
    }
    else
    {
        printf("Error opening image file\n");
    }
    
    //free(image_name);
}
        
        // Reads Codec information of mp3
Status read_Id3tag_head(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata,size_t tag_size) 
{
    int flag = 0;
    unsigned short bitrates_mpeg1[3][16] = {{0,32,64,96,128,160,192,224,256,288,320,352,384,416,448,0},
    {0,32,48,56,64,80,96,112,128,160,192,224,256,320,384,0},{0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,0}};
    unsigned short bitrates_mpeg2[2][16] = {{0,32,48,56,64,80,96,112,128,144,160,176,192,224,256,0},{0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,0}};

    char mpeg[4][10] = {"MPEG2.5","0","MPEG2","MPEG1"};
    char layer[4][10] ={"0","Layer III","Layer II","layer I"}; 
    char modes[4][15] = {"Stereo","joint stereo","Dual channel","Mono"};
    int sampling[4][3] = {{44100,22050,11025},{48000,24000,12000},{32000,16000,8000},{0,0,0}};
    int bitrate;
    char data[4] = {0};
    fread(data,sizeof(char),4,mp3_finfo->mp3_file_ptr);
    //printf("0x%02x\n",data[3]);
    // read MPEG version
    char get_mpeg = (data[1] >> 3) & 0x03;
    strcpy(mp3_metadata->mpeg,mpeg[get_mpeg]);
    //printf("%s\n",mp3_metadata->mpeg);
    
    // read layer
    char get_layer = (data[1] >> 1) & 0x03;
    strcpy(mp3_metadata->layer,layer[get_layer]);
    //printf("%s\n",mp3_metadata->layer);
                                    
            //read bitrates
    if(get_mpeg == 0x00 || get_mpeg == 0x02)
    {
        if (get_layer == 0x03)
            get_layer = 0x01;
        else if (get_layer == 0x01)
            get_layer = 0x02;
        
        char get_brate = (data[2] >> 4) & 0x0f;
        mp3_metadata->bitrate = bitrates_mpeg1[get_layer-1][get_brate];
        flag = 1;
        //printf("bitrate -> %d\n",mp3_metadata->bitrate);
    }
    else
    {   
        if (get_layer == 0x03)
            get_layer = 0x01;
        else if (get_layer == 0x01)
            get_layer = 0x03;
        char get_brate = (data[2] >> 4) & 0x0f;
        mp3_metadata->bitrate = bitrates_mpeg1[get_layer-1][get_brate];
        flag = 0;
        //printf("bitrate -> %d\n",mp3_metadata->bitrate);
    }
                            //sampling rate
    char get_sampling = (data[2] >> 2) & 0x03;
    if(get_mpeg == 0x00)
        get_mpeg = 0x02;
    else if (get_mpeg == 0x02)
    {
        get_mpeg = 0x01;
    }
    else if (get_mpeg == 0x03)
    {
        get_mpeg = 0x00;
    }
    mp3_metadata->sampling = sampling[get_sampling][get_mpeg];
    //printf("Sampling rate -> %dHz\n",mp3_metadata->sampling);

    char get_chmod = (data[3] >> 6) & 0x03;
    //printf("%d\n",get_chmod);
    
    strcpy(mp3_metadata->mode,modes[get_chmod]);
    //printf("channel mode -> %s\n",mp3_metadata->mode);

}


    
    