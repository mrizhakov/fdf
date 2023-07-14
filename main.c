#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

typedef struct data {
	int h_size;
	int v_size;
	int** map;
} t_data;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	for (int32_t i = 0; i < image->width; ++i)
	{
		for (int32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

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

int measure_map_h_size(char *buf)
{
	int counter;

	counter = 0;
	while(*buf != '\0')
	{
		if (*buf == '\n')
			counter++;
		buf++;
	}
	return (counter + 1);
}

int measure_map_v_size(char *buf)
{
	int i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	return (*buf);
}

int	ft_word_count_first_line(char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str != '\n')
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

int **allocate_map(t_data data)
{
	int i;

	i = data.v_size;
	data.map = (int **)malloc(data.v_size * sizeof(int*));
//		if (!data.map)
//		{
//			free(data.map);
//			return ;
//		}
	while (i != data.v_size)
	{
		data.map[i] = (int *)malloc(data.h_size * sizeof(int));
//		if (!data.map[i])
//		{
//			free(data.map[i]);
//			return ;
//		}
		i++;
	}
	return (data.map);
}

//void free_int_arr(t_data data)
//{
//	datatype size = sizeof(data) / sizeof(array_name[index]);
//
//}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;
	size_t rd;
	char buf[5000];
	char *path ="./maps/";
	t_data data;
	path = ft_strjoin(path, argv[1]);
	int fd;
	fd = open(path, O_RDONLY);
	rd = read(fd, buf, 1000);
	printf("%s\n", buf);

	char *test_str = "1 2 5 6 \n 1 2 4 5 \n 2 4 6 7 \0";

	data.h_size = measure_map_h_size(test_str);
	data.v_size = ft_word_count_first_line(test_str,' ');
	data.map = allocate_map(data);
//
//	while
	printf("H_size is %d\n", data.h_size);
	printf("V_size is %d\n", data.v_size);

//	free_int_arr(data);









	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	//free(str);
	return (EXIT_SUCCESS);
}
