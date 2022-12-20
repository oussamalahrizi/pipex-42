/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/12/06 02:21:08 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/06 02:21:08 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex_bonus.h"

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
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
		exit(1);
	}
	execve(pipex->cmd, pipex->cmd_args, NULL);
	close(fd_in);
	close(pipex->fd[1]);
}

static void	wait_and_continue(t_pipe *pipex, int *fd_in)
{
	waitpid(pipex->pid, NULL, 0);
	close(pipex->fd[1]);
	*fd_in = pipex->fd[0];
}

void	get_ready(int ac, char **av, char **env, t_pipe *pipex)
{
	pipex->cmd_count = ac - 4;
	pipex->paths = ft_split(find_path(env), ':');
	pipex->infile = open(".temp", O_RDONLY);
	pipex->outfile = open(av[ac - 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (pipex->infile < 0 || pipex->outfile < 0)
	{
		unlink(".temp");
		p_error(ERR_FILES);
	}
}

static void	initialize_stuff(int ac, char **av, char **env, t_pipe *pipex)
{
	char	*line;

	pipex->infile = open(".temp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex->infile < 0)
		p_error(ERR_TEMP);
	while (1)
	{
		write(1, "heredoc>", 8);
		line = get_next_line(0);
		if (!line)
			p_error(ERR_LINE);
		if (!ft_strncmp(line, av[2], ft_strlen(av[2])))
			break ;
		write(pipex->infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(pipex->infile);
	get_ready(ac, av, env, pipex);
}

void	here_doc(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		fd_in;
	int		it;

	if (ac < 6)
		error(INVALID_ARGS_HERE_DOC);
	initialize_stuff(ac, av, env, &pipex);
	fd_in = pipex.infile;
	it = 0;
	while (it < pipex.cmd_count)
	{
		if (pipe(pipex.fd) < 0)
			p_error(ERR_PIPE);
		pipex.pid = fork();
		if (pipex.pid < 0)
			p_error(ERR_FORK);
		else if (pipex.pid == 0)
			child(av, &pipex, fd_in, it);
		else
		{
			wait_and_continue(&pipex, &fd_in);
			it++;
		}
	}
	unlink(".temp");
}
