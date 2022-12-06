/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarizi <olahrizi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:34:33 by olarizi           #+#    #+#             */
/*   Updated: 2022/12/01 23:34:33 by olarizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*result;
	size_t	i;

	if (nelem && elsize > __SIZE_MAX__ / nelem)
		return (0);
	result = malloc(nelem * elsize);
	if (!result)
		return (0);
	i = 0;
	while (i < nelem * elsize)
	{
		*((unsigned char *)(result + i)) = 0;
		i++;
	}
	return (result);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (0);
	if (start >= (unsigned int) ft_strlen(s))
		return (ft_calloc(1, 1));
	while (s[start + i] && i < len)
		i++;
	sub = (char *) malloc((i + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	size_t		i;

	if (!src && !dest)
		return (dest);
	i = 0;
	while (i < n)
	{
		*((char *)(dest + i)) = *((char *)(src + i));
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	char	*start;
	size_t	total_len;

	if (!s1 || !s2)
		return (0);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *) malloc(sizeof(char) * (total_len + 1));
	if (!join)
		return (NULL);
	start = join;
	ft_memcpy(join, s1, ft_strlen(s1));
	join += ft_strlen(s1);
	ft_memcpy(join, s2, ft_strlen(s2));
	join += ft_strlen(s2);
	*join = 0;
	return (start);
}
