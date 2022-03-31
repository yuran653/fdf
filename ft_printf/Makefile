# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/07 01:29:57 by jgoldste          #+#    #+#              #
#    Updated: 2022/03/31 17:39:36 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

SRCS	=	ft_chr_func.c	ft_parse_func.c		ft_printf.c\
			ft_printnbr_func.c	ft_put_func.c	ft_putnbr_func.c\
			ft_printhex_func.c

HEADER	=	ft_printf.h

OBJS	=	$(patsubst %.c,%.o,$(SRCS))

D_FILES	=	$(patsubst %.c,%.d,$(SRCS))

CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)

CC		=	gcc

RM					=	rm -rf

GREEN				=	"\033[1;32m"
YELLOW				=	"\033[1;33m"
END					=	"\033[0m"

.PHONY	:	all clean fclean re bonus

all		:	$(NAME)

$(NAME)	:	$(OBJS) $(HEADER)
			ar rcs $(NAME) $?
			@echo ${GREEN} "\n\tft_printf is compiled\n" ${END}

%.o		:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@ -MD

clean	:	
			@$(RM) $(OBJS) $(D_FILES)
			@echo ${YELLOW} "\n\tft_printf 'clean' status: DONE\n" ${END}

fclean	:	clean
			@$(RM) $(NAME)
			@echo ${YELLOW} "\n\tft_printf 'fclean' status: DONE\n" ${END}

re		:	fclean all

bonus	:	$(NAME)

list	:	
			ar -t $(NAME)
