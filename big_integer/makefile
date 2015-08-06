CC = gcc
CC_Flag= -std=c99 -Wall -g
LD_Flag= -Wl,-wrap,malloc

UNIT_TEST : unit_test.out

unit_test_list.h : unit_case_add.c
	./genarate_unit_test_list.sh

smoke : smoke_test.out

LIB_OBJS += big_integer.o
big_integer.o : big_integer.c big_integer.h
	$(CC) -c $< $(CC_Flag) -o $@

SMOKE_OBJS += smoke_test.o
smoke_test.o : smoke_test.c 
	$(CC) -c $< $(CC_Flag) -o $@

UNIT_OBJS += unit_test.o
unit_test.o : unit_test.c unit_test.h unit_test_list.h
	$(CC) -c $< $(CC_Flag) -o $@

MEMORY_OBJS += memory_wrapper.o
memory_wrapper.o : memory_wrapper.c memory_wrapper.h
	$(CC) -c $< $(CC_Flag) -o $@

CASE_OBJS += unit_case_add.o
unit_case_add.o : unit_case_add.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_minus.o
unit_case_minus.o : unit_case_minus.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_multiply.o
unit_case_multiply.o : unit_case_multiply.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_divide.o
unit_case_divide.o : unit_case_divide.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_mod.o
unit_case_mod.o : unit_case_mod.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_less.o
unit_case_less.o : unit_case_less.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_less_equal.o
unit_case_less_equal.o : unit_case_less_equal.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_greater.o
unit_case_greater.o : unit_case_greater.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_greater_equal.o
unit_case_greater_equal.o : unit_case_greater_equal.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_equal.o
unit_case_equal.o : unit_case_equal.c
	$(CC) -c $^ $(CC_Flag) -o $@

CASE_OBJS += unit_case_not_equal.o
unit_case_not_equal.o : unit_case_not_equal.c
	$(CC) -c $^ $(CC_Flag) -o $@

TARGET += unit_test.out
unit_test.out : $(UNIT_OBJS) $(CASE_OBJS) $(LIB_OBJS) $(MEMORY_OBJS)
	$(CC) $^ $(CC_Flag) -o $@

SMOKE_TARGET += smoke_test.out
smoke_test.out : $(SMOKE_OBJS) $(LIB_OBJS) $(MEMORY_OBJS)
	$(CC) $^ $(CC_Flag) -o $@

clean:
	rm -rf $(CASE_OBJS) $(UNIT_OBJS) $(TARGET) $(LIB_OBJS) $(SMOKE_OBJS) $(MEMORY_OBJS) $(SMOKE_TARGET)
