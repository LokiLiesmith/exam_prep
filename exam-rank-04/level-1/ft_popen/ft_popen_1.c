#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int		pipefds[2];
	pid_t	cpid;

	// validate input();
	// In case of error or invalid parameter the function
	// must return -1.
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);

	// create pipe
	if (pipe(pipefds) == - 1)
		return -1;

	// fork
	cpid = fork();
	if (cpid == -1)
	{
		close(pipefds[0]);
		close(pipefds[1]);
		return (-1);
	}

	// child behaviour
	// w-branch
	// r-branch
	if (cpid == 0)
	{
		if (type == 'r')
			dup2(pipefds[1], STDOUT_FILENO);
		else
			dup2(pipefds[0], STDIN_FILENO);
		close(pipefds[0]);
		close(pipefds[1]);
		execvp(file, argv);
		exit(1);
	}

	// parent behaviour
	if (type == 'r')
	{
		close (pipefds[1]);
		return (pipefds[0]);
	}
	else
	{
		close(pipefds[0]);
		return (pipefds[1]);
	}
	return (-1);
}

int main()
{
    int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
	close(fd);
	fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'w');

    char buf[128];
    read(fd, buf, sizeof(buf));

    close(fd);
}