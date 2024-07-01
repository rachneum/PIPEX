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
int	ft_strlen(const char *s);

char    *get_path(char *s_cmd, char **env, int i);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);

#endif