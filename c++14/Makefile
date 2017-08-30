OBJS = $(shell allfile=''; for file in `ls *.c *.cpp 2>/dev/null`; do allfile="$${allfile} `echo $$file |cut -d '.' -f 1`"; done; echo $$allfile)

.PHONY: all

CXXFLAGS = -std=c++14

all: $(OBJS)

clean:
	rm -f $(OBJS) core output
