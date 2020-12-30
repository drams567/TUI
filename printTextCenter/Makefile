CC = g++
CCFLAGS = -Wall
EFLAGS = -I ~/Documents/Libraries/
LDFLAGS = -lncurses
OBJ = printTextCenter.cpp

driver.out: $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LDFLAGS) -o driver.out


.PHONY:
run:
	./driver.out 15 20

.PHONY:
valrun:
	valgrind ./driver.out 15 20

.PHONY:
clean:

	rm *.o*
	rm *~*
