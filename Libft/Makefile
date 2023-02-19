# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: event <event@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 19:21:22 by fl-hote           #+#    #+#              #
#    Updated: 2023/02/19 20:55:24 by event            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isspace.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c\
	  ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
	  ft_strchr.c ft_strdup.c ft_strndup.c ft_striteri.c ft_strcat.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
	  ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strtrim.c ft_itoa.c ft_split.c ft_strjoin.c ft_strmapi.c\
	  ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c\
	  ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_strcmp.c ft_putstr.c ft_nb_lines_tab.c\
	  ft_strlen_tab.c ft_strposchr.c ft_realloc.c get_next_line.c get_next_line_utils.c

OBJS = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

alln : all
		norminette
.c.o :
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
