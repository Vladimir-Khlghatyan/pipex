/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <vkhlghat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:46:00 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/11 18:57:00 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static char	**tabfree(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**malloccheck(char **tab)
{
	if (!tab)
		return (NULL);
	return (tab);
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

static int	wordlen(char *s, char c, int index)
{
	int	q;
	int	i;
	int	len;

	q = 0;
	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	if (s[i++] != '\0')
		q = 1;
	while (s[i])
	{
		while (index == q - 1 && s[i - 1] && s[i - 1] != c)
		{
			len++;
			i++;
		}
		if (s[i] != c && s[i - 1] == c)
			q++;
		i++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		wc;
	int		i;
	int		t;

	if (!s)
		return (NULL);
	i = -1;
	wc = wordcount(s, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	malloccheck(tab);
	while (++i < wc)
	{
		tab[i] = (char *)malloc(sizeof(char) * (wordlen(s, c, i) + 1));
		if (!tab[i])
			return (tabfree(tab));
		while (*s == c)
			s++;
		t = 0;
		while (*s != c && *s)
			tab[i][t++] = *s++;
		tab[i][t] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}
