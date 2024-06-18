/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:26:03 by rachou            #+#    #+#             */
/*   Updated: 2024/06/18 15:17:06 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int ft_open_files(char *name, int nb)
{
    int	fd;

	fd = 0;
	if (nb == 1)
	{
		fd = open(name, O_RDONLY);
		dup2(fd, 0);
	}
	if (nb == 2)
	{
		fd = open(name, O_WRONLY, O_CREAT, O_TRUNC, 0777);
		dup2(fd, 1);
	}
	if (fd == -1)
		return (-1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
    //if (argc != 5)
    //    return (0);
    int	i;

	//if (ft_open_files(argv[1], 1) == -1 || ft_open_files(argv[4], 2) == -1)
	//	return (0);
    i = 0;
    while (env[i])
    {
        if (ft_strncmp("PATH", env[i], 4) == 0)
            printf("%s\n", env[i]);
        i++;
    }
}