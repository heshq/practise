CC = gcc
CC_Flag= -std=c99 -Wall -g
LD_Flag= -Wl,-wrap,malloc

UNIT_TEST : unit_test.exe

unit_test_list.h : unit_case_add.c
	./genarate_unit_test_list.sh

UNIT_OBJS += unit_test.o
unit_test.o : unit_test.c unit_test.h unit_test_list.h
	$(CC) -c $< $(CC_Flag) -o $@

#UNIT_OBJS += memory_wrapper.o
#memory_wrapper.o : memory_wrapper.c memory_wrapper.h
#	$(CC) -c $< $(CC_Flag) -o $@

CASE_OBJS += unit_case_add.o
unit_case_add.o : unit_case_add.c
	$(CC) -c $^ $(CC_Flag) -o $@

TARGET += unit_test.exe
unit_test.exe : $(UNIT_OBJS) $(CASE_OBJS)
	$(CC) $^ $(CC_Flag) -o $@

clean:
	rm -rf $(CASE_OBJS) $(UNIT_OBJS) $(TARGET)