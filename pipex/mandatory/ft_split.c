/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:46:00 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/11 18:57:00 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**tabfree(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

static int	wordcount(char *s, char c)
{
	int	q;
	int	i;

	q = 0;
	i = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	if (s[i++] != '\0')
		q = 1;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			q++;
		i++;
	}
	return (q);
}

static int	wordlen(char *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		wc;
	int		i[2];

	if (!s)
		return (NULL);
	i[0] = -1;
	wc = wordcount(s, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	while (++i[0] < wc)
	{
		tab[i[0]] = (char *)malloc(sizeof(char) * (wordlen(s, c) + 1));
		if (!tab[i[0]])
			return (tabfree(tab));
		while (*s == c)
			s++;
		i[1] = 0;
		while (*s != c && *s)
			tab[i[0]][i[1]++] = *s++;
		tab[i[0]][i[1]] = '\0';
	}
	tab[i[0]] = NULL;
	return (tab);
}
