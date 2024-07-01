/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rachou <rachou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:41:03 by raneuman          #+#    #+#             */
/*   Updated: 2024/06/28 14:23:09 by rachou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char *path, char *full_path)
{
	free(path);
	free(full_path);
}

static void	ft_free_tab(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != NULL)	
			free(cmd[i]);
		i++;
	}
}

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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

 char	*ft_strjoin(char *s1, char *s2)//alloue et retourne une nouvelle chaîne qui est la concaténation de s1 et s2, ou NULL en cas d'échec d'allocation ou si l'un des arguments est NULL.
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char    *get_path(char *s_cmd, char **env, int i)//vérifie si s_cmd est exécutable et, si ce n'est pas le cas, extrait et divise la variable d'environnement PATH pour rechercher le chemin de la commande.
{
	char	**split_path;
	char	*path;
	char	*full_path;

	if (!access(s_cmd, X_OK))//vérifie si la cmd est déjà exécutable
		return (s_cmd);
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			break ;
		i++;
	}
	split_path = ft_split(env[i] + 5, ':');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
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

static void ft_exec(char *cmd, char **env)//divise la commande en arguments, cherche le chemin de la commande dans l'environnement, et exécute la commande, affichant un message d'erreur et sortant avec un code d'erreur approprié si la commande ne peut pas être trouvée ou exécutée.
{
    char	**split_cmd;
	char	*path;
   
	split_cmd = NULL;
	path = NULL; 
	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		exit(EXIT_FAILURE);
	path = get_path(split_cmd[0], env, 0);
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

int open_files(char *argv1, char *argv2, bool boolean)//ouvre un fichier en lecture ou en écriture selon la valeur du booléen, retournant le descripteur de fichier correspondant.
{
    int fd;

    if (boolean == true)
        fd = open(argv1, O_RDONLY, 0777);
    if (boolean == false)
        fd = open(argv2, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    return (fd);
}

static void child_parent_ex(char **argv, char **env, int *pipe_fd, bool boolean)//redirige les entrées/sorties standard pour un processus enfant en fonction d'un booléen, exécute un fichier, et utilise un pipe pour la communication entre processus parent et enfant.
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
		dup2(pipe_fd[0], 0);
        dup2(fd, 1);
		close(pipe_fd[1]);
		ft_exec(argv[3], env);
    }
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

int main(int argc, char **argv, char **env)
{
    pid_t   pid;//pid == numéro de matricule (ex: le pid du child = 0).
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
