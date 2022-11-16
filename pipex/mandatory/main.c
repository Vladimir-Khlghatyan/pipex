/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;

	if (ac - 1 != 4)
		return (ft_putstr_fd("pipex: invalitd number of arguments\n", 2));
	p.infile = open(av[1], O_RDONLY);
	if (p.infile == -1)
		error_message(av[1]);
	p.outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (p.outfile == -1)
		error_message(av[ac - 1]);
	if (pipe(p.fd) < 0)
		error_message("pipe");
	p.command_paths = ft_split(get_path(envp), ':');
	p.pid1 = fork_and_check();
	if (p.pid1 == 0)
		exec_command_1(p, av, envp);
	p.pid2 = fork_and_check();
	if (p.pid2 == 0)
		exec_command_2(p, av, envp);
	close_pipe(p.fd);
	wait_for_children(p.pid1, p.pid2);
	free_parent(p);
	return (0);
}
