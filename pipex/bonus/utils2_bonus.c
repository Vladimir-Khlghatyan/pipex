/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	open_infile(char **argv, t_pipex_b *pb)
{
	if (pb->here_doc == 1)
		here_doc(argv, pb);
	else
	{
		pb->infile = open(argv[1], O_RDONLY);
		if (pb->infile == -1)
			error_message(argv[1]);
	}
}

void	open_outfile(int argc, char **argv, t_pipex_b *pb)
{
	if (pb->here_doc == 1)
		pb->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pb->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pb->outfile == -1)
		error_message(argv[argc - 1]);
}

void	here_doc(char **argv, t_pipex_b *pb)
{
	int		fd;
	char	*buffer;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		error_message("here_doc");
	while (1)
	{
		write(1, "here_doc> ", 10);
		buffer = get_next_line(0);
		if (!buffer)
			exit(1);
		if (ft_strncmp(argv[2], buffer, ft_strlen(argv[2])) == 0)
			break ;
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
	}
	free(buffer);
	close(fd);
	pb->infile = open(".here_doc", O_RDONLY);
	if (pb->infile == -1)
		unlink(".here_doc");
	if (pb->infile == -1)
		error_message("here_doc");
}

void	wait_for_children(t_pipex_b *pb)
{
	int	i;

	i = -1;
	while (++i < pb->command_cnt)
		waitpid(pb->pid, NULL, 0);
}
