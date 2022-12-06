/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 01:48:02 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/06 01:48:02 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	wait_and_continue(t_pipe *pipex, int *fd_in)
{
	waitpid(-1, NULL, 0);
	close(pipex->fd[1]);
	*fd_in = pipex->fd[0];
}

void	child(char **av, t_pipe *pipex, int fd_in, int it)
{
	dup2(fd_in, 0);
	if (it != pipex->cmd_count - 1)
		dup2(pipex->fd[1], 1);
	else
		dup2(pipex->outfile, 1);
	pipex->cmd_args = ft_split(av[it + 2], ' ');
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		free_child(pipex);
		p_error("Command not found");
	}
	execve(pipex->cmd, pipex->cmd_args, NULL);
	free_child(pipex);
}

void	initiliaze_stuff(t_pipe *pipex, int ac, char **env, char **av)
{
	pipex->infile = open(av[1], O_RDONLY);
	pipex->outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex->infile < 0 || pipex->outfile < 0)
		p_error("Failed to open files.");
	pipex->cmd_count = ac - 3;
	pipex->paths = ft_split(find_path(env), ':');
}

void	multi_pipes(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		fd_in;
	int		it;

	initiliaze_stuff(&pipex, ac, env, av);
	it = 0;
	fd_in = pipex.infile;
	while (it < pipex.cmd_count)
	{
		if (pipe(pipex.fd) < 0)
			p_error("Failed to create a pipe.");
		pipex.pid = fork();
		if (pipex.pid < 0)
			p_error("Failed to fork.");
		else if (pipex.pid == 0)
			child(av, &pipex, fd_in, it);
		else
		{
			wait_and_continue(&pipex, &fd_in);
			it++;
		}
	}
	free_parent(&pipex);
}
