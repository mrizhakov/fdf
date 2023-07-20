


LIBMLX = MLX42/build/libmlx42.a
MLXFLAGS = -L/path/to/glfw/library -lglfw
CFLAGS = -Wall -Werror -Wextra -g3

GNL_DIR = ./get_next_line/
GNL = $(GNL_DIR)gnl.a

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a


all:name
	cc -g3 main.c fdf_utils.c fdf_utils2.c $(LIBFT) $(LIBMLX) $(GNL) $(MLXFLAGS)
	
name:
	make -C $(LIBFT_PATH) all
	
clean:
	make -C $(LIBFT_PATH) fclean
	rm a.out
