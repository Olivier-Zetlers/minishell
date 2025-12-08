/* ************************************************************************** */
/*   process_manager.c — Incremental pipe creation for pipelines              */
/* ************************************************************************** */

#include "executor.h"
#include "builtins.h"
#include "signals.h"
#include "utils.h"

/*
** Sets up file descriptors in child process:
** - prev_read: read end of PREVIOUS pipe → becomes STDIN
** - pipe_fd[1]: write end of CURRENT pipe → becomes STDOUT (if not last cmd)
*/
static void	child_setup_fds(int prev_read, int pipe_fd[2], int has_next)
{
    if (prev_read != -1)
    {
        dup2(prev_read, STDIN_FILENO);
        close(prev_read);
    }
    if (has_next)
    {
        close(pipe_fd[0]);  // Child doesn't read from current pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
}

/*
** Executes the actual command in child process after FD setup
*/
static void	exec_child_cmd(t_shell *shell, t_cmd *cmd, char **envp)
{
    char	*path;
    int		status;

    path = resolve_path(cmd->argv[0], shell->env);
    if (!path && !ft_strchr(cmd->argv[0], '/'))
    {
        status = try_exec_no_search(cmd->argv, envp);
        ft_free_array(envp);
        exit(status);
    }
    if (path)
        execve(path, cmd->argv, envp);
    else
        execve(cmd->argv[0], cmd->argv, envp);
    print_errno_error(cmd->argv[0], NULL);
    ft_free_array(envp);
    if (errno == ENOENT)
        exit(127);
    exit(126);
}

/*
** Child process entry point: sets up FDs, redirections, then execs
*/
static void	exec_child(t_shell *shell, t_cmd *cmd, int prev_rd, int pfd[2])
{
    char	**envp;

    setup_signals(SIG_CHILD);
    child_setup_fds(prev_rd, pfd, cmd->next != NULL);
    if (setup_redirections(cmd->redirects) == -1)
        exit(1);
    if (!cmd->argv || !cmd->argv[0])
        exit(0);
    if (is_builtin(cmd->argv[0]))
        exit(execute_builtin(shell, cmd->argv));
    envp = env_to_array(shell->env);
    if (!envp)
        exit(1);
    exec_child_cmd(shell, cmd, envp);
}

/*
** Forks ONE command, creating pipe only if needed (not last command)
** Updates prev_read to point to read end for next iteration
*/
int	fork_one_cmd(t_shell *sh, t_cmd *cmd, int *prev_read, int pfd[2])
{
    pid_t	pid;

    if (cmd->next && pipe(pfd) == -1)  // Create pipe ONLY if not last
        return (-1);
    pid = fork();
    if (pid == 0)
        exec_child(sh, cmd, *prev_read, pfd);
    // Parent cleanup: close FDs no longer needed
    if (*prev_read != -1)
        close(*prev_read);  // Done reading from previous pipe
    if (cmd->next)
        close(pfd[1]);      // Parent doesn't write to current pipe
    // Update prev_read for next iteration
    if (cmd->next)
        *prev_read = pfd[0];
    else
        *prev_read = -1;
    return (pid);
}
