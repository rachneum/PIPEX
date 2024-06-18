#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_open_files(char *name, int nb);

#endif