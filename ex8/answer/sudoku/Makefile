CC = g++
RM = del
CC_FLAG = -Wall -std=c++11
LD_FLAG =

.PHONY : DEFAULT
DEFAULT : targets

#objs

OBJ += sudoku.o
sudoku.o : sudoku.cpp sudoku.h
	$(CC) -c $< $(CC_FLAG) -O3 -o $@

OBJ += timer.o
timer.o : timer.cpp timer.h
	$(CC) -c $< $(CC_FLAG) -O3 -o $@

OBJ += test.o
test.o : test.cpp sudoku.h timer.h solve.h
	$(CC) -c $< $(CC_FLAG) -O3 -o $@

.PHONY : objects
objects : $(OBJ)

#bins

TAR += test_naive_o0.exe
test_naive_o0.exe : solve_naive.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O0 $(LD_FLAG) -o $@

TAR += test_naive_o2.exe
test_naive_o2.exe : solve_naive.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O2 $(LD_FLAG) -o $@

TAR += test_naive_o3.exe
test_naive_o3.exe : solve_naive.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O3 $(LD_FLAG) -o $@

TAR += test_stack_o0.exe
test_stack_o0.exe : solve_stack.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O0 $(LD_FLAG) -o $@

TAR += test_stack_o2.exe
test_stack_o2.exe : solve_stack.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O2 $(LD_FLAG) -o $@

TAR += test_stack_o3.exe
test_stack_o3.exe : solve_stack.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O3 $(LD_FLAG) -o $@

TAR += test_stack_simplified_o0.exe
test_stack_simplified_o0.exe : solve_stack_simplified.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O0 $(LD_FLAG) -o $@

TAR += test_stack_simplified_o2.exe
test_stack_simplified_o2.exe : solve_stack_simplified.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O2 $(LD_FLAG) -o $@

TAR += test_stack_simplified_o3.exe
test_stack_simplified_o3.exe : solve_stack_simplified.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O3 $(LD_FLAG) -o $@

TAR += test_naive_simplified_o0.exe
test_naive_simplified_o0.exe : solve_naive_simplified.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O0 $(LD_FLAG) -o $@

TAR += test_naive_simplified_o2.exe
test_naive_simplified_o2.exe : solve_naive_simplified.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O2 $(LD_FLAG) -o $@

TAR += test_naive_simplified_o3.exe
test_naive_simplified_o3.exe : solve_naive_simplified.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O3 $(LD_FLAG) -o $@

TAR += test_ultimate_o0.exe
test_ultimate_o0.exe : solve_ultimate.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O0 $(LD_FLAG) -o $@

TAR += test_ultimate_o2.exe
test_ultimate_o2.exe : solve_ultimate.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O2 $(LD_FLAG) -o $@

TAR += test_ultimate_o3.exe
test_ultimate_o3.exe : solve_ultimate.cpp solve.h $(OBJ)
	$(CC) $^ $(CC_FLAG) -O3 $(LD_FLAG) -o $@

.PHONY : targets
targets : $(TAR)


#phony

.PHONY : clean
clean :
	$(RM) $(TAR) $(OBJ) *~ a.out a.exe


