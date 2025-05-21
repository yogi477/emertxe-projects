/*
Name: Yogesh k
Batch: 24021B
Date: 14/4/2025
Project: Mninshell project
*/

#include"header.h"
int exit_status,status;
int stop_cnt;
int sig_flag;
pid_t pid;
Cmd_list *cmd_list_head;
char input_string[100];
char prompt[1024] = "Minishell$ ";
char prev_dir[100] = "";
char **str = NULL;

char *get_command(char *input_string)
{
	char *cmd = (char*)malloc(sizeof(char) * strlen(input_string));
	int i = 0;
	for (i; input_string[i] != ' ' && input_string[i] != '\0' ;i++)
	{
		cmd[i] = input_string[i];
	}
	cmd[i] = '\0';
	return cmd;
}
int check_command_type(char *command)
{
	char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
		"set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
		"exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","bg","fg","jobs",NULL};
	for (int i = 0; builtins[i] != NULL; i++)
	{
		if (strcmp(builtins[i],command) == 0)
		{
			return BUILTIN;
			
		}
		
	}
	for(int i = 0; i< 152 ;i++)
	{
		if(strcmp(str[i],command) == 0)
		{
			return EXTERNAL;
		}
	}
	return EXTERNAL;
}
void extract_external_commands(char **external_commands)
{
	int fd = open("external_cmd.txt",O_RDONLY);
	if (fd == -1)
	{
		printf("file open failed\n");
		return;
	}
	char ch;
	char arr[20];
	int j = 0,index = 0;
	while (read(fd,&ch,1) != 0)
	{
		if(ch == '\n')
		{
			arr[j] = '\0';
			external_commands[index] = malloc(20);
			strcpy(external_commands[index++],arr);
			j = 0;
		}
		else
		{
			arr[j++] = ch;
			
		}
		
	}
}

