CFLAGS = -Wall -pedantic
OBJS   = game.o
PROG = tictactoe
CXX = gcc

all: $(PROG)

%.o: src/%.c
	$(CXX) $(CFLAGS) -c -s $<

$(PROG): $(OBJS)
	$(CXX) $(OBJS) -o $(PROG) -lm

clean:
	rm $(PROG) *.o
