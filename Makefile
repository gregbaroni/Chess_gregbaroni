CC		= gcc
CXX		= g++
FLAGS   = # add the -g flag to compile with debugging output for gdb
TARGET	= chess

OBJS = chessboard.o main.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

chessboard.o: chessboard.cpp chessboard.hpp
	$(CXX) $(FLAGS) -c -o chessboard.o chessboard.cpp

main.o: main.cpp
	$(CXX) $(FLAGS) -c -o main.o main.cpp

clean:
	rm *.o $(TARGET)
