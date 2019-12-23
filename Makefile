CC := g++
WARN := -Wall -Wextra
CCOPTS := $(WARN) -O -g -static

fcomp : fcomp.o
	$(CC) $(CCOPTS) -o $@ $^

fcomp.o : fcomp.cpp fcomp.hpp Makefile
	$(CC) $(CCOPTS) -c $<

clean :
	rm -f *.o fcomp
