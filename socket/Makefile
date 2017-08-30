OBJS = $(shell allfile=''; for file in `ls`; do allfile="$${allfile} `echo $$file |cut -d '.' -f 1`"; done; echo $$allfile)
OBJ = $(OBJS:Makefile=)
LOADLIBES = -lpthread

.PHONY: all

all: $(OBJS)

$(OBJ):

clean:
	rm -f $(OBJ)
