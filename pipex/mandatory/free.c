/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_child(t_pipex p)
{
	int	i;

	i = 0;
	while (p.command_arguments[i])
	{
		free(p.command_arguments[i]);
		i++;
	}
	free(p.command_arguments);
	free(p.command);
}

void	free_parent(t_pipex p)
{
	int	i;

	close(p.infile);
	close(p.outfile);
	i = 0;
	while (p.command_paths[i])
	{
		free(p.command_paths[i]);
		i++;
	}
	free(p.command_paths);
}
