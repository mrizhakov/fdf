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

typedef struct s_data {
	int char_h_size;
	int int_h_size;
	int v_size;
	int** map_ints;
	char** map_chars;
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

int ft_measure_map_v_size(char *buf)
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

//int measure_map_h_size(char *buf)
//{
//	int i;
//
//	i = 0;
//	while (buf[i] != '\n')
//		i++;
//	return (*buf);
//}

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

int	ft_word_count(char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
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

void	clean_ptrs(char **double_ptr)
{
	char	**tmp;

	tmp = double_ptr;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(double_ptr);
}



int **allocate_map_ints(t_data fdf)
{
	int i;
	int y;
	char **arr;

	i = 0;
	y = 0;

	fdf.map_ints = (int **)malloc(fdf.v_size * sizeof(int*));
//		if (!data.map)
//		{
//			free(data.map);
//			return ;
//		}

	while (i != fdf.v_size)
	{
		y = 0;
		arr = ft_split(fdf.map_chars[i], ' ');

		printf("Arr is %s\n", arr[0]);
		printf("Arr is %s\n", arr[1]);
		printf("Arr is %s\n", arr[2]);
		printf("Arr is %s\n", arr[3]);

		fdf.map_ints[i] = (int *)malloc(ft_word_count(fdf.map_chars[i], ' ') * sizeof(int));
		fdf.int_h_size = ft_word_count(fdf.map_chars[i], ' ');
		while (arr[y] != NULL)
		{
			fdf.map_ints[i][y] = ft_atoi(arr[y]);
			printf("fdf.map_ints[i][y] %d\n", fdf.map_ints[i][y]);
			y++;
		}
		clean_ptrs(arr);
		i++;
	}
	return (fdf.map_ints);
}

void ft_free_2d_int_arr(int **arr, int v)
{
	int i;

	i = 0;
//	size_t arr_len = arr[0] /sizeof(int)
	while (i < v)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	//return (NULL);
}

char **allocate_map_chars(char *str, t_data fdf)
{
	char **arr;
	int len;
	int start;
	int rows;
	arr = (char **) malloc((fdf.v_size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	start = 0;
	len = 0;
	rows = 0;
	while (rows != fdf.v_size + 1) // ||
	{
		while (str[len] != '\n')
		{
			len++;
		}
		arr[rows] = ft_substr(str, start, len - start);
		printf("String is %s\n", arr[rows]);
		printf("Start is %d\n", start);
		printf("Len is %d\n", len);
		printf("Rows is %d\n", rows);
		printf("FDF.v_size is %d\n", fdf.v_size);
		start = len + 1;
		rows++;
		len++;
	}
	arr[rows] = NULL;
	return (arr);
}

void	print_char2d_arr(char **double_ptr)
{
	int i = 0;

	while (double_ptr[i][0] != '\0')
	{
		printf("Line %d contains %s\n", i, double_ptr[i]);
		i++;
	}
}

void	print_int2d_arr(int **double_ptr, int rows, int columns)
{
//	int rows = 3;
//	int columns = 4;
	int rows_c = 0;
	int columns_c = 0;

	printf("2d int array contains\n");

	while (rows_c != rows)
	{
		columns_c = 0;
		while (columns_c != columns)
		{
			printf("%d ", double_ptr[rows_c][columns_c]);
			columns_c++;
		}
		printf("\n");

		rows_c++;
	}
}




//void free_int_arr(t_data data)
//{
//	datatype size = sizeof(data) / sizeof(array_name[index]);
//
//}

// -----------------------------------------------------------------------------

char	*retrieve_buf(const char *arg1)
{
	size_t	rd;
	int 	fd;
	char 	*buf;
	char 	*buf2;
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
	t_data fdf;
	buf = retrieve_buf(argv[1]);
	printf("%s", buf);

	char *test_str = "1 2 5 6\n7 8 9 10\n11 12 13 14";

	fdf.v_size = ft_measure_map_v_size(test_str);
	fdf.char_h_size = ft_word_count_first_line(test_str,' ');
	fdf.map_chars = allocate_map_chars(test_str, fdf);
	fdf.map_ints = allocate_map_ints(fdf);



	printf("H_size is %d\n", fdf.char_h_size);
	printf("V_size is %d\n", fdf.v_size);

	print_char2d_arr(fdf.map_chars);
	print_int2d_arr(fdf.map_ints, 3, 4);

//	print_int2d_arr(fdf.map_ints);



	clean_ptrs(fdf.map_chars);

//	= ft_parse_string_to_2d_char_arr(char *str);

	ft_free_2d_int_arr(fdf.map_ints, fdf.v_size);


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
	free(buf);
	return (EXIT_SUCCESS);
}
