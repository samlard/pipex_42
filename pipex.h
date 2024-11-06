/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssoumill <ssoumill@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:37:25 by ssoumill          #+#    #+#             */
/*   Updated: 2024/11/04 13:22:04 by ssoumill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct t_data
{
	int		fd1;
	int		fd2;
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}			t_data;

void		ft_free(char **buffer, char *str);
char		**ft_get_path(char **env, int i);
char		*ft_exec(char **env, char **cmd, int j);
void		ft_quit(char *str, int i, t_data *variable);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
void		ft_putstr_fd(char *s, int fd);
char		*ft_prepare_split(char *str, int i);

#endif
