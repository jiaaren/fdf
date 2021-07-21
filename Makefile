# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:52:02 by jkhong            #+#    #+#              #
#    Updated: 2021/07/21 16:12:29 by jkhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/fdf_main.c			srcs/initialise.c	srcs/make_grid_utils.c		srcs/make_grid.c 	\
			srcs/make_line_utils.c	srcs/make_line.c	srcs/print_and_process.c	srcs/projection.c	\
			srcs/rotation.c			srcs/transformation.c
OBJS	=	${SRCS:.c=.o}
NAME	=	fdf
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HPATH	=	-I ./mlx_linux -I ./includes -I ./libft/includes -I /usr/include
LIBPATH =	-L ./mlx_linux -l mlx  -L ./libft -l ft -L /usr/lib -lXext -lX11 -lm -lz

%.o: %.c
			$(CC) $(CFLAGS) -c $(HPATH) $< -o ${<:.c=.o}

all:		$(NAME)

bonus:		$(NAME)

libft:
			make -C ./libft

clean_libft:
			make clean -C ./libft

mlx:
			make -C ./mlx_linux

clean_mlx:
			make clean -C ./mlx_linux

$(NAME): 	libft mlx $(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBPATH) 

clean:		clean_libft clean_mlx
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME) ./libft/*.a ./mlx_linux/*.a

re:			fclean all

.PHONY:		all clean fclean re bonus libft clean_libft mlx clean_mlx
