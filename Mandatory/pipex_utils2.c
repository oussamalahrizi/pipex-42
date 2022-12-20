/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:25:31 by olahrizi          #+#    #+#             */
/*   Updated: 2022/12/10 00:26:16 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	get_total_words(const char *str, char c)
{
	size_t	_string_count;

	_string_count = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			_string_count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (_string_count);
}

char	**free_stuff(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		strings[i] = NULL;
		i++;
	}
	free(strings);
	strings = NULL;
	return (strings);
}

size_t	get_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char *s, char c)
{
	char	**strings;
	size_t	index;

	if (!s)
		return (NULL);
	strings = (char **) malloc(sizeof(char *) * (get_total_words(s, c) + 1));
	if (!strings)
		return (NULL);
	index = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			strings[index++] = ft_substr(s, 0, get_len(s, c));
			if (!strings[index - 1])
				return (free_stuff(strings));
			s += get_len(s, c);
		}
	}
	strings[index] = 0;
	return (strings);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
