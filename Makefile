##
## EPITECH PROJECT, 2018
## {PUT HERE YOUR PROJECT NAME}
## File description:
## Makefile a3.1
##

CC			=	g++

CFLAG		=	-Wall							\
				-Wextra

VGFLAG		=	--track-origins=yes				\
				--leak-check=full

SRCPATH		=	./source

MAIN		=	$(SRCPATH)/main.cpp

SRC			=

SRCOBJ		=	$(SRC:.c=.o)

TESTPATH	=	./tests

TEST		=

TESTOBJ		=	$(TEST:.c=.o)

PARAMS		=	./dataset/dataset.tsv

CRITERION	=	--coverage -lcriterion

INCLUDE		=

LIBPATH		=

LIB			=

NAME		=	SC_trading_advisor

TESTNAME	=	unit_tests

REMOVE		=	*.o						\
				vgcore*					\
				*gc*

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(MAIN) $(SRC) $(INCLUDE) $(LIBPATH) $(LIB) $(CFLAG)

debug:
	$(CC) -g3 -o $(NAME) $(MAIN) $(SRC) $(INCLUDE) $(LIBPATH) $(LIB) $(CFLAG)

tests_run:
	$(CC) -g3 -o $(TESTNAME) $(SRC) $(TEST) $(INCLUDE) $(LIBPATH) $(LIB) $(CRITERION) $(CFLAG)
	./$(TESTNAME)

show_coverage:
	gcovr --filter $(SRCPATH)

valgrind: debug
	valgrind $(VGFLAG) ./$(NAME) $(PARAMS)

clean:
	rm -f $(REMOVE)

fclean:	clean
	rm -f $(NAME) $(TESTNAME)

re:	fclean all
