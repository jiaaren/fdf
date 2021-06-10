# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:52:02 by jkhong            #+#    #+#              #
#    Updated: 2021/06/10 13:43:15 by jkhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	cube3.c	ft_make_line.c	rotation.c projection.c	transformation.c read_file.c
OBJS	=	${SRCS:.c=.o}
NAME	=	fdf
CC		=	gcc
# CFLAGS	=	-Wall -Wextra -Werror 
CFLAGS	=

%.o: %.c
			$(CC) $(CFLAGS) -c -I/usr/include -Imlx_linux -O3 $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME): 	
			gcc srcs/*.c -Ilibft/includes -Iincludes -Imlx_linux -Llibft -lft -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
