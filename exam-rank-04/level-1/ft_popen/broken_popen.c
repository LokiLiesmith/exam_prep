#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int     p[2];
    pid_t   pid;

    if (!file || !argv || !type)
        return (-1);

    if (pipe(p) == -1)
        return (-1);

    pid = fork();
    if (pid == 0)
    {
        if (type == 'r')
            dup2(p[0], STDOUT_FILENO);
        else
            dup2(p[1], STDIN_FILENO);

        execvp(*argv, (char *const *)argv);
        return (1);
    }

    if (type == 'r')
    {
        close(p[0]);
        return (p[1]);
    }
    else
    {
        close(p[1]);
        return (p[0]);
    }

    return (-1);
}
