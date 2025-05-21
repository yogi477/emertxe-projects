/*
Name: Yogesh k
Batch: 24021B
Date: 28/4/2024
Project: Lexical analyzer
*/
#include<stdio.h>
#include<ctype.h>
#include<string.h>

char key_word[33][10] = {
    "auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto",
    "if","int","long","register","return","short","signed",
    "sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while","typedef"
};

char symbols[] = {'/','+','*','-','%','=','#','<','>','~','&','!','^','|','(',')','[',']',':',';','{','}'};

int main(int argc,char *argv[])
{
    if(argv[1] == NULL)
    {
        printf("ERROR : Invalid arguments\n");
        printf("Usage : ./a.out <filename.c>\n");
        return 1;
    }

    if(strstr(argv[1],".c") == NULL)
    {
        printf("ERROR: Enter .c file\n");
        return 1;
    }

    FILE *ptr = fopen(argv[1],"r");
    if(ptr == NULL)
    {
        printf("ERROR: Could not open file %s\n", argv[1]);
        return 1;
    }

    printf("open    : %s : Success\n",argv[1]);
    printf("parsing : %s : Started\n",argv[1]);

    char ch, str[100];
    int i;

    while ((ch = getc(ptr)) != EOF)
    {
        i = 0;
        if(ch == '#')
        {
            int flag = 0;
            while((ch = getc(ptr)) != '\n' && ch != EOF)
            {
                if(ch == '<' || ch == ' ')
                {
                    str[i] = '\0';
                    if(strcmp(str,"include") == 0)
                        flag = 1;
                    else if(strcmp(str,"define") == 0)
                        flag = 2;
                }
                str[i++] = ch;
            }
            str[i] = '\0';
            if(flag == 1)
            {
                printf("Header file     : %s\n", str);
            }
            else if(flag == 2)
            {
                printf("preprocessor    : %s\n", str);
            }
        }
        else if (isdigit(ch))
        {
            printf("Constants       : %c\n", ch);
        }
        else if (ch == '"') // handling string literal
        {
            i = 0;
            while ((ch = getc(ptr)) != '"' && ch != EOF)
            {
                if(ch == '\\')
                {
                    getc(ptr);
                    continue;
                }
                str[i++] = ch;
            }
            str[i] = '\0';
            printf("String Literal  : %s\n", str);
        }
        else if (!isalpha(ch))
        {
            for (int j = 0; j < strlen(symbols); j++)
            {
                if(ch == symbols[j])
                {
                    printf("Operator        : %c\n", ch);
                    break;
                }
            }
        }
        else if (isalpha(ch))
        {
            str[i++] = ch;
            while ((ch = getc(ptr)) != EOF)
            {
                if (!isalpha(ch))
                {
                    fseek(ptr, -1, SEEK_CUR); // move back one character
                    break;
                }
                str[i++] = ch;
            }
            str[i] = '\0';

            int flag = 0;
            for (int j = 0; j < 33; j++)
            {
                if(strcmp(str, key_word[j]) == 0)
                {
                    flag = 1;
                    printf("Keyword         : %s\n", str);
                    break;
                }
            }

            if(flag == 0)
            {
                printf("Identifier      : %s\n", str);
            }
        }
    }

    fclose(ptr);
    return 0;
}