void execute_internal_commands(char *input_string)
{
    char temp[1024];
	char cur_dir[100];
    strcpy(temp, input_string);

    char *cmd = strtok(temp, " ");
    if (!cmd) return;

    if (strcmp(cmd, "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(cmd, "pwd") == 0)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        else
            perror("pwd failed");
    }
    else if (strcmp(cmd, "cd") == 0)
    {
        char *dir = strtok(NULL, " ");
        if (dir == NULL)
            dir = getenv("HOME");

        if (chdir(dir) == -1)
            perror("cd failed");
		if (getcwd(cur_dir, sizeof(cur_dir)) != NULL)
		{
			snprintf(prompt, sizeof(prompt), "minishell:%s$ ", cur_dir);
		}
    }
    else if (strcmp(cmd, "echo") == 0)
    {
        char *arg = strtok(NULL, " ");
        while (arg != NULL)
        {
            if (strcmp(arg, "$?") == 0)
            {
                if (WIFEXITED(exit_status))
                    printf("%d ", WEXITSTATUS(exit_status));
            }
            else if (strcmp(arg, "$$") == 0)
            {
                printf("%d ", getpid());
            }
            else if (strcmp(arg, "$SHELL") == 0)
            {
                char *env = getenv("SHELL");
                printf("%s ", env ? env : "");
            }
            else
            {
                printf("%s ", arg);
            }
            arg = strtok(NULL, " ");
        }
        printf("\n");
    }
    else if (strcmp(cmd, "jobs") == 0)
    {
        print_cmd_list();
    }
    else if (strcmp(cmd, "bg") == 0)
    {
        if (stop_cnt)
        {
            stop_cnt--;
            Cmd_list* node = get_last();
            printf("%d %s\n", node->pid, node->command);
            kill(node->pid, SIGCONT);
            waitpid(node->pid, &status, WNOHANG);
            free(node);
        }
        else
        {
            printf("bg: current: no such job\n");
        }
    }
    else if (strcmp(cmd, "fg") == 0)
    {
        if (stop_cnt)
        {
            stop_cnt--;
            Cmd_list* node = get_last();
            printf("%d %s\n", node->pid, node->command);
            kill(node->pid, SIGCONT);
            waitpid(node->pid, &status, WUNTRACED);
            free(node);
        }
        else
        {
            printf("fg: current: no such job\n");
        }
    }
}

int execute_external_commands(char *input_string)
{
	int pipe_flag = 0;
	char **str = (char **)malloc(sizeof(char*) * 10);
	str[0] = "a.out";
	int index = 1,arg_cnt = 1;
	char *tok = strtok(input_string, " ");
	while (tok != NULL)
	{
		str[index] = malloc(strlen(tok) + 1);
		strcpy(str[index++],tok);
		arg_cnt++;
		tok = strtok(NULL," ");
	}
	str[index] = NULL;
	for (int i = 1; str[i] != NULL; i++)
	{
		if(strcmp(str[i],"|") == 0)
		{
			pipe_flag = 1;
			break;
		}
	}
	if(pipe_flag == 1)
	{
		pipe_fun(arg_cnt,str);
		exit(0);
	}
	else
	{
		execvp(str[1],str+1);
	}
	
	return 0;

 }
int insert_at_last()
{
    Cmd_list *new_node = (Cmd_list*)malloc(sizeof(Cmd_list));
    if(new_node==NULL)
    {
        printf("Malloc failed\n");
        return 0;
    }
    new_node->pid = pid;
    strcpy(new_node->command, input_string);
    new_node->next = NULL;
    if(cmd_list_head==NULL)
    {
        cmd_list_head = new_node;
    }
    else
    {
        Cmd_list *temp = cmd_list_head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    return 1;
}

Cmd_list* get_last()
{
    if(cmd_list_head==NULL)
        return NULL;
    
    Cmd_list *temp = cmd_list_head;
    if(temp->next==NULL)
    {
        cmd_list_head = NULL;
        return temp;
    }

    Cmd_list *temp2 = temp->next;
    
    while (temp2->next)
    {
        temp = temp->next;
        temp2 = temp2->next;
    }
    temp->next = NULL;
    return temp2;
}

void print_cmd_list()
{
    if(cmd_list_head==NULL)
        return ;

    Cmd_list *temp = cmd_list_head;
    int i=0;
    while (temp)
    {
        printf("[%d] %d Stopped\t\t%s\n", i++, temp->pid, temp->command);
        temp = temp->next; 
    }
    
}
void my_handler(int signum)
{
	printf("\n%s",prompt);
	fflush(stdout);
}

void sig_handler1(int sig_num)
{ 
    if(sig_num==SIGCHLD)
    {
       waitpid(-1, NULL, WNOHANG);
    }

}
void sig_handler2(int sig_num)
{ 
    if(sig_num==SIGINT || sig_num == SIGTSTP)
    {
        printf("\n");
        sig_flag=1;
    }

    if((sig_num==SIGTSTP) && (pid!=0))
    {
        stop_cnt++;
        printf("\n[%d]+ Stopped\t\t\t", stop_cnt);
        printf("%s\n", input_string);
        insert_at_last();
    }
} 	
void scan_input(char *prompt, char *input_string)
{
    while(1)
    {
		printf("%s",prompt);
		fflush(stdout);

		fgets(input_string,50,stdin);
		input_string[strlen(input_string)-1] = '\0';

		int is_background = 0;
		int len = strlen(input_string);
		if (len > 0 && input_string[len - 1] == '&') {
			is_background = 1;
			input_string[len - 1] = '\0';
			len--;
			if (len > 0 && input_string[len - 1] == ' ') {
				input_string[len - 1] = '\0';
			}
		}

		if(strncmp(input_string,"PS1=",4) == 0)
		{
			strcpy(prompt,input_string+4);
		}
		char *cmd = get_command(input_string);
		int ret = check_command_type(cmd);
		if( ret == BUILTIN)
		{
			execute_internal_commands(input_string);
		}
		else if (ret == EXTERNAL)
		{
			pid = fork();
			if(pid == 0)
			{
				signal(SIGINT,SIG_DFL);
				signal(SIGTSTP,SIG_DFL);
				execute_external_commands(input_string);
			}
			else
			{
				if (is_background)
				{
					insert_at_last();
					printf("[%d] %d\n", stop_cnt + 1, pid);
				}
				else
				{
					waitpid(pid,&exit_status,WUNTRACED);
				}
			}
		}
		else if (ret == NO_COMMAND)
		{
			printf("Invalid command\n");
			continue;
		}
        sig_flag = 0;
    }
}

int main()
{
	str = (char **)malloc(sizeof(char*) * 153);
	struct sigaction newact;
    memset(&newact, 0, sizeof(newact));
	newact.sa_handler = sig_handler2;
	sigaction(SIGINT, &newact, (struct sigaction *)NULL);
	sigaction(SIGTSTP, &newact, (struct sigaction *)NULL);
    signal(SIGCHLD, sig_handler1);
	system("clear");
	extract_external_commands(str);
	scan_input(prompt,input_string);
}
