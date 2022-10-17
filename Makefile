CC=gcc
#CFLAGS=-std=c11 -Wall -Wextra -Wextra -Wno-unused-parameter -Wno-unused-variable -Werror
CFLAGS=-std=c11 -Wall -Wextra -Wno-unused-parameter
LDLIBS =`pkg-config gtk+-3.0 --cflags --libs`
NAME = reversi

$(NAME): reversi.o logic.o lin-fifo.o connection.o
	$(CC) $(CFLAGS) -g reversi.o logic.o lin-fifo.o connection.o $(LDLIBS) -o $(NAME)

reversi.o: reversi.c logic.h fifo.h connection.h
	$(CC) $(CFLAGS) -c reversi.c $(LDLIBS) -o reversi.o

logic.o: logic.c logic.h connection.h fifo.h
	$(CC) $(CFLAGS) -c logic.c $(LDLIBS) -o logic.o

lin-fifo.o: lin-fifo.c fifo.h
	$(CC) $(CFLAGS) -c lin-fifo.c -o lin-fifo.o

connection.o: connection.c connection.h logic.h fifo.h
	$(CC) $(CFLAGS) -c connection.c $(LDLIBS) -o connection.o


clean:
	rm -f reversi.o logic.o lin-fifo.o connection.o reversi AtoB BtoA 
