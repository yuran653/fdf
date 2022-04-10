# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 16:35:06 by jgoldste          #+#    #+#              #
#    Updated: 2022/04/10 20:04:15 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

SRCS		=	fdf.c			validation.c		get_map.c\
				check_utils.c	free_func.c\
				draw_map.c\
				error_free.c	error_exit.c		win_exit.c\
				$(GNL)get_next_line.c	$(GNL)get_next_line_utils.c
#				key_hook.c		bresenham.c\

HEADER		=	fdf.h

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

D_FILES		=	$(patsubst %.c,%.d,$(SRCS))

INCLUDES	=	-I.

CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc

RM			=	rm -rf

LIB			=	./libft/libft.a

GNL			=	./get_next_line/

FT_PRINTF	=	./ft_printf/libftprintf.a

MLX			=	-lmlx -framework OpenGL -framework AppKit

YELLOW		=	"\033[1;33m"
GREEN		=	"\033[1;32m"
END			=	"\033[0m"

.PHONY		:	all bonus libft ft_printf clean fclean re rebonus

all			:	libft ft_printf $(NAME)

bonus		:	libft ft_printf $(NAME_B)

libft		:	
				$(MAKE) -C $(dir $(LIB))

ft_printf	:
				$(MAKE) -C $(dir $(FT_PRINTF))

%.o			:	%.c $(HEADER)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MD

$(NAME)		:	$(OBJS) $(LIB) $(FT_PRINTF)
				$(CC) $(CFLAGS) $(INCLUDES) $(LIB) $(FT_PRINTF) -o $(NAME) $(OBJS) $(MLX)
				@echo ${GREEN} "\n\tFDF is compiled\n" ${END}

clean		:	
				@$(RM) $(OBJS) $(OBJS_B) $(D_FILES) $(D_FILES_B)
				@$(MAKE) -C $(dir $(LIB)) clean
				@$(MAKE) -C $(dir $(FT_PRINTF)) clean
				@echo ${YELLOW} "\n\tFDF 'clean' status: DONE\n" ${END}
				
fclean		:	clean
				@$(RM) $(NAME) $(NAME_B)
				@$(MAKE) -C $(dir $(LIB)) fclean
				@$(MAKE) -C $(dir $(FT_PRINTF)) fclean
				@echo ${YELLOW} "\n\tFDF 'fclean' status: DONE\n" ${END}

re			:	fclean all

rebonus		:	fclean bonus
