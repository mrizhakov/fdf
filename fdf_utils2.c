/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'fdf_utils2.c'                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-07-18 15:55:07 by lbaron            :+:    #+#             */
/*   Updated: 2023-07-18 15:55:07 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	matrix_loop(t_strm *v, int *cl)
{
	v->split2 = ft_split(v->split[v->i], ' ');
	*cl = 0;
	while (v->split2[*cl])
		(*cl)++;
	v->matrix[v->i] = (int *)malloc(*cl * sizeof(int));
	v->j = 0;
	while (v->split2[v->j])
	{
		v->matrix[v->i][v->j] = ft_atoi(v->split2[v->j]);
		v->j++;
	}
	free_split(v->split2);
	v->i++;
}

int	**str_to_matrix(char *buf, int *rw, int *cl)
{
	t_strm	v;

	v.i = 0;
	v.split = ft_split(buf, '\n');
	while (buf[v.i])
	{
		if (buf[v.i] == '\n')
			*rw = *rw + 1;
		v.i++;
	}
	v.matrix = (int **)malloc((*rw) * sizeof(int *));
	v.i = 0;
	while (v.split[v.i])
	{
		matrix_loop(&v, cl);
	}
	free_split(v.split);
	return (v.matrix);
}

char	*retrieve_buf(const char *arg1)
{
	size_t	rd;
	int		fd;
	char	*buf;
	char	*path;

	buf = (char *)malloc(100000);
	path = "./maps/";
	path = ft_strjoin(path, arg1);
	fd = open(path, O_RDONLY);
	rd = read(fd, buf, 100000);
	if (rd == -1)
	{
		write(2, "error: invalid map\n", 20);
		exit(0);
	}
	buf[rd] = '\0';
	free(path);
	close(fd);
	return (buf);
}
