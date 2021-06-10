# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/03 16:52:02 by jkhong            #+#    #+#              #
#    Updated: 2021/06/10 19:07:04 by jkhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/*.c
OBJS	=	${SRCS:.c=.o}
NAME	=	fdf
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

%.o: %.c
			$(CC) $(CFLAGS) -c -I/usr/include -Imlx_linux -O3 $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME): 	
			gcc srcs/*.c -Wall -Wextra -Werror -Ilibft/includes -Iincludes -Imlx_linux -Llibft -lft -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
