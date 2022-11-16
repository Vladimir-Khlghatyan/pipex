/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	error_message(char *str)
{
	char	*err;

	err = strerror(errno);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

char	*get_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	create_pipes(t_pipex_b *pb)
{
	int	i;

	i = -1;
	while (++i < pb->command_cnt - 1)
		if (pipe(&(pb->pipes[2 * i])) == -1)
			free_parent(pb);
}

void	close_pipes(t_pipex_b *pb)
{
	int	i;

	i = -1;
	while (++i < pb->pipes_cnt)
		close(pb->pipes[i]);
}

int	argv_check(char **argv, int *here_doc)
{
	if (argv[1] && strncmp("here_doc", argv[1], 9) == 0)
	{
		*here_doc = 1;
		return (5);
	}
	else
	{
		*here_doc = 0;
		return (4);
	}
	return (0);
}
