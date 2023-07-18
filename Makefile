


LIBMLX = MLX42/build/libmlx42.a
MLXFLAGS = -L/usr/local/lib -lglfw
CFLAGS = -Wall -Werror -Wextra -g3

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a


all:name
	cc -g3 main.c $(LIBFT) $(LIBMLX) $(MLXFLAGS)
	
name:
	make -C $(LIBFT_PATH) all
	
clean:
	make -C $(LIBFT_PATH) fclean
	rm a.out
