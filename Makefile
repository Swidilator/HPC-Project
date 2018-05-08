CC=g++
CFLAGS=-g -O0 -std=c++11
INC_MAIN=inc
INC_USER=src/inc

all: clean project

project: 
	$(CC) $(CFLAGS) -I$(INC_MAIN) -I$(INC_USER) src/*.cpp -o $@.out

clean:
	rm -f *.out *.o

latex:
	$(MAKE) -C latex
	cp latex/Project.pdf ./report.pdf
