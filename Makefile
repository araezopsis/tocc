CFLAGS=-Wall -std=c11
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

tocc: $(OBJS)
	gcc -o tocc $(OBJS) $(LDFLAGS)

$(OBJS): tocc.h

test: tocc
	./tocc -test
	./test.sh

clean:
	rm -f tocc *.o *~ tmp*
