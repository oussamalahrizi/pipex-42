/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/12/01 23:51:57 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 23:51:57 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command(char **path, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(command, F_OK))
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

void	first_child(t_tube pipex, char **av)
{
	dup2(pipex.input, 0);
	close(pipex.fd[0]);
	dup2(pipex.fd[1], 1);
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = get_command(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, NULL);
}

void	second_child(t_tube *pipex, char **av)
{
	dup2(pipex->output, 1);
	close(pipex->fd[1]);
	dup2(pipex->fd[0], 0);
	pipex->cmd_args = ft_split(av[3], ' ');
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
		exit(1);
	}
	execve(pipex->cmd, pipex->cmd_args, NULL);
}
