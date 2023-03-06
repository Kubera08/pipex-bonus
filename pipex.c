/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:56:33 by abeaudui          #+#    #+#             */
/*   Updated: 2023/03/06 17:53:21 by abeaudui         ###   ########.fr       */
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
	char *str;
	char **tab;
	tab = ft_split(pipex.cmd[j], ' ');
	str = ft_strjoin("/bin/", tab[0]);
	return(str);
	
}
// BONUS PART TEST


// A FAIRE :

// creer tableau pour stocker nos options : **options[] 

// fermeture des extremites des pipes non utilisees
// attente de la fin de tous les processus enfants avec waitpid

int main(int ac, char **av, char **env)
{
	t_pipex pipex;
	int i;
	int j = 0;

	i = 0;

	pipex.cmd = fill_tabs(ac,av);
	
	pipex.path_pos = path_pos(env);
	pipex.envVec = ft_split(pipex.path_pos, ':');

	pipex.infile = open(av[1], O_RDONLY);
	pipex.outfile = open(av[ac -1], O_RDWR, O_CREAT);

	int process;
	process = ac - 3;

	int pids[process];// pour stocker nos PIDS
	int pipes[process -1][2]; // pour stocker nos pipe

	if (pipex.infile != -1 && pipex.outfile != -1 && ac < 5)
		return(3);
	while (i < process -1)	// on crée les pipes
	{
		if(pipe(pipes[i]) == -1)
			return 1;
		i++;
	}
	while (j < process) // on crée les process
	{
		pids[j] = fork();
		printf("%d\n", pids[j]);

		if (pids[j] == -1)
			return(1);
		if (pids[j] == 0)
		{
			if (j == 0) // premier process donc pas besoin de lire a partir de la pipe
			{
				printf("LUCAS\n");
				dup2(pipex.infile, 0);
			}
			else
				printf("2eme processus");
			if (j == process -1) // dernier process donc pas besoin d'ecrire dans la pipe
				dup2(pipex.outfile, 1);
			else // on est dans le cas d'un process intermediaire
			{
				printf("BLABLA\n");
				dup2(pipes[j - 1][0], 0); // on doit lire a partir de la pipe precedente
				dup2(pipes[j][1], 1); // on affecte la sortie standard a la sortie de notre pipe
			}
			execve(create_str(pipex, j), ft_split(pipex.cmd[j],' '), pipex.envVec);
		}
		j++;
	}
	for (int a = 0; a < process - 1; a++) {
        close(pipes[a][0]);
        close(pipes[a][1]);
	}
	
	
	
}