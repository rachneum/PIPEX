/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:10:02 by rachou            #+#    #+#             */
/*   Updated: 2024/07/04 14:52:51 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	open_files(char *argv1, char *argv2, bool boolean)
{
	int	fd;

	if (boolean == true)
		fd = open(argv1, O_RDONLY, 0777);
	if (boolean == false)
		fd = open(argv2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

char	*get_path(char *s_cmd, char **env, int i)
{
	char	**split_path;
	char	*path;
	char	*full_path;

	if (!access(s_cmd, X_OK))
		return (s_cmd);
	if (check_path(env) == -1)
		ft_error("ERROR: The PATH does not exist in the environment!\n");
	if (!env[check_path(env)])
		return (s_cmd);
	split_path = ft_split(env[check_path(env)] + 5, ':');
	if (!split_path)
		return (NULL);
	while (split_path[++i])
	{
		path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(path, s_cmd);
		if (!path || !full_path)
			ft_free(path, full_path);
		if (!access(full_path, X_OK))
			return (full_path);
		if (full_path)
			free(full_path);
	}
	return (ft_free_tab(split_path));
}
