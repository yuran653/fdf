# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 16:35:06 by jgoldste          #+#    #+#              #
#    Updated: 2023/08/07 13:14:59 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	fdf

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -g
LIBRARIES 		=	-lmlx -lm -lft -framework OpenGL -framework AppKit -L$(LIBFT_DIR) -L$(MINILIBX_DIR) 
INCLUDES		=	-I$(HEADERS_DIR) -I$(LIBFT_HEADER) -I$(MINILIBX_HEADER)

LIBFT_DIR		=	./libft/
LIBFT			=	$(LIBFT_DIR)libft.a
LIBFT_HEADER	=	$(LIBFT_DIR)

MINILIBX_DIR	=	./minilibx_macos/
MINILIBX		=	$(MINILIBX_DIR)libmlx.a
MINILIBX_HEADER	=	$(MINILIBX_DIR)
MINILIBX_SILENCE	=	-framework OpenGL -framework Cocoa -Wno-deprecated-declarations

HEADERS_DIR		=	./include/
HEADERS_LIST	=	fdf.h
HEADERS			=	$(addprefix $(HEADER_DIR), $(HEADER_LIST))

GNL_DIR			=	gnl/

SOURCES_DIR		=	./src/
SOURCES_LIST	=	fdf.c			validation.c		get_map.c\
					draw_map.c		rotate.c			gradient.c\
					utils.c			utils_fdf.c			key_hook.c\
					free_func.c		error_free.c		error_exit.c\
					$(GNL_DIR)get_next_line.c			$(GNL_DIR)get_next_line_utils.c
SOURCES			=	$(addprefix $(SOURCES_DIR), $(SOURCES_LIST))

OBJECTS_DIR		=	./object/
OBJECTS_LIST	=	$(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS			=	$(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

MKDIR			=	mkdir -p

YELLOW			=	"\033[1;33m"
GREEN			=	"\033[1;32m"
END				=	"\033[0m"

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME) $(MINILIBX_SILENCE)
	@echo $(GREEN) "\n\tProject is compiled\n" ${END}

$(OBJECTS_DIR):
	$(MKDIR) $(OBJECTS_DIR)
	$(MKDIR) $(OBJECTS_DIR)$(GNL_DIR)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -g -c -o $@ $< -MD

$(LIBFT):
	$(MAKE) -sC $(LIBFT_DIR)

$(MINILIBX):
	@$(MAKE) -sC $(MINILIBX_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@$(MAKE) -sC $(MINILIBX_DIR) clean
	@rm -rf $(OBJECTS_DIR)
	@echo $(YELLOW) "\n\tProject 'clean' status: DONE\n" ${END}


fclean: clean
	@rm -rf $(MINILIBX)
	@rm -rf $(LIBFT)
	@rm -rf $(NAME)
	@echo $(YELLOW) "\n\tProject 'fclean' status: DONE\n" ${END}

re: fclean all

.PHONY: all clean fclean re


# NAME		=	fdf

# SRCS		=	fdf.c			validation.c		get_map.c\
# 				draw_map.c		rotate.c			gradient.c\
# 				utils.c			utils_fdf.c			key_hook.c\
# 				free_func.c		error_free.c		error_exit.c\
# 				$(GNL)get_next_line.c	$(GNL)get_next_line_utils.c

# HEADER		=	fdf.h

# OBJS		=	$(patsubst %.c,%.o,$(SRCS))

# D_FILES		=	$(patsubst %.c,%.d,$(SRCS))

# INCLUDES	=	-I.

# CFLAGS		=	-Wall -Wextra -Werror -g

# CC			=	gcc

# RM			=	rm -rf

# LIB			=	./libft/libft.a

# GNL			=	./get_next_line/

# FT_PRINTF	=	./ft_printf/libftprintf.a

# MLX			=	-lmlx -framework OpenGL -framework AppKit

# YELLOW		=	"\033[1;33m"
# GREEN		=	"\033[1;32m"
# END			=	"\033[0m"

# .PHONY		:	all bonus libft ft_printf clean fclean re rebonus

# all			:	libft ft_printf $(NAME)

# bonus		:	libft ft_printf $(NAME)

# libft		:	
# 				$(MAKE) -C $(dir $(LIB))

# ft_printf	:
# 				$(MAKE) -C $(dir $(FT_PRINTF))

# %.o			:	%.c $(HEADER)
# 				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MD

# $(NAME)		:	$(OBJS) $(LIB) $(FT_PRINTF)
# 				$(CC) $(CFLAGS) $(INCLUDES) $(LIB) $(FT_PRINTF) -o $(NAME) $(OBJS) $(MLX)
# 				@echo ${GREEN} "\n\tFDF is compiled\n" ${END}

# clean		:	
# 				@$(RM) $(OBJS) $(OBJS_B) $(D_FILES) $(D_FILES_B)
# 				@$(MAKE) -C $(dir $(LIB)) clean
# 				@$(MAKE) -C $(dir $(FT_PRINTF)) clean
# 				@echo ${YELLOW} "\n\tFDF 'clean' status: DONE\n" ${END}
				
# fclean		:	clean
# 				@$(RM) $(NAME) $(NAME_B)
# 				@$(MAKE) -C $(dir $(LIB)) fclean
# 				@$(MAKE) -C $(dir $(FT_PRINTF)) fclean
# 				@echo ${YELLOW} "\n\tFDF 'fclean' status: DONE\n" ${END}

# re			:	fclean all

# rebonus		:	fclean bonus
