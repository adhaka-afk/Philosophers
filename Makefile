# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adhaka <adhaka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 09:45:56 by adhaka            #+#    #+#              #
#    Updated: 2023/10/29 22:32:01 by adhaka           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 			= philo

CC				= cc

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

SRCS			=	philo.c \
					check_argcvs.c \
					fork_and_philo.c \
					routine.c \
					utils.c \

OBJS			= $(SRCS:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS):		philo.h

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
