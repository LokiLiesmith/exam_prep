#include <unistd.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int		fds[2];
	pid_t	cpid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	if(pipe(fds) == -1)
		return -1;
	
	cpid = fork();
	if(cpid < 0)
	{
		close(fds[0]);
		close(fds[1]);
		return -1;
	}
	
	if(cpid == 0)
	{
		if (type == 'r')
		{
			if(dup2(fds[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else
		{
			if(dup2(fds[0], STDIN_FILENO) == -1)
				exit(1);
		}
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fds[1]);
		return(fds[0]);
	}
	close(fds[0]);
	return(fds[1]);
}

int main(int ac, char **av)
{
	int fd;
	char buf[128];

	if (ac != 2)
		return 1;

	fd = ft_popen("ls", (char *const []){"ls", av[1], NULL}, 'r');

	int n;
	while ((n = read(fd, buf, sizeof(buf))) > 0)
		write(1, buf, n);
	close(fd);
	return 0;
}

