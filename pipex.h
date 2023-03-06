/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:54:23 by arnaud            #+#    #+#             */
/*   Updated: 2023/03/06 15:13:18 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
 #include <fcntl.h>


typedef struct s_pipex
{
	int pid;
	int fd[2];
	int infile;
	int outfile;
	char **cmd;
	char *path_pos;
	char **envVec;
	char **argOptions[];
		
}	t_pipex;

void	ft_free(t_pipex pipex);
void free_tab(char **tab);
//int 	main(int ac, char **av, char **env);
int check_all(int ac, const char *file1, const char *file2 );
char *path_pos( char **env);
void first_child(t_pipex pipex);
void second_child(t_pipex pipex);
void daddy(t_pipex pipex);



// UTILS
int	ft_countword(char *s, char c);
char	*tab_filler(char  *s, char c);
char	**ft_split(char  *s, char c);
int		ft_strncmp(char *s1,  char *s2, size_t n);
char	*ft_strjoin(char  *s1, char  *s2);
char	*ft_strdup(char *src);
int	ft_strlen(char *str);


#endif