/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <vkhlghat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:03:55 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/26 13:06:11 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*check_command(char **path, char *cmd)
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

void	exec_command_1(t_pipex p, char **av, char **envp)
{
	dup2(p.fd[1], 1);
	close(p.fd[1]);
	close(p.fd[0]);
	dup2(p.infile, 0);
	close(p.infile);
	p.command_arguments = ft_split(av[2], ' ');
	p.command = check_command(p.command_paths, p.command_arguments[0]);
	if (p.command == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(p.command_arguments[0], 2);
		ft_putstr_fd("\n", 2);
		free_child(p);
		exit(1);
	}
	if (execve(p.command, p.command_arguments, envp) == -1)
		exit(1);
}

void	exec_command_2(t_pipex p, char **av, char **envp)
{
	dup2(p.fd[0], 0);
	close(p.fd[1]);
	close(p.fd[0]);
	dup2(p.outfile, 1);
	close(p.outfile);
	p.command_arguments = ft_split(av[3], ' ');
	p.command = check_command(p.command_paths, p.command_arguments[0]);
	if (p.command == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(p.command_arguments[0], 2);
		ft_putstr_fd("\n", 2);
		free_child(p);
		exit(1);
	}
	if (execve(p.command, p.command_arguments, envp) == -1)
		exit(1);
}
