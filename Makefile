NAME = so_long

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

SRCS = main.c\
		gnl.c\
		creation_map.c\
		init.c\
		printer.c\
		plus.c

LIBS = -L./lib/libft -L./lib/ft_printf -lft -lftprintf libmlx.dylib

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) | libraries
		$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
		
libraries:
	cd ./lib/libft; make;
	cd ./lib/ft_printf; make;
	make -C ./lib/mlx
	cp ./lib/mlx/libmlx.dylib .

clean:
	rm -f $(NAME) $(OBJS)

fclean: clean
	make fclean -C ./lib/libft
	make fclean -C ./lib/ft_printf
	make clean -C ./lib/mlx
	rm -rf libmlx.dylib
	
re: fclean all
