# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/24 14:43:05 by gkoechli          #+#    #+#              #
#    Updated: 2022/02/10 18:58:23 by gkoechli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c\
	init.c\
	utils.c\
	routine.c\
	ft_itoa.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

INCLUDES = -pthread

${NAME}: ${OBJS}
	gcc ${FLAGS} ${INCLUDES} ${SRCS} -o ${NAME}
.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}
all: ${NAME}
clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
re: fclean all

.PHONY: all clean fclean re
