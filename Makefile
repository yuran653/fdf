# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 16:35:06 by jgoldste          #+#    #+#              #
#    Updated: 2022/03/31 17:45:18 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

SRCS		=	fdf.c\
				$(GNL)get_next_line.c	$(GNL)get_next_line_utils.c

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
				$(CC) $(CFLAGS) $(INCLUDES) $(LIB) -o $(FT_PRINTF) -o $(NAME) $(OBJS)
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