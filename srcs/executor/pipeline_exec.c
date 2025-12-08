/* ************************************************************************** */
/*   pipeline_exec.c — Pipeline orchestration with incremental pipe creation  */
/* ************************************************************************** */

#include "executor.h"
#include "signals.h"
#include "utils.h"

int	fork_one_cmd(t_shell *sh, t_cmd *cmd, int *prev_read, int pfd[2]);

static int	count_commands(t_cmd *commands)
{
    int		count;
    t_cmd	*cmd;

    count = 0;
    cmd = commands;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

static int	fork_all_cmds(t_shell *shell, t_cmd *cmds, int *pids, int count)
{
    int		i;
    int		prev_read;
    int		pipe_fd[2];
    t_cmd	*cmd;

    prev_read = -1;  // No previous pipe initially
    i = 0;
    cmd = cmds;
    (void)count;
    while (cmd)
    {
        pids[i] = fork_one_cmd(shell, cmd, &prev_read, pipe_fd);
        if (pids[i] < 0)
            return (1);
        cmd = cmd->next;
        i++;
    }
    return (0);
}

static void	handle_pipeline_signals(t_shell *shell)
{
    if (shell->last_status == 130)
        write(1, "\n", 1);
    else if (shell->last_status == 131)
        write(2, "Quit (core dumped)\n", 19);
}

int	execute_pipeline(t_shell *shell, t_cmd *commands)
{
    int		*pids;
    int		count;

    count = count_commands(commands);
    pids = safe_malloc(sizeof(int) * count);
    if (!pids)
        return (1);
    if (fork_all_cmds(shell, commands, pids, count) != 0)
    {
        free(pids);
        return (1);
    }
    setup_signals(SIG_EXECUTING);
    shell->last_status = wait_for_children(pids, count);
    if (shell->interactive)
        setup_signals(SIG_INTERACTIVE);
    handle_pipeline_signals(shell);
    free(pids);
    return (shell->last_status);
}
