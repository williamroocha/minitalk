SOURCEFILES	= 	ft_printf.c ft_putchar.c ft_unsgint.c\
				ft_putstr.c ft_puthexa.c ft_putnbr.c ft_putadd.c

OBJECTS	= $(SOURCEFILES:.c=.o)

NAME	= libftprintf.a

COMPILER		= cc

RM		= rm -f
FLAGS	= -Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

all: $(NAME) 

${NAME} : ${OBJECTS}
	ar -rcs $(NAME) $(OBJECTS)


%.o : %.c
	${COMPILER} ${FLAGS} -c $< -o $@

clean:
	${RM} ${OBJECTS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

teste: re 
	${COMPILER} ${FLAGS} main.c -L. -lftprintf