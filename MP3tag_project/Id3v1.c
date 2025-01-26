#include"main.h"


double round_alternative(double x) {
    return (x >= 0) ? (long)(x + 0.5) : (long)(x - 0.5);
}
const char *id3v1_genres[] = {
    "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz",
    "Metal", "New Age", "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno",
    "Industrial", "Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack", "Euro-Techno",
    "Ambient", "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental",
    "Acid Punk", "Acid Jazz", "Polka", "Retro", "Rock & Roll", "Hard Rock", "Folk", "Folk Rock",
    "National Folk", "Swing", "Fast Fusion", "Bebop", "Latin", "Revival", "Celtic", "Bluegrass",
    "Avantgarde", "Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Slow Rock", "Big Band",
    "Chorus", "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson", "Opera", "Art Rock",
    "Progressive House", "Psytrance", "Chillout", "Indie", "Britpop", "Big Beat", "Breakbeat",
    "DJ", "House", "Trance", "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult", "Gangsta",
    "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave",
    "Punk Rock", "Drum Solo", "Acapella", "Eurodance", "Alternative Rock", "Polka", "Indie Rock",
    "Grunge Rock"};

Status read_Id3v1_metadata(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata)
{
    char data[30] = {0};
    fseek(mp3_finfo->mp3_file_ptr,-125,SEEK_END);//points after 3 bytes
    mp3_metadata->Title = (char*)malloc(sizeof(char) * 30);
    fread(mp3_metadata->Title,sizeof(char),30,mp3_finfo->mp3_file_ptr);
    //printf("Title -> %s\n",mp3_metadata->Title);

    mp3_metadata->Artist = (char*)malloc(sizeof(char) * 30);
    fread(mp3_metadata->Artist,sizeof(char),30,mp3_finfo->mp3_file_ptr);
    //printf("Artist -> %s\n",mp3_metadata->Artist);

    mp3_metadata->Album = (char*)malloc(sizeof(char) * 30);
    fread( mp3_metadata->Album,sizeof(char),30,mp3_finfo->mp3_file_ptr);
    //printf("Album -> %s\n", mp3_metadata->Album);

    mp3_metadata->Year = (char*)malloc(sizeof(char) * 4);
    fread( mp3_metadata->Year,sizeof(char),4,mp3_finfo->mp3_file_ptr);
    //printf("Year -> %s\n", mp3_metadata->Year);

    mp3_metadata->Comment = (char*)malloc(sizeof(char) * 30);
    fread(data,sizeof(char),30,mp3_finfo->mp3_file_ptr);
    if(strcmp(mp3_metadata->Tag,"ID3v1.1") == 0)
    {
        if(data[28] == 0x00)
        {
            printf("%d\n",data[29]);
            mp3_metadata->track = data[29];
        }
    }
    else
    {
        mp3_metadata->track = 0;
    }
    
    strcpy(mp3_metadata->Comment,data);
    //printf("Comment -> %s\n",mp3_metadata->Comment);

    fread(&mp3_metadata->Genere,sizeof(char),1,mp3_finfo->mp3_file_ptr);
    //printf("Genere -> %s\n",id3v1_genres[mp3_metadata->Genere]);
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_END);
    size_t size = ftell(mp3_finfo->mp3_file_ptr);
    mp3_finfo->file_size = size;
    //printf("size of mp3 -> %zuMB\n", mp3_finfo->file_size/MB);
    
    fseek(mp3_finfo->mp3_file_ptr,0,SEEK_SET);
    read_Id3tag_head(mp3_finfo,mp3_metadata,size);
}
Status display_id3v1(mp3_fileinfo *mp3_finfo,mp3_data *mp3_metadata)
{
    printf("\n");
    printf("Song:%s",mp3_finfo->file_name);
    printf("     [ %ld mb]\n",mp3_finfo->file_size/MB);
    printf("--------------------------------------------------------------------------\n");

    //printf("Time: %02d:%02d",mp3_metadata->time[0],mp3_metadata->time[1]);
    printf("Tag:%s ",mp3_metadata->Tag);
    printf("     %s,",mp3_metadata->mpeg);
    printf(" %s",mp3_metadata->layer);
    printf("     [ %d Hz - %s]\n",mp3_metadata->sampling,mp3_metadata->mode);
    printf("--------------------------------------------------------------------------\n");

    //printf("%s:\n",mp3_metadata->Tag);
    printf("Title: %s\n",mp3_metadata->Title);
    printf("Artist: %s\n",mp3_metadata->Artist);
    printf("Album: %s\n",mp3_metadata->Album);
    printf("Year: %s\n",mp3_metadata->Year);
    if (mp3_metadata->track != 0)
    {
        printf("Track: %d\n",mp3_metadata->track);
        printf("Genere: %s id(%d)\n",id3v1_genres[mp3_metadata->Genere],mp3_metadata->Genere);
    }
    else
         printf("Genere: %s id(%d)\n",id3v1_genres[mp3_metadata->Genere],mp3_metadata->Genere);
    printf("Comment: %s\n",mp3_metadata->Comment);
    printf("--------------------------------------------------------------------------\n");
    printf("\n");


}