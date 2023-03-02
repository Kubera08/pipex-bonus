/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaudui <abeaudui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:16:38 by abeaudui          #+#    #+#             */
/*   Updated: 2023/02/23 13:32:52 by abeaudui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_countword(char *s, char c)
{
	int	word;
	int	check;
	int	i;

	word = 0;
	check = 0;
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		if (s[i] != c && check == 0)
		{
			check = 1;
			word++;
		}
		else if (s[i] == c)
			check = 0;
		i++;
	}
	return (word);
}

char	*tab_filler(char *s, char c)
{	
	char	*str;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (s[y] && s[y] != c)
		y++;
	str = malloc(sizeof(char) * (y + 1));
	if (!str)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		i;
	int		word;
	int		y;

	i = 0;
	y = 0;
	if (!s)
		return (NULL);
	word = ft_countword((char *)s, c);
	str = malloc(sizeof(char *) * (word + 1));
	if (!str)
		return (NULL);
	str[word] = NULL;
	while (s[i])
	{
		if (((i == 0) || (s[i - 1] == c)) && (y < word) && (s[i] != c))
		{
			str[y] = tab_filler(&s[i], c);
			y++;
		}
		i++;
	}
	return (str);
}