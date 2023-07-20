/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'fdf_utils.c'                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-07-18 15:43:36 by lbaron            :+:    #+#             */
/*   Updated: 2023-07-18 15:43:36 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
}

void	print_matrix(int **matrix, int *rw, int *cl)
{
	int	i;
	int	j;

	i = 0;
	while (i < *rw)
	{
		j = 0;
		while (j < *cl)
		{
			printf("%d ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	free_matrix(int **matrix, int *rw)
{
	int	i;

	i = 0;
	while (i < *rw)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
