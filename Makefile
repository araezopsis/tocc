tocc: tocc.c

test: tocc
	./test.sh

clean:
	rm -f tocc *.o *~ tmp*
