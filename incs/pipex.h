/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:38:53 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/24 10:29:27 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/incs/libft.h"

typedef struct s_pipex
{
	int		idx;
	int		heredoc;
	int		nb_args;
	int		nb_pipes;
	int		pid;
	int		fd1;
	int		fd2;
	int		*tmp;
	char	*cmd;
	char	**path;
}	t_pipex;

int		print_err(char *msg);

void	multi_dup2(int fd1, int fd2);

char	**get_path(char **envp);

char	*get_cmd(char **paths, char *cmd);

void	here_doc(t_pipex *pipex, char *arg);

int		args_cmp(t_pipex *pipex, int argc, char **argv);

#endif
