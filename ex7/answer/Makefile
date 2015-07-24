CC_FLAG = -Wall -std=c++11 -g
LD_FLAG =

CC = g++
RM = del

.PHONY : DEFAULT
DEFAULT : demo.exe


# Objects:

OBJS += priority_queue.o
priority_queue.o : priority_queue.cpp priority_queue.h common.h
	$(CC) -c $< -o $@ $(CC_FLAG)

OBJS += demo.o
demo.o : demo.cpp priority_queue.h common.h
	$(CC) -c $< -o $@ $(CC_FLAG)

# Target binaries:

TARS += demo.exe
demo.exe : demo.o priority_queue.o
	$(CC) $^ -o $@ $(LD_FLAG)

.PHONY : objs
objs : $(OBJS)

.PHONY : targets
target : $(TARS)

.PHONY : clean
clean :
	$(RM) *~ a.out a.exe $(OBJS) $(TARS)


