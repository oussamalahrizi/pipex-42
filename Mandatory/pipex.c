/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:15:06 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 20:15:06 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int main(int ac, char **av, char **env)
{
    tube	pipex;

    if (ac != 5)
		error(INVALID_ARGS);
    pipex.paths = ft_split(find_path(env), ':');
    pipex.input = open(av[1], O_RDONLY);
	if (pipex.input < 0)
		p_error(ERR_INPUT);
    pipex.output = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0777);
    if (pipex.output < 0)
		p_error(ERR_OUTPUT);
	if (pipe(pipex.fd) < 0)
        p_error(ERR_PIPE);
	pipex.pid1 = fork();
    if (pipex.pid1 == 0)
    	first_child(pipex, av);
    else /* forking second child */
    {
        pipex.pid2 = fork();
        if (pipex.pid2 == 0)
            second_child(pipex, av);
        else /* parent process */
        {
		close(pipex.fd[0]);
		close(pipex.fd[1]);
		waitpid(pipex.pid1, NULL, 0);
		waitpid(pipex.pid2, NULL, 0);
		free_main(pipex);
        }
    }
    return 0;
}
