/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:52:44 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/25 18:52:48 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <errno.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**command_paths;
	char	**command_arguments;
	char	*command;
}				t_pipex;

/* exec_command.c */
char	*check_command(char **path, char *cmd);
void	exec_command_1(t_pipex p, char **av, char **envp);
void	exec_command_2(t_pipex p, char **av, char **envp);

/* free.c */
void	free_child(t_pipex p);
void	free_parent(t_pipex p);

/* ft_libft.c */
int		ft_strlen( char *str);
int		ft_putstr_fd(char *str, int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);

/* ft_split.c */
char	**ft_split(char *s, char c);

/* utils.c */
void	error_message(char *str);
char	*get_path(char **envp);
pid_t	fork_and_check(void);
void	close_pipe(int fd[2]);
void	wait_for_children(pid_t pid1, pid_t pid2);

#endif
