/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:56:33 by abeaudui          #+#    #+#             */
/*   Updated: 2023/03/08 16:38:04 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



// ./pipex file1 cmd1 cmd2 file2
//
//
//			STRUCTURE
//
//	  au total : 3 process et un pipe
// 	 1 main process et deux child process pour les deux commandes 
// 
//  exemple : infile.txt cat | wc -l outfile.txt
//  la commande cat va écrire le résutlat dans la pipe et non sur le terminal (on ferme donc l'écriture sur le terminal)
//  la commande wc -l va lire dans la pipe et non dans le terminal (on ferme donc la lecture sur le terminal)
//    
// 	  
//
//	input (keyboard input in terminal)= 0
//	output (when a command print text) = 1
//	fd1 write data
// 	fd0 read from 	



// utilité de créer des sous-processus : si pas de fork alors le processuc engendré remplacerait totalement le premier
// le fils sera en mesure de lire depuis pipefd[0] les informations fournies par son père dans pipefd[1] et inversement

#include "pipex.h"


char **fill_tabs(int ac, char **av)
{
	char **tab;
	int i;
	int j;
	j = 2;
	i = 0;
	
	tab = malloc(sizeof(char *) * ac - 3);
	while (i < ac - 3)
	{
		tab[i] = ft_strdup(av[j]);
		i++;
		j++;
		
	}
	tab[i] = NULL;
	return(tab);
	
}

char *create_str(t_pipex pipex, int j)
{
	pipex.tab = ft_split(pipex.cmd[j], ' ');
	pipex.str = ft_strjoin("/bin/", pipex.tab[0]);
	return(pipex.str);
	
}

static void ft_waitandclose(t_pipex pipex)
{
	while (pipex.a < pipex.process -1)
	{
		close(pipex.pipes[pipex.a][0]);
        close(pipex.pipes[pipex.a][1]);
		pipex.a++;
	}
	while (pipex.k < pipex.process - pipex.j)
	{
		waitpid(pipex.pids[pipex.k], NULL, 0);
		pipex.k++;
	}
}

static t_pipex init_content(t_pipex pipex, int ac, char **av, char **env)
{
	pipex.cmd = fill_tabs(ac,av);
	pipex.path_pos = path_pos(env);
	pipex.envVec = ft_split(pipex.path_pos, ':');
	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[ac -1], O_RDWR, O_CREAT);
	pipex.j = -1;
	pipex.i = 0;
	pipex.a = 0;
	pipex.k = 0;
	pipex.process = ac - 3;
	pipex.pids[0] = ac - 3;
	pipex.pipes[0][2] = ac - 4;
	return (pipex);
}

static void ft_dup(int a, int b, int c, int d)
{
	dup2(a, b);
	dup2(c, d);
}

int main(int ac, char **av, char **env)
{
	t_pipex pipex;

	pipex = init_content(pipex, ac, av, env);
	if (pipex.infile != -1 && pipex.outfile != -1 && ac < 5)
		return(3);
	while (pipex.i < pipex.process -1)	// on crée les pipes
		if (pipe(pipex.pipes[pipex.i++]) == -1)
			return (1);
	while (pipex.j++ < pipex.process && (pipex.pids[pipex.j] = fork()) != -1)  // on crée les process
	{
		if (pipex.pids[pipex.j] == 0)
		{
			if (pipex.j == 0) // premier process donc pas besoin de lire a partir de la pipe
				dup2(pipex.infile, 0);
			if (pipex.j == pipex.process -1) // dernier process donc pas besoin d'ecrire dans la pipe
				ft_dup(pipex.pipes[pipex.j-1][0], 0, pipex.outfile, 1);
			else // on est dans le cas d'un process intermediaire
				ft_dup(pipex.pipes[pipex.j -1][0], 0, pipex.pipes[pipex.j][1], 1); // on doit lire a partir de la pipe precedente && on affecte la sortie standard a la sortie de notre pipe
			if (execve(create_str(pipex, pipex.j), ft_split(pipex.cmd[pipex.j],' '), pipex.envVec) == -1)
				return 3;
		}
	}
	ft_waitandclose(pipex);
	ft_free(pipex);
}