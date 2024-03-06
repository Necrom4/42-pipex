/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:36:45 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/24 11:21:08 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	open_files(t_pipex *pipex, int argc, char **argv)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(pipex, argv[2]);
	else
		pipex->fd1 = open(argv[1], O_RDONLY);
	if (pipex->heredoc)
		pipex->fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pipex->tmp = malloc(pipex->nb_pipes * sizeof(int));
	if (pipex->fd1 < 0 || pipex->fd2 < 0 || pipex->tmp < 0)
		print_err("Error accessing file descriptors");
}

void	close_free(t_pipex pipex)
{
	int	i;

	i = -1;
	while (pipex.nb_pipes > 0)
		close(pipex.tmp[pipex.nb_pipes--]);
	while (pipex.path[++i])
		free(pipex.path[i]);
	free(pipex.path);
	free(pipex.tmp);
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_args - 1)
	{
		if (pipe(pipex->tmp + 2 * i) < 0)
			printf("heyo");
		i++;
	}
}

void	pipy(t_pipex pipex, char **argv, char **envp)
{
	int	i;

	while (++pipex.idx < pipex.nb_args)
	{
		i = -1;
		pipex.pid = fork();
		if (!pipex.pid)
		{
			if (!pipex.idx)
				multi_dup2(pipex.fd1, pipex.tmp[1]);
			else if (pipex.idx == pipex.nb_args - 1)
				multi_dup2(pipex.tmp[2 * pipex.idx - 2], pipex.fd2);
			else
				multi_dup2(pipex.tmp[2 * pipex.idx - 2],
					pipex.tmp[2 * pipex.idx + 1]);
			while (++i < pipex.nb_pipes)
				close(pipex.tmp[i]);
			pipex.cmd = get_cmd(pipex.path,
					ft_split(argv[2 + pipex.idx + pipex.heredoc], ' ')[0]);
			if (!pipex.cmd)
				exit(1);
			execve(pipex.cmd,
				ft_split(argv[2 + pipex.idx + pipex.heredoc], ' '), envp);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (args_cmp(&pipex, argc, argv))
	{
		pipex.nb_args = argc - 3 - pipex.heredoc;
		pipex.nb_pipes = 2 * (pipex.nb_args - 1);
		open_files(&pipex, argc, argv);
		create_pipes(&pipex);
		pipex.path = get_path(envp);
		if (!pipex.path)
			print_err("Error accessing environment paths");
		pipex.idx = -1;
		pipy(pipex, argv, envp);
		close_free(pipex);
		waitpid(-1, 0, 0);
	}
	else
		print_err("Incorrect number of arguments");
	return (0);
}
