##
## EPITECH PROJECT, 2018
## myARPspoof
## File description:
## Makefile
##

CC		=	gcc
INC		=	-Iinclude/
DTESTS		=	tests/
DSRC		=	src/

MAIN		=	$(DSRC)main.c

SRC		=	$(DSRC)socket.c			\
			$(DSRC)init_header.c	\
			$(DSRC)address.c		\
			$(DSRC)args.c			\
			$(DSRC)spoof.c			\
			$(DSRC)utilities.c      \

SRC_UT		=	$(DTESTS)socket_test.c		\
				$(DTESTS)arg_test.c			\
				$(DTESTS)mac_address_test.c \

CFLAGS		+=	-Wall -Wextra $(INC)
OBJ		=	$(SRC:.c=.o) $(MAIN:.c=.o)
NAME		=	myARPspoof
NAME_UT		=	units

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

tests_run: CFLAGS += --coverage -lgcov -lcriterion
tests_run:
	$(CC) -o $(NAME_UT) $(SRC) $(SRC_UT) $(CFLAGS) $(LDFLAGS) $(INC_UT)
	./$(NAME_UT)
	gcov *.gcno &> /dev/null

tests_debug: CXXFLAGS += -g
tests_debug: tests_run

tests_clean:
	rm -f $(NAME_UT) *.gcno *.gcov *.gcda

.PHONY: all clean fclean re debug tests_run tests_debug tests_clean
