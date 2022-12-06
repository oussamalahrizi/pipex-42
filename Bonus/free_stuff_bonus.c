/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 01:48:29 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/06 01:48:29 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipes(t_pipe *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

void	free_me(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_child(t_pipe *pipex)
{
	close_pipes(pipex);
	free_me(pipex->cmd_args);
	free(pipex->cmd);
}

void	free_parent(t_pipe *pipex)
{
	close_pipes(pipex);
	free_me(pipex->paths);
}
