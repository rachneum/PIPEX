/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:03 by raneuman          #+#    #+#             */
/*   Updated: 2024/06/24 14:40:09 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, int n)//compare les 1er n caractères des chaînes s1 et s2, renvoit un entier négatif, nul ou positif selon que s1 est <, = , > à s2.
{
	int	i;

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

int path(char **env)//vérifie que le Path existe dans l’environnement.
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp("PATH", env[i], 4) == 0)
            return (1);
        i++;
    }
    return (0);
}
char    *get_path(char **env, char *s_cmd)//vérifie si s_cmd est exécutable et, si ce n'est pas le cas, extrait et divise la variable d'environnement PATH pour rechercher le chemin de la commande.
{
    int     i;
    char    **all_path;
    
    if (!access(s_cmd, X_OK))
        return (s_cmd);
    i = 0;
    while (env[i])
    {
        if (ft_strncmp("PATH", env[i], 4) == 0)
            break;
        i++;
    }
    all_path = ft_split(env[i + 5], ':');
    
}

static void ft_exec(char *cmd, char **env)
{
    char    **s_cmd;
    char    *path;

    s_cmd = ft_split(cmd, ' ');
    path = get_path(env, s_cmd[0]);
    
    
}

int open_files(char *argv1, char *argv2, bool boolean)
{
    int fd;

    if (boolean == true)
        fd = open(argv1, O_RDONLY, 0777);
    if (boolean == false)
        fd = open(argv2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    return (fd);
}

static void child_parent_ex(char **argv, char **env, int *pipe_fd, bool boolean)
{
    int fd;

    fd = open_files(argv[1], argv[4], boolean);
    if (fd == -1)
        exit(EXIT_FAILURE);
    if (boolean == true)
    {
        dup2(fd, 0);//redirige l'entrée standard pour qu'elle vienne d'un fichier (redirige fd vers le descripteur de fichier 0, qui est généralement l'entrée standard (stdin)).
        dup2(pipe_fd[1], 1);//redirige la sortie standard pour qu'elle aille dans un pipe, permettant au processus parent de lire cette sortie.
        close(pipe_fd[0]);//assure que l'extrémité de lecture du pipe est fermée dans le processus enfant, car le processus enfant n'en a pas besoin.
        ft_exec(argv[2], env);//exécute un nouveau programme, utilisant les redirections mises en place juste avant.
    }
    if (boolean == false)
    {
        //dup2(fd, 0);
        dup2(fd, 1);
    }
}

int main(int argc, char **argv, char **env)
{
    pid_t   pid;
    int     pipe_fd[2];//tube de communication
    
    if (path(env) == 0)
        return (0);
    if (argc != 5)
        return (0);
    if (pipe(pipe_fd) == -1)//lance ma fct pipe et la vérifie simultanément.
        exit(EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0)
        child_parent_ex(argv, env, pipe_fd, true);
    child_parent_ex(argv, env, pipe_fd, false);
}
//pid == numéro de matricule
//ex: le pid du child = 0.