/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:21:08 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/06 02:21:08 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line.h"


static void	child(char **av, t_pipe *pipex, int fd_in, int it)
{
	dup2(fd_in, 0);
	if (it != pipex->cmd_count - 1)
		dup2(pipex->fd[1], 1);
	else
		dup2(pipex->outfile, 1);
	pipex->cmd_args = ft_split(av[it + 3], ' ');
	pipex->cmd = get_command(pipex->paths, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		free_child(pipex);
		p_error("Command not found");
	}
	execve(pipex->cmd, pipex->cmd_args, NULL);
	free_child(pipex);
}

static void	wait_and_continue(t_pipe *pipex, int *fd_in)
{
	waitpid(-1, NULL, 0);
	close(pipex->fd[1]);
	*fd_in = pipex->fd[0];
}

void	here_doc(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int	fd_in;
	char *line;
	int it;
	int file;

	//todo : print the limiter followed by >
	if (ac < 6)
		error("Invalid arguments for here_doc\n");
	file = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (file < 0)
		p_error("Failed to open a temp file.");
	pipex.cmd_count = ac - 4;
	pipex.paths = ft_split(find_path(env), ':');
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (line < 0)
			p_error("failed to get the line.");
		if (!ft_strncmp(line, av[2], ft_strlen(av[2])))
			break;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file);
	pipex.infile = open(".temp", O_RDONLY);
	pipex.outfile = open(av[ac - 1], O_CREAT | O_APPEND | O_RDWR, 0664);
	if (pipex.infile < 0 || pipex.outfile < 0)
	{
		unlink(".temp");
		p_error("failed to open the files");
	}
	it = 0;
	fd_in = pipex.infile;
	pipex.cmd_count = ac - 4;
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
	unlink(".temp");
}
