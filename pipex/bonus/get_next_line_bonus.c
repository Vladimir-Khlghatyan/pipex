/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:00:39 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/03/26 21:33:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*upto_first_nl_or_0(char *str)
{
	char	*short_str;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	short_str = (char *)malloc(sizeof(char) *(i + 2));
	if (!short_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		short_str[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		short_str[i] = '\n';
		i++;
	}
	short_str[i] = '\0';
	return (short_str);
}

char	*after_nl(char *str)
{
	char	*short_str;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	short_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!short_str)
		return (NULL);
	short_str = ft_copy(short_str, str + i + 1);
	free(str);
	return (short_str);
}

char	*get_next_line(int fd)
{
	static char	*temp[65535];
	char		*line;

	if (fd < 0 || fd > 65535)
		return (NULL);
	temp[fd] = read_from_file(fd, temp[fd]);
	if (!temp[fd])
		return (NULL);
	line = upto_first_nl_or_0(temp[fd]);
	temp[fd] = after_nl(temp[fd]);
	return (line);
}
