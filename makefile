NAME = cub3D

CC = cc
CFLAGS 	= -Wall -Wextra -Werror -Wno-unused-function -g3
LIBFT = -Lturbo_libft -Iturbo_libft/include -lft

GLFW = -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -ldl -pthread -lm
MLX = -IMLX42/include/ -LMLX42/build/ -lmlx42 $(GLFW)

OBJDIR= .objs

SRCS = srcs/main.c srcs/parsing/verif.c srcs/parsing/get_data.c srcs/parsing/map.c srcs/parsing/flood_fill.c \
srcs/raycasting/init_raycasting.c srcs/utils/utils_parsing.c srcs/parsing/player_utils.c srcs/utils/utils.c srcs/utils/free.c \
srcs/raycasting/draw_wall.c srcs/raycasting/input.c srcs/raycasting/utils.c

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

INCLUDE = -I./include

all : $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

${NAME}: ${OBJS}
	@make -s -C ./turbo_libft
	@$(CC) ${OBJS} $(LIBFT) $(MLX) -o ${NAME} ${CFLAGS}
	@echo "\033[32mcub3D compiled\033[0m"

clean:
	@rm -rf turbo_libft/.objs
	@rm -rf $(OBJDIR)
	@echo "\033[31mclean cub3D\033[0m"

fclean: clean
	@make -s fclean -C ./turbo_libft
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
