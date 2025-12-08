#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

// “Parent wants R => child writes. Parent wants W => child reads.”

int ft_popen(const char *file, char *const argv[], char type)
{
    int     fd[2];
    pid_t   cpid;

    // Validate input
    if (!file || !argv || (type != 'r' && type != 'w'))
        return (-1);

    // Create pipe: fd[0] = read end, fd[1] = write end
    if (pipe(fd) == -1)
        return (-1);

    cpid = fork();

    // Fork error => close both ends and return -1
    if (cpid < 0)
    {
        close(fd[0]);
        close(fd[1]);
        return (-1);
    }

    // CHILD PROCESS
    if (cpid == 0)
    {
        
        //  If type == 'r':
        //      Parent will READ from the pipe.
        //      Child must WRITE into the pipe => connect stdout to fd[1].
       
        if (type == 'r')
            dup2(fd[1], STDOUT_FILENO);

        
        //  If type == 'w':
        //    Parent will WRITE into the pipe.
        //    Child must READ from the pipe => connect stdin to fd[0].
       
        else
            dup2(fd[0], STDIN_FILENO);

        // Close both ends: no longer needed after dup2
        close(fd[0]);
        close(fd[1]);

        // Replace child with new executable
        execvp(file, argv);

        // exec only returns on error
        exit(1);
    }

    // PARENT PROCESS

    
    // If type == 'r':
    //  Parent wants to READ => keep fd[0], close write end.
   
    if (type == 'r')
    {
        close(fd[1]);
        return (fd[0]);
    }

    
    // If type == 'w':
    //   Parent wants to WRITE => keep fd[1], close read end.
   
    close(fd[0]);
    return (fd[1]);
}


int main()
{
    int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
	// close(fd);
	// fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'w');

    char buf[128];
    read(fd, buf, sizeof(buf));

    close(fd);
}

// int main()
// {
//     int  fd;
//     char *line;

//     fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
//     while ((line = get_next_line(fd)))
//         ft_putstr(line);
//     return (0);
// }


// int	main() {
// 	int	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
// 	dup2(fd, 0);
// 	fd = ft_popen("grep", (char *const []){"grep", "c", NULL}, 'r');
// 	char	*line;
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// }