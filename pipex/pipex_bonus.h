/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:52:44 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/04/25 18:52:48 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <errno.h>

typedef struct s_pipex_b
{
	int		infile;
	int		outfile;
	int		pipes_cnt;
	int		*pipes;
	int		here_doc;
	int		command_cnt;
	char	*command;
	char	**command_paths;
	char	**command_arguments;
	int		i;
	pid_t	pid;
}				t_pipex_b;

/* exec_command_conus.c */
char	*check_cmd(char **path, char *cmd);
void	double_dup2(int in, int out);
void	exec_command(t_pipex_b pb, char **av, char **envp);

/* free_bonus.c */
void	free_child(t_pipex_b *pb);
void	free_parent(t_pipex_b *pb);
void	free_pipes(t_pipex_b *pb);

/* ft_libft_bonus.c */
int		ft_strlen( char *str);
int		ft_putstr_fd(char *str, int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);

/* ft_split_bonus.c */
char	**ft_split(char *s, char c);

/* get_next_line_bonus.c */
char	*upto_first_nl_or_0(char *str);
char	*after_nl(char *str);
char	*get_next_line(int fd);

/* get_next_line_utils_bonus.c */
char	*ft_strjoin_upd(char *s1, char *s2);
char	*ft_strchr_upd(char *s, int c);
char	*ft_copy(char *s1, char *s2);
char	*read_from_file(int fd, char *temp);

/* utils1_bonus.c */
void	error_message(char *str);
char	*get_path(char **envp);
void	create_pipes(t_pipex_b *pb);
void	close_pipes(t_pipex_b *pb);
int		argv_check(char **argv, int *here_doc);

/* utils2_bonus.c */
void	open_infile(char **argv, t_pipex_b *pb);
void	open_outfile(int argc, char **argv, t_pipex_b *pb);
void	here_doc(char **argv, t_pipex_b *pb);
void	wait_for_children(t_pipex_b *pb);

#endif
