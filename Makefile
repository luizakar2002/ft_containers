SRC			=	main

INC			=	utils

SRCS		= $(addsuffix .cpp, ${SRC})

INCS		= $(addsuffix .hpp, ${INC})

OBJS		= ${SRCS:.cpp=.o}

NAME		= containers

CC			= clang++
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -std=c++98

.cpp.o:
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

std:		fclean
			${CC} ${CFLAGS} -o ${NAME} ${SRCS} -D NAMESPACE=std

all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
