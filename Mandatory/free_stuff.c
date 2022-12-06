/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:04:47 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/02 02:04:47 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_main(tube pipex)
{
	int	i;

	i = 0;
	close(pipex.input);
	close(pipex.output);
	while (pipex.paths[i])
	{
		free(pipex.paths[i]);
		i++;
	}
	free(pipex.paths);
}

void free_childs(tube pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_args[i])
	{
		free(pipex.cmd_args[i]);
		i++;
	}
	free(pipex.cmd_args);
	free(pipex.cmd);
}

