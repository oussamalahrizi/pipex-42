NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	Mandatory/children.c \
		Mandatory/errors.c \
		Mandatory/pipex_utils.c \
		Mandatory/pipex_utils2.c \
		Mandatory/pipex.c
BSRCS = 	Bonus/errors_bonus.c \
		Bonus/get_cmd.c \
		Bonus/get_next_line_utils.c \
		Bonus/get_next_line.c \
		Bonus/here_doc.c \
		Bonus/multi_pipes.c \
		Bonus/pipex_bonus.c \
		Bonus/pipex_utils_bonus.c \
		Bonus/pipex_utils_bonus_2.c

OBJS = ${SRCS:.c=.o}
BOBJS = ${BSRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
		${CC} ${CFLAGS} -I Mandatory/pipex.h ${OBJS} -o ${NAME}

%.o : %.c
		${CC} ${CFLAGS} -c $< -o $@

bonus:	${BOBJS}
		${CC} ${CFLAGS} -I Bonus/pipex_bonus.h ${BOBJS} -o ${NAME}

clean :
	rm -rf ${OBJS} ${BOBJS}

fclean: clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re bonus