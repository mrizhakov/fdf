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
char	*retrive_buf(const char *arg1)
{
	size_t	rd;
	int fd;
	char *buf;
	char *buf2;
	char	*path;

	buf = (char *) malloc(10000);
	path = "./maps/";
	path = ft_strjoin(path, arg1);
	fd = open(path, O_RDONLY);
	rd = read(fd, buf, 10000);
	buf2 = ft_strjoin(buf, "\0");
	free(path);
	free(buf);
	return (buf2);
}
// -----------------------------------------------------------------------------

int32_t	main(int32_t argc, const char* argv[])
{
	if(argc != 2)
	{
		write(2, "error: you need a valid map name\n", 33);
		return (0);
	}
	mlx_t* mlx;
	char *buf;
	buf = retrive_buf(argv[1]);
	printf("%s", buf);

	 Gotta error check this stuff
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
	free(buf);
	return (EXIT_SUCCESS);
}
