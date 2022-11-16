/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_strjoin_upd(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr_upd(char *s, int c)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	str = (char *) s;
	i = ft_strlen(str);
	if (c == '\0')
		return (str + i);
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char) c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_copy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*read_from_file(int fd, char *temp)
{
	char	*buf;
	int		sz;

	buf = (char *)malloc(42 + 1);
	if (!buf)
		return (NULL);
	sz = 1;
	while (!ft_strchr_upd(temp, '\n') && sz != 0)
	{
		sz = read(fd, buf, 42);
		if (sz == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[sz] = '\0';
		temp = ft_strjoin_upd(temp, buf);
	}
	free(buf);
	return (temp);
}
