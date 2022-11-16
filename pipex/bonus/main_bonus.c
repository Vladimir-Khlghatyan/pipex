/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex_b	pb;

	pb.here_doc = 0;
	if (ac - 1 < argv_check(av, &pb.here_doc))
		return (ft_putstr_fd("pipex: invalitd number of arguments\n", 2));
	open_infile(av, &pb);
	open_outfile(ac, av, &pb);
	pb.command_cnt = ac - 1 - 2 - pb.here_doc;
	pb.pipes_cnt = (pb.command_cnt - 1) * 2;
	pb.pipes = (int *)malloc(sizeof(int) * pb.pipes_cnt);
	if (!pb.pipes)
		error_message("pipes");
	pb.command_paths = ft_split(get_path(envp), ':');
	if (!pb.command_paths)
		free_pipes(&pb);
	create_pipes(&pb);
	pb.i = -1;
	while (++(pb.i) < pb.command_cnt)
		exec_command(pb, av, envp);
	close_pipes(&pb);
	wait_for_children(&pb);
	free_parent(&pb);
	return (0);
}
