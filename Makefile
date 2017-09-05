OBJ=test
#SRC=sync.c
SRC=sync_cond.c

CCFLAGS += -lpthread

$(OBJ):$(SRC) 
	gcc -o $@ $^ $(CCFLAGS)

clean:
	rm $(OBJ)

