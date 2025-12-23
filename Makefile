CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./minilibx-linux
DEBUG_FLAGS = -g

NAME = cub3d

SRC = main.c \
      engine/engine.c \
      parse/parse.c \
      gnl/get_next_line_utils.c \
      gnl/get_next_line.c \
      parse/parse_utils.c \
      parse/map_parse.c \
      parse/read_file.c \
      engine/init_player.c \
      engine/player_rotate.c \
      engine/load_textures.c \
      engine/render_frame.c \
      parse/player_parse.c \
      parse/parse_utils2.c \
      parse/rgb_parse.c \
      frees.c \
      engine/move_vertical.c \
      engine/draw.c \
      engine/dda.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_LINUX_DIR = ./minilibx-linux
MLX_LINUX = $(MLX_LINUX_DIR)/libmlx.a
MLX_LINUX_FLAGS = -L$(MLX_LINUX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LINUX)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(OBJ) $(LIBFT) $(MLX_LINUX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LINUX):
	make -C $(MLX_LINUX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_LINUX_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
