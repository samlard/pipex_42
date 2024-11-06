/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:42:11 by ssoumill          #+#    #+#             */
/*   Updated: 2024/08/12 21:34:56 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **buffer, char *str)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i])
		{
			free(buffer[i]);
			i++;
		}
		free(buffer);
	}
	if (str)
		free(str);
}

char	**ft_get_path(char **env, int i)
{
	char	**s_path;

	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			s_path = ft_split(ft_substr(env[i], 5, ft_strlen(env[i])), ':');
		i++;
	}
	return (s_path);
}

char	*ft_exec(char **env, char **cmd, int j)
{
	char	*exec;
	char	*tmp;
	char	**s_path;

	if (access(cmd[0], X_OK) != -1)
		return (cmd[0]);
	if (!env[0])
		return (NULL);
	s_path = ft_get_path(env, 0);
	while (s_path[j] && s_path)
	{
		tmp = ft_strjoin(s_path[j], "/");
		exec = ft_strjoin(tmp, cmd[0]);
		if (access(exec, X_OK) != -1)
		{
			ft_free(s_path, tmp);
			return (exec);
		}
		j++;
		free(tmp);
		free(exec);
	}
	ft_free(s_path, NULL);
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd >= 0 && s)
	{
		i = 0;
		while (s[i])
		{
			write(fd, s + i, 1);
			i++;
		}
	}
}

char	*ft_prepare_split(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	if ((count % 2) == 1)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != 39)
	{
		if (str[i] == 32)
			str[i] = 1;
		i++;
	}
	while (str[i])
	{
		if (str[i] == 39)
			str[i] = 1;
		i++;
	}
	return (str);
}
