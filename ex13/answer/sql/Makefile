CC = g++
CFLAG = -std=c++11 -O2 -Wall

HEADER += query_maker.h

SRC += sql_test.cpp
SRC += query_maker_*.cpp

sql_test.exe : $(SRC) $(HEADER)
	g++ $(CFLAG) $(SRC) -o $@


