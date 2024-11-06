/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:39:35 by ssoumill          #+#    #+#             */
/*   Updated: 2024/11/04 13:25:12 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(t_data *v)
{
	close(v->fd1);
	close(v->fd2);
	close(v->pipe_fd[0]);
	close(v->pipe_fd[1]);
}

void	ft_quit(char *str, int i, t_data *variable)
{
	if (errno)
	{
		perror(str);
		errno = 0;
	}
	else
		ft_putendl_fd(str, 2);
	if (i == 0)
	{
		if (variable->fd1 != -1)
			close(variable->fd1);
		if (variable->fd2 != -1)
			close(variable->fd2);
		exit(EXIT_FAILURE);
	}
}

void	ft_child1(t_data *variable, char **env, char **cmd)
{
	char	*temp;

	temp = ft_prepare_split(cmd[2], 0);
	variable->cmd1 = ft_split(temp, 1);
	variable->path1 = ft_exec(env, variable->cmd1, 0);
	if (variable->path1 == NULL)
	{
		ft_putstr_fd("cmd1 not found : ", 2);
		if (!variable->cmd1[0])
			write(2, "\n", 1);
		ft_putendl_fd(variable->cmd1[0], 2);
		ft_free(variable->cmd1, variable->path1);
		exit(EXIT_FAILURE);
	}
	dup2(variable->fd1, STDIN_FILENO);
	dup2(variable->pipe_fd[1], STDOUT_FILENO);
	ft_close(variable);
	execve(variable->path1, variable->cmd1, env);
}

void	ft_child2(t_data *variable, char **env, char **cmd)
{
	char	*temp;

	temp = ft_prepare_split(cmd[3], 0);
	variable->cmd2 = ft_split(temp, 1);
	variable->path2 = ft_exec(env, variable->cmd2, 0);
	if (variable->path2 == NULL)
	{
		ft_putstr_fd("cmd2 not found : ", 2);
		if (!variable->cmd2[0])
			write(2, "\n", 1);
		ft_putendl_fd(variable->cmd2[0], 2);
		ft_free(variable->cmd2, variable->path2);
		exit(EXIT_FAILURE);
	}
	dup2(variable->pipe_fd[0], STDIN_FILENO);
	dup2(variable->fd2, STDOUT_FILENO);
	ft_close(variable);
	execve(variable->path2, variable->cmd2, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	variable;

	if (argc != 5)
		ft_quit("mauvais input : ./pipex file1 <cmd1> <cmd2> file2", 0,
			&variable);
	variable.fd1 = open(argv[1], O_RDONLY);
	if (variable.fd1 == -1)
		ft_quit(argv[1], 1, &variable);
	variable.fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (variable.fd2 == -1)
		ft_quit(argv[4], 0, &variable);
	if (pipe(variable.pipe_fd) == -1)
		ft_quit("error when opening the pipe", 0, &variable);
	if (variable.fd1 != -1)
		variable.pid1 = fork();
	if (variable.pid1 == 0)
		ft_child1(&variable, env, argv);
	variable.pid2 = fork();
	if (variable.pid2 == 0)
		ft_child2(&variable, env, argv);
	ft_close(&variable);
	if (variable.fd1 != -1)
		waitpid(variable.pid1, NULL, 0);
	waitpid(variable.pid2, NULL, 0);
	return (0);
}
