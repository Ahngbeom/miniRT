# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeyu <jaeyu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 23:30:59 by jaeyu             #+#    #+#              #
#    Updated: 2022/03/31 15:03:57 by jaeyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

# src / obj files
SRC		=	main.c	\
			parse_file.c	\
			parse_scene.c	\
			parse_objects.c	\
			parse_color3.c	\
			split_utils.c	\
			

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# mlx library
MLX		= ./miniLibx/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./miniLibx
MLX_LNK	= -L ./miniLibx -lmlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -lft

# directories
SRCDIR	= ./src/
INCDIR	= ./include/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)
	@cp $(MLX)libmlx.dylib ./

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	rm -rf libmlx.dylib

re: fclean all

.PHONY: all clean fclean re
