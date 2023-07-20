/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <lbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 08:27:25 by lbaron            #+#    #+#             */
/*   Updated: 2023/01/19 14:22:03 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(const char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = (char *)malloc((sizeof(char)) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_remainder(char *remainder)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * (ft_strlen1(remainder) - i + 1));
	if (!buff)
		return (NULL);
	i++;
	j = 0;
	while (remainder[i])
		buff[j++] = remainder[i++];
	buff[j] = '\0';
	free(remainder);
	return (buff);
}

char	*get_buffer(char *remainder, int fd)
{
	char		*buff;
	size_t		size;
	size_t		exit;

	exit = -1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	size = 1;
	while (!ft_strchr1(remainder, '\n') && size != 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == exit)
		{
			free(buff);
			free(remainder);
			return (NULL);
		}
		buff[size] = '\0';
		remainder = ft_strjoin1(remainder, buff);
	}
    free(buff);
	return (remainder);
}	

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	remainder = get_buffer(remainder, fd);
	if (!remainder)
        return (NULL);
	line = get_new_line(remainder);
	remainder = get_remainder(remainder);
	return (line);
}

