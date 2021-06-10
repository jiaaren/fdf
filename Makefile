# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:52:02 by jkhong            #+#    #+#              #
#    Updated: 2021/06/10 19:28:27 by jkhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/fdf_main.c			srcs/initialise.c	srcs/make_grid_utils.c		srcs/make_grid.c 	\
			srcs/make_line_utils.c	srcs/make_line.c	srcs/print_and_process.c	srcs/projection.c	\
			srcs/rotation.c			srcs/transformation.c
OBJS	=	${SRCS:.c=.o}
NAME	=	fdf
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HPATH	=	-Imlx_linux -Iincludes -Ilibft/includes -I/usr/include
LIBPATH =	-Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -Llibft -lft 

%.o: %.c
			$(CC) $(CFLAGS) -c $(LIBPATH) $(HPATH)  -O3 $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) $(HPATH) -o $(NAME) $(OBJS) $(LIBPATH) 
clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
