/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <vkhlghat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	free_child(t_pipex_b *pb)
{
	int	i;

	i = 0;
	while (pb->command_arguments[i])
	{
		free(pb->command_arguments[i]);
		i++;
	}
	free(pb->command_arguments);
	free(pb->command);
}

void	free_parent(t_pipex_b *pb)
{
	int	i;

	close(pb->infile);
	close(pb->outfile);
	if (pb->here_doc == 1)
		unlink(".here_doc");
	i = 0;
	while (pb->command_paths[i])
	{
		free(pb->command_paths[i]);
		i++;
	}
	free(pb->command_paths);
	free(pb->pipes);
}

void	free_pipes(t_pipex_b *pb)
{
	close(pb->infile);
	close(pb->outfile);
	if (pb->here_doc == 1)
		unlink(".here_doc");
	free(pb->pipes);
	ft_putstr_fd("Environment error!", 2);
	exit(1);
}
