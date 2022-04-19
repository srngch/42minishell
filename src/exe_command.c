#include "minishell.h"

void    set_builtin_pipe()
{
    int		fds[2];

	pipe(fds);
    dup2(fds[0], STDIN_FILENO);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[0]);
    close(fds[1]);
}

int is_builtin(char **cmd)
{
    if (!ft_strcmp(*cmd, "cd"))
        return (1);
    if (!ft_strcmp(*cmd, "echo"))
        return (2);
    if (!ft_strcmp(*cmd, "env"))
        return (3);
    if (!ft_strcmp(*cmd, "exit"))
        return (4);
    if (!ft_strcmp(*cmd, "export"))
        return (5);
    if (!ft_strcmp(*cmd, "pwd"))
        return (6);
    if (!ft_strcmp(*cmd, "unset"))
        return (7);
    return (0);
}

void route_builtin(char **cmd, int n)
{
    if (n == 1)
        return (ft_cd(cmd));
    if (n == 2)
        return (ft_echo(cmd));
    if (n == 3)
        return (ft_env(cmd));
    if (n == 4)
        return (ft_exit(cmd));
    if (n == 5)
        return (ft_export(cmd));
    if (n == 6)
        return (ft_pwd(cmd));
    if (n == 7)
        return (ft_unset(cmd));
}

int exe_builtin(char **cmd)
{
    int n;

    n = is_builtin(cmd);
    if (n)
    {
        set_builtin_pipe();
        route_builtin(cmd, n);
        restore_ori_stdout();
    }
    return (n);
}

int exe_execve(char **command)
{
    pid_t   pid;
    int     fds[2];
    int     status;
    char    **envp;

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        set_pipein_to_stdout(fds);
        envp = find_all_env();
        if (access(command[0], X_OK) != 0)
        command[0] = find_command_path(command[0]);
        if (execve(command[0], command, envp) == -1)
        {
            perror("command not found");
            exit (127);
        }
        return (0);
    }
    set_pipeout_to_stdin(fds);
    waitpid(pid, &status, 0);
    g_mini.exit_status = status;
    return (1);
}