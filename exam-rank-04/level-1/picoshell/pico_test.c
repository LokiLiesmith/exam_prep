#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
    pid_t pid;
    int pipefd[2];
    int prev_fd = -1;
    int status;
    int exit_code = 0;
    int i = 0;
    int child_count = 0;
	

    // LOOP TRU COMMANDS
    while (cmds[i])
    {
        if (cmds[i + 1])
        {
			// Create a pipe — only if NOT the last command
            if (pipe(pipefd) == -1)
            {
                if (prev_fd != -1)
                    close(prev_fd);
                return 1;
            }
        }
		//fork each cmd, runs its own child process
        pid = fork();
        if (pid == -1)
        {
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }
            if (prev_fd != -1)
                close(prev_fd);
            return 1;
        }


        ///CHILD EXECUTES THE PROGRAM
        if (pid == 0)
        {
            if (prev_fd != -1)//if not the first command
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(1);
                close(prev_fd);
            }
            if (cmds[i + 1])
            {
                close(pipefd[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                    exit(1);
                close(pipefd[1]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit(1);
        }
        child_count++;
        if (prev_fd != -1)
            close(prev_fd);

        if (cmds[i + 1])
        {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
        else
            prev_fd = -1;

        i++;
    }

    //WAIT FOR CHILDREN
    while (child_count-- > 0)
    {
        wait(&status);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            exit_code = 1;
    }
    return exit_code;
}


// For each command:
// Create a pipe unless last command.
// Fork a child.
// Child sets:
// stdin to previous pipe’s read end (if exists)
// stdout to new pipe’s write end (if exists)
// Child exec’s the program.
// Parent:
// Closes fds it no longer needs
// Remembers new pipe’s read end (prev_fd)
// After running all commands:
// Parent waits for ALL children
// If any exited with non-zero -> return 1