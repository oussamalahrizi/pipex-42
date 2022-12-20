/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:26:59 by olahrizi          #+#    #+#             */
/*   Updated: 2022/12/10 00:26:59 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	p_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
