/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:51:57 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 23:51:57 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_command(char **path, char *cmd)
{
    char *tmp;
    char *command;

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

void first_child(tube pipex, char **av)
{
	dup2(pipex.input, 0); // input of the command now is the input file
	close(pipex.fd[0]); // closing the read end since we are not using it
	dup2(pipex.fd[1], 1); // switching the output of the command in the write end
	pipex.cmd_args = ft_split(av[2], ' ');
	pipex.cmd = get_command(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		error(ERR_CMD);
		exit(127);
	}
	execve(pipex.cmd, pipex.cmd_args, NULL);
	free_childs(pipex);
	close(pipex.fd[1]); // closing the write end (only apply on this process)
	// even after closing the write end here it is still open by 
	// other processes if they inherit the pipe
}

void second_child(tube pipex, char **av)
{
	dup2(pipex.output, 1); // switching the st_out to the file
	close(pipex.fd[1]); // closing the write end since we are not using it
	dup2(pipex.fd[0], 0); // input of the command now is the read end of the pipe
	pipex.cmd_args = ft_split(av[3], ' ');
	pipex.cmd = get_command(pipex.paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
		error(ERR_CMD);	
	execve(pipex.cmd, pipex.cmd_args, NULL);
	close(pipex.fd[0]); // closing the read end of the pipe
	free_childs(pipex);
}