NAME_SERVER = server
NAME_CLIENT = client

SRCS_CLIENT =  src/client.c
SRCS_SERVER =  src/server.c

OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
OBJS_SERVER = ${SRCS_SERVER:.c=.o}

CC = gcc
RM = rm -f

all = client server

client: ${OBJS_CLIENT}
	${CC} ${OBJS_CLIENT} -o ${NAME_CLIENT}

server: ${OBJS_SERVER}	
	${CC} ${OBJS_SERVER} -o ${NAME_SERVER}

clean:
			${RM} ${OBJS_CLIENT} ${OBJS_SERVER} ${OBJS_CLIENTBONUS} ${OBJS_SERVERBONUS}

fclean: clean
			${RM} ${NAME_CLIENT} ${NAME_SERVER} ${NAME_CLIENTB} ${NAME_SERVERB}

re: fclean all

.PHONY: all clean fclean bonus