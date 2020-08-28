CC = g++
CCFLAGS = -Wall
EFLAGS = -I ~/Documents/Libraries/
LDFLAGS = -lncurses
OBJ = printTextCenter.cpp

driver.out: $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LDFLAGS) -o driver.out


.PHONY:
run:
	./driver.out

.PHONY:
valrun:
	valgrind ./driver.out

.PHONY:
clean:

	rm *.o*
	rm *~*
