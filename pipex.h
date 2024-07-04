/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:52:19 by raneuman          #+#    #+#             */
/*   Updated: 2024/07/04 12:55:10 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, int n);
int		path(char **env);
int		open_files(char *argv1, char *argv2, bool boolean);
int		ft_strlen(const char *s);

char	*get_path(char *s_cmd, char **env, int i);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_free_tab(char **cmd);

void	child_parent_ex(char **argv, char **env, int *pipe_fd, bool boolean);
void	ft_exec(char *cmd, char **env);
void	ft_putstr_fd(char *s, int fd);
void	ft_free(char *path, char *full_path);
void	ft_error(char *str);

#endif