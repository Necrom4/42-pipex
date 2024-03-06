/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:49:22 by dferreir          #+#    #+#             */
/*   Updated: 2023/02/24 11:39:25 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/pipex.h"

void	here_doc(t_pipex *pipex, char *arg)
{
	int		file;
	char	*str;

	file = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
		print_err("Error creating temporary heredoc file descriptor");
	while (1)
	{
		write(1, "heredoc> ", 9);
		str = get_next_line(0);
		str[ft_strlen(str) - 1] = '\0';
		if (!ft_strncmp(arg, str, ft_strlen(arg) + 1))
			break ;
		write(file, str, ft_strlen(str));
		write(file, "\n", 1);
		free(str);
	}
	free(str);
	close(file);
	pipex->fd1 = open(".heredoc", O_RDONLY);
	if (pipex->fd1 < 0)
	{
		unlink(".heredoc");
		print_err("Error reading from heredoc file descriptor");
	}
}
