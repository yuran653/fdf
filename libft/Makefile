# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 02:40:24 by jgoldste          #+#    #+#              #
#    Updated: 2022/01/26 19:38:16 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	libft.a

override SRCS		=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c\
						ft_isascii.c	ft_isprint.c	ft_strlen.c\
						ft_memset.c		ft_bzero.c		ft_memcpy.c\
						ft_memmove.c	ft_strlcpy.c	ft_strlcat.c\
						ft_toupper.c	ft_tolower.c	ft_strchr.c\
						ft_strrchr.c	ft_strncmp.c	ft_memchr.c\
						ft_memcmp.c		ft_strnstr.c	ft_atoi.c\
						ft_calloc.c		ft_strdup.c		ft_substr.c\
						ft_strjoin.c	ft_strtrim.c	ft_split.c\
						ft_itoa.c		ft_strmapi.c	ft_striteri.c\
						ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c\
						ft_putnbr_fd.c

override HEADER		=	libft.h

OBJS				=	$(patsubst %.c,%.o,$(SRCS))

D_FILES				=	$(patsubst %.c,%.d,$(SRCS))

INCLUDES			=	-I.

CFLAGS				=	-Wall -Wextra -Werror

CC					=	gcc

RM					=	rm -rf

GREEN				=	"\033[1;32m"
YELLOW				=	"\033[1;33m"
END					=	"\033[0m"

.PHONY		:	all clean fclean re list

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				ar rcs $(NAME) $?
				@echo ${GREEN} "\n\tLibft is compiled\n" ${END}

%.o			:	%.c $(HEADER)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MD

clean		:	
				@$(RM) $(OBJS) $(D_FILES)
				@echo ${YELLOW} "\n\tLibft 'clean' status: DONE\n" ${END}
						
fclean		:	clean
				@$(RM) $(NAME)
				@echo ${YELLOW} "\n\tLibft 'fclean' status: DONE\n" ${END}

re			:	fclean all

list		:	
				ar -t $(NAME)