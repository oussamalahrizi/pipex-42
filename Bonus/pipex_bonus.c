/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 02:09:48 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/06 02:09:48 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	if (ac < 5)
		error("Invalid arguments.\n");
	if (!ft_strncmp("here_doc", av[1], ft_strlen("here_doc")))
		here_doc(ac, av, env);
	else
		multi_pipes(ac, av, env);
	return (EXIT_SUCCESS);
}
