#include"header.h"
int pipe_fun(int argc,char *argv[])
{
    if(argc < 4)
    {
	printf("Invalid arguments\n");
	return 1;
    }
    int pipe_cnt = 0,i = 0,pipe_arr[argc];
    pipe_arr[0] = 1;
    while(i < argc)
    {
	if(strcmp("|",argv[i]) == 0)
	{
	    argv[i] = NULL;
	    pipe_cnt++;
	    pipe_arr[pipe_cnt] = i+1;
	}
	i++;
    }
    for(int i=0;i<pipe_cnt + 1;i++)
    {
	int fd[2];
	int ret = pipe(fd);
	if(ret == -1)
	{
	    printf("ERROR\n");
	    return 1;
	}
	int pid = fork();
	if(pid == -1)
	{
	    printf("process failed\n");
	    return 1;
	}
	if(pid == 0)
	{
	    if(i == pipe_cnt)
	    {
		close(fd[0]);
		close(fd[1]);
	    	execvp(argv[pipe_arr[i]],argv + pipe_arr[i]);
	    }
	    else
	    {
	    	close(fd[0]);
	    	dup2(fd[1],1);
	    	execvp(argv[pipe_arr[i]],argv + pipe_arr[i]);
	    }

	}
	else
	{
	    close(fd[1]);
	    dup2(fd[0],0);
	    int status;
	    wait(&status);
	}

    }

}