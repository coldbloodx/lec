OBJS = lib/libop.o
SO = libop.so
MAIN = main.o
ALL = main
SODEST = /usr/lib


$(ALL): $(MAIN) $(SO)
	gcc -o $@ $^

$(SO): $(OBJS)
	gcc -fPIC -shared -o $@ $^

clean:
	rm -f $(SO) $(MAIN) $(ALL) $(OBJS)

install:
	cp $(SO) $(SODEST)/ 

uninstall:
	unlink $(SODEST)/$(SO)
