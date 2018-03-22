CC = g++
INC = -I./Header
CFLAGS = -c -g -Wall -Wextra

all: main

%.o: %.cpp
	$(CC) -O3 -c -o $@ $< $(INC) $(CFLAGS)

main.o: main.cpp
	$(CC) -O3 -c main.cpp $(INC)

clean:
	rm main
	rm *.o
