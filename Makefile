##
## EPITECH PROJECT, 2018
## PSU_myftp_2018
## File description:
## Makefile
##

CC			=	gcc
INC			=	-Iinclude/
DTESTS		=	tests/
DSRC		=	src/
DUTILS		=	$(DSRC)utils/
DCOMMANDS	=	$(DSRC)commands/

MAIN		=	$(DSRC)main.c		\

SRC			=	$(DSRC)socket.c			\

SRC_UT		=	$(DTESTS)socket_test.c		\

CFLAGS		+=	-Wall -Wextra $(INC)
OBJ			=	$(SRC:.c=.o) $(MAIN:.c=.o)
NAME		=	myARPspoof

all: $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_UT)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug
