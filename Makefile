CFLAGS=-Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

tocc: $(OBJS)
	gcc -o tocc $(OBJS) $(LDFLAGS)

$(OBJS): tocc.h

test: tocc
	./test.sh

clean:
	rm -f tocc *.o *~ tmp*
