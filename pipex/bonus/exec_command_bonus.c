/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*check_cmd(char **path, char *cmd)
{
	int		i;
	char	*command;
	char	*full_path;

	if (access(cmd, 0) == 0)
		return (cmd);
	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], "/");
		command = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	double_dup2(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
}

void	exec_command(t_pipex_b pb, char **av, char **envp)
{
	pb.pid = fork();
	if (pb.pid == -1)
		exit (1);
	if (pb.pid == 0)
	{
		if (pb.i == 0)
			double_dup2(pb.infile, pb.pipes[1]);
		else if (pb.i == pb.command_cnt - 1)
			double_dup2(pb.pipes[2 * pb.i - 2], pb.outfile);
		else
			double_dup2(pb.pipes[2 * pb.i - 2], pb.pipes[2 * pb.i + 1]);
		close_pipes(&pb);
		pb.command_arguments = ft_split(av[2 + pb.here_doc + pb.i], ' ');
		pb.command = check_cmd(pb.command_paths, pb.command_arguments[0]);
		if (pb.command == NULL)
		{
			ft_putstr_fd("pipex: command not found: ", 2);
			ft_putstr_fd(pb.command_arguments[0], 2);
			ft_putstr_fd("\n", 2);
			free_child(&pb);
			exit(1);
		}
		if (execve(pb.command, pb.command_arguments, envp) == -1)
			exit(1);
	}
}
