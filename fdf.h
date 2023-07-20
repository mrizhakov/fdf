/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'fdf.h'                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-07-18 15:43:02 by lbaron            :+:    #+#             */
/*   Updated: 2023-07-18 15:43:02 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef struct s_main
{
	int32_t 		row;
	int32_t 		col;
	char			*buf;
	int				**matrix;
}t_main;

typedef struct s_data
{
	int		char_h_size;
	int		int_h_size;
	int		v_size;
	int		**map_ints;
	char	**map_chars;
}t_data;

typedef struct s_strm
{
	int		i;
	int		j;
	char	**split;
	char	**split2;
	int		**matrix;
}t_strm;

//fdf_utils.c

void	print_split(char **split);
void	print_matrix(int **matrix, int *rw, int *cl);
void	free_matrix(int **matrix, int *rw);
void	free_split(char **split);

//fdf_utils2.c

int		**str_to_matrix(char *buf, int *rw, int *cl);
char	*retrieve_buf(const char *arg1);

#endif //FDF_H
