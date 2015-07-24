CC = g++
CC_FLAG = -std=c++11 -Wall -g -ftemplate-depth=2000
LD_FALG =
RM = rm -rf

HEADER += binary.h
HEADER += find_most.h
HEADER += find_most_impl.h
HEADER += safe_compare.h
HEADER += safe_compare_impl.h
HEADER += prime_table.h
HEADER += meta_function.h
HEADER += unit.h

SRC += test.cpp

.PHONY: test
test : test.exe
	./test.exe

test.exe : $(SRC) $(HEADER)
	$(CC) $(SRC) $(CC_FLAG) $(LD_FLAG) -o $@ 2> error.txt

.PHONY: clean
clean:
	$(RM) test.exe *.o *~ error.txt


