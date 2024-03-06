/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:36:45 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/24 11:38:37 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	child_one(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd1, 0);
	dup2(pipex.tmp[1], 1);
	close(pipex.tmp[0]);
	pipex.cmd = get_cmd(pipex.path, ft_split(argv[2], ' ')[0]);
	execve(pipex.cmd, ft_split(argv[2], ' '), envp);
	print_err("Command not found");
}

void	child_two(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.tmp[0], 0);
	dup2(pipex.fd2, 1);
	close(pipex.tmp[1]);
	pipex.cmd = get_cmd(pipex.path, ft_split(argv[3], ' ')[0]);
	execve(pipex.cmd, ft_split(argv[3], ' '), envp);
	print_err("command not found");
}

void	pipy(t_pipex pipex, char **argv, char **envp)
{
	int		i;

	i = -1;
	pipex.path = get_path(envp);
	if (!pipex.path)
		print_err("Error accessing environment paths");
	if (pipe(pipex.tmp) < 0)
		print_err("Inexecutable pipe");
	pipex.pid = fork();
	if (pipex.pid < 0)
		print_err("Error forking process #1");
	if (!pipex.pid)
		child_one(pipex, argv, envp);
	pipex.pid = fork();
	if (pipex.pid < 0)
		print_err("Error forking process #2");
	if (!pipex.pid)
		child_two(pipex, argv, envp);
	close(pipex.tmp[0]);
	close(pipex.tmp[1]);
	waitpid(-1, 0, 0);
	while (pipex.path[++i])
		free(pipex.path[i]);
	free(pipex.path);
	free(pipex.tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.fd1 = open(argv[1], O_RDONLY);
		pipex.fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		pipex.tmp = malloc(2 * sizeof(int));
		if (pipex.fd1 < 0 || pipex.fd2 < 0 || pipex.tmp < 0)
			print_err("Error accessing file descriptors");
		pipy(pipex, argv, envp);
		if (close(pipex.fd1) < 0 || close(pipex.fd2) < 0)
			print_err("Error closing file descriptors");
	}
	else
		print_err("Incorrect number of arguments");
	return (0);
}
