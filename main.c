/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   'main.c'                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron  <lbaron@student.42berlin.de>       :+:  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-07-18 15:24:19 by lbaron            :+:    #+#             */
/*   Updated: 2023-07-18 15:24:19 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 512
#define HEIGHT 512

static	mlx_image_t	*image;

// -----------------------------------------------------------------------------

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_put_pixel(int32_t x, int32_t y, long color)
{
	mlx_put_pixel(image, x, y, color);
}


// works by putting either vertical or horizontal lines only. Commented part of the code only prints out the diagonal line.
// Have to use https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm to print out lines in any angle
void	ft_put_line(int32_t x, int32_t y, int32_t x_end, int32_t y_end, long color)
{
	while (y <= y_end && x <= x_end)
	{
		ft_put_pixel(x, y, color);
//		x++;
//		y++;

		if (y == y_end && x <= x_end)
		{
			x++;
		}
		if (x == x_end && y <= y_end)
		{
			y++;
		}
//		else if (x <= x_end && y <= y_end)
//		{
//			x++;
//			y++;
//		}


	}
}
void	ft_put_2d_matrix(long color, void *param)
{
//	int32_t x = 0;
//	int32_t y = 0;
//	int32_t x_end = 256;
//	int32_t y_end = 256;
	t_main *v = (t_main *)param;
//	long color = 0xFF00FFFF;
	int32_t offset = 20;
	int32_t row_start = 0;
	int32_t col_start = 0;

//	ft_put_line(row_start * offset, col_start * offset, v->row * offset, v->col * offset, color);

	ft_put_line(0, 0, 0, 100, color);


//	while (row_start <= v->row )
//	{
//		ft_put_line(row_start * offset, col_start * offset, v->row * offset, v->col * offset, color);
//		row_start++;
//	}
//	while (row_start <= v->row)
//	{
//		ft_put_line(col_start * offset, row_start <= v->row, row_start * offset,v->row * offset, color);
//		row_start++;
//	}


//	ft_put_line(row_start * offset, col_start * offset, v->row * offset, v->col * offset, color);


//	while (row_start <= v->row && col_start <= v->col)
//	{
////		ft_put_pixel(row_start * offset, col_start * offset, color);
//		ft_put_line(row_start * offset, col_start * offset, v->row, v->col, color);
//
//		row_start++;
//		col_start++;
//	}
//	ft_put_line(x, y, x_end, y_end, color);
}

void	ft_randomize(void *param)
{
	int32_t x = 0;
	int32_t y = 0;
	t_main *v = param;


	int32_t x_end = 256;
	int32_t y_end = 256;
	long color = 0xFF00FFFF;
	//ft_put_pixel(x, y, color);
//	ft_put_line(x, y, x_end, y_end, color);
	ft_put_2d_matrix(color, param);

//	mlx_put_pixel(image, x, y, 0xFF00FFFF);
//
//	for (int32_t i = 0; i < 1; ++i)
//	{
//		for (int32_t y = 0; y < 1; ++y)
//		{
//			mlx_put_pixel(image, i, y, 0xFF00FFFF);
//		}
//	}
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

//test

int32_t	init_mlx(mlx_t **mlx, t_main *v)
{
	if (!(*mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(*mlx, 512, 512)))
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(*mlx, image, 0, 0) == -1)
	{
		mlx_close_window(*mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(*mlx, ft_randomize, v);
	mlx_loop_hook(*mlx, ft_hook, *mlx);
	return (EXIT_SUCCESS);
}

int32_t	main(int32_t argc, const char *argv[])
{
	mlx_t	*mlx;
	t_main	v;

	if (argc != 2)
	{
		write(2, "error: you need a valid map name\n", 33);
		return (0);
	}
	v.row = 0;
	v.col = 0;
	v.buf = retrieve_buf(argv[1]);
	v.matrix = str_to_matrix(v.buf, &v.row, &v.col);
	//print_matrix(v.matrix, &v.row, &v.col);
	if (init_mlx(&mlx, &v) != EXIT_SUCCESS)
	{
		return (EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_matrix(v.matrix, &v.row);
	free(v.buf);
	return (EXIT_SUCCESS);
}
