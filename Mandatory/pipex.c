/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2022/12/01 20:15:06 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 20:15:06 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **env)
{
	while (*env)
	{
		if (!ft_strncmp("PATH", *env, 4))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

void	initialize(t_tube *pipex, char **env, char **av)
{
	pipex->paths = ft_split(find_path(env), ':');
	if (!pipex->paths)
		error(ERR_PATH);
	pipex->input = open(av[1], O_RDONLY);
	pipex->output = open(av[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->input < 0 || pipex->output < 0)
		p_error(ERR_FILES);
	if (pipe(pipex->fd) < 0)
		p_error(ERR_PIPE);
}

void	check_failure(int pid)
{
	if (pid < 0)
		p_error(ERR_FORK);
}

int	main(int ac, char **av, char **env)
{
	t_tube	pipex;

	if (ac != 5)
		error(INVALID_ARGS);
	initialize(&pipex, env, av);
	pipex.pid1 = fork();
	check_failure(pipex.pid1);
	if (pipex.pid1 == 0)
		first_child(pipex, av);
	else
	{
		pipex.pid2 = fork();
		check_failure(pipex.pid2);
		if (pipex.pid2 == 0)
			second_child(&pipex, av);
		else
		{
			waitpid(pipex.pid1, NULL, 0);
			waitpid(pipex.pid2, NULL, 0);
		}
	}
	return (EXIT_SUCCESS);
}
