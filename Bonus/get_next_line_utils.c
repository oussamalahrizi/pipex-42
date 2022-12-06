/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:06:25 by olahrizi          #+#    #+#             */
/*   Updated: 2022/12/06 04:27:01 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_strs(char *s1, char *s2)
{
	char	*join;
	char	*start;

	join = (char *)malloc(sizeof(char) * (ft_strlength(s1) + ft_strlength(s2) + 1));
	if (!join)
		return (NULL);
	start = join;
	join = str_copy(join, s1);
	join += ft_strlength(s1);
	join = str_copy(join, s2);
	join += ft_strlength(s2);
	*join = 0;
	free(s1);
	return (start);
}

char	*str_copy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlength(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*search(char *s, char c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

void	*reset_c(size_t nelem, size_t elsize)
{
	void	*result;
	size_t	i;
	size_t	n;

	if (nelem && elsize > __SIZE_MAX__ / nelem)
		return (0);
	result = malloc(nelem * elsize);
	if (!result)
		return (0);
	i = 0;
	n = nelem * elsize;
	while (i < n)
	{
		*((unsigned char *)result + i) = 0;
		i++;
	}
	return (result);
}
