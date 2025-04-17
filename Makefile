# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 01:58:51 by ssadi-ou          #+#    #+#              #
#    Updated: 2025/04/17 02:48:11 by ssadi-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =		main/main.c \
		utils/moves.c \
		src/so_long.c \
		utils/checks_map.c \
		utils/put_img_utils.c \
		utils/set_rectangle.c \
		utils/set_tab.c \
		utils/utils.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

NAME =		so_long


CFLAGS =	-Wall -Werror -Wextra -g3

CC =		cc

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft

MINI_LIBX_DIR = minilibx-linux

LIBFT_OBJ = $(LIBFT_DIR)/libft.a

MINI_LIBX_OBJ = $(MINI_LIBX_DIR)/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_OBJ) $(MINI_LIBX_OBJ)
		$(CC) $(CFLAGS) -o $@ $^ -Lminilibx-linux -lmlx_Linux -lX11 -lXext

%.o: %.c inc/so_long.h
		$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_OBJ):
		$(MAKE) -C $(LIBFT_DIR)

$(MINI_LIBX_OBJ):
		$(MAKE) -C $(MINI_LIBX_DIR)

clean:
		rm -f $(OBJ)
		$(MAKE) -C $(LIBFT_DIR) clean
		$(MAKE) -C $(MINI_LIBX_DIR) clean

fclean: clean
		rm -f $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean all re bonus
