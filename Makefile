CC=g++
FLAGS=-std=c++14 -O2 -Wall -Wno-sign-compare
OUTPUT=solution

all: main.cpp
	$(CC) $(FLAGS) main.cpp -o $(OUTPUT)
clean:
	rm -f *.o $(EXECUTABLE)