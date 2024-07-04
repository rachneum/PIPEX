/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raneuman <raneuman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:03 by raneuman          #+#    #+#             */
/*   Updated: 2024/07/04 13:45:35 by raneuman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = NULL;
	path = NULL;
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		exit(EXIT_FAILURE);
	path = get_path(split_cmd[0], env, -1);
	if (!path)
	{
		perror("CMD: ");
		ft_free_tab(split_cmd);
		exit(127);
	}
	if (execve(path, split_cmd, env) == -1)
	{
		perror("EXEC: ");
		ft_free_tab(split_cmd);
		exit(126);
	}
}

void	child_parent_ex(char **argv, char **env, int *pipe_fd, bool boolean)
{
	int	fd;

	fd = open_files(argv[1], argv[4], boolean);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (boolean == true)
	{
		dup2(fd, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		ft_exec(argv[2], env);
	}
	if (boolean == false)
	{
		dup2(pipe_fd[0], 0);
		dup2(fd, 1);
		close(pipe_fd[1]);
		ft_exec(argv[3], env);
	}
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (argc != 5)
		ft_error("ERROR: There is not 5 arguments!\n");
	if (pipe(pipe_fd) == -1)
		ft_error("ERROR: The cration of the pipe has failed!\n");
	pid = fork();
	if (pid == -1)
		ft_error("ERROR: Fork has failed!\n");
	if (pid == 0)
		child_parent_ex(argv, env, pipe_fd, true);
	child_parent_ex(argv, env, pipe_fd, false);
}
