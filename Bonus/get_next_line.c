/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olahrizi <olahrizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:06:00 by olahrizi          #+#    #+#             */
/*   Updated: 2022/12/12 22:13:16 by olahrizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_holder(char *holder)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (!holder[i])
	{
		free(holder);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen2(holder) - i + 1));
	if (!new)
		return (NULL);
	i++;
	j = 0;
	while (holder[i])
		new[j++] = holder[i++];
	new[j] = 0;
	free(holder);
	return (new);
}

char	*read_line(char *holder)
{
	char	*line;
	int		i;

	i = 0;
	if (!holder[i])
		return (NULL);
	while (holder[i] && holder[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
	{
		line[i] = holder[i];
		i++;
	}
	if (holder[i] == '\n')
	{
		line[i] = holder[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*join_holder(int fd, char *holder)
{
	char	*buff;
	int		readed;

	if (!holder)
		holder = reset_c(1, 1);
	readed = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!search(holder, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(buff);
			free(holder);
			return (NULL);
		}
		buff[readed] = 0;
		holder = join_strs(holder, buff);
		if (!holder)
			return (NULL);
	}
	free(buff);
	return (holder);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	holder = join_holder(fd, holder);
	if (!holder)
		return (NULL);
	line = read_line(holder);
	holder = update_holder(holder);
	return (line);
}
