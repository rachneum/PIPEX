#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, int n);
int path(char **env);
int open_files(char *argv1, char *argv2, bool boolean);

char    *get_path(char **env, char *s_cmd);
char	**ft_split(char const *s, char c);

#endif