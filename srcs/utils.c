/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:54:15 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/24 11:32:20 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

int	print_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	multi_dup2(int fd1, int fd2)
{
	dup2(fd1, 0);
	dup2(fd2, 1);
}

char	**get_path(char **envp)
{
	int		i;
	char	*env;
	char	**res;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			env = ft_substr(envp[i], 6, ft_strlen(envp[i]));
			if (!env)
				return (0);
			res = ft_split(env, ':');
			free (env);
			if (!res)
				return (0);
			return (res);
		}
		i++;
	}
	return (0);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	write(2, cmd, ft_strlen(cmd));
	print_err(" doesn't exits");
	return (0);
}

int	args_cmp(t_pipex *pipex, int argc, char **argv)
{
	if (argv[1] && !ft_strncmp("here_doc", argv[1], 9) && argc == 6)
	{
		pipex->heredoc = 1;
		return (1);
	}
	else
	{
		pipex->heredoc = 0;
		if (argc >= 5)
			return (1);
		else
			return (0);
	}
}
