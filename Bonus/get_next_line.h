/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:06:12 by olahrizi          #+#    #+#             */
/*   Updated: 2022/12/06 04:25:57 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

char	*join_strs(char *s1, char *s2);
char	*str_copy(char *dest, char *src);
size_t	ft_strlength(char *s);
char	*get_next_line(int fd);
char	*search(char *s, char c);
void	*reset_c(size_t nelem, size_t elsize);
#endif