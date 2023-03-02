/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:47:59 by abeaudui          #+#    #+#             */
/*   Updated: 2023/02/23 13:49:37 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex)
{
	char	*str;
	
	dup2(pipex.fd[1], 1);
	close(pipex.fd[0]);
	dup2(pipex.infile, 0);
	str = ft_strjoin("/bin/", pipex.argOptions1[0]);
	execve(str, pipex.argOptions1, pipex.envVec);
}

void	second_child(t_pipex pipex)
{
	char	*str;
	
	dup2(pipex.fd[0], 0);
	close(pipex.fd[1]);
	dup2(pipex.outfile, 1);
	str = ft_strjoin("/bin/", pipex.argOptions2[0]);
	execve(str, pipex.argOptions2, pipex.envVec);
}