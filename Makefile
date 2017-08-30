.PHONY: all
.PHONY: clean


MAKE = make -k -B
MAKECLEAN = make clean

MAKEFILES = $(shell find . -iname makefile)
CUR_DIR = $(shell pwd)

all:	
	@for makefile in $(MAKEFILES); do\
	    echo making $$makefile...; \
	    sub_dir=`dirname $$makefile`; \
	    cd $$sub_dir &&  $(MAKE) ; \
	    cd $(CUR_DIR); \
	    echo ;\
	done

clean:
	@for makefile in $(MAKEFILES); do\
	    sub_dir=`dirname $$makefile`; \
	    echo cleaning $$sub_dir...; \
	    cd $$sub_dir &&  $(MAKECLEAN) ; \
	    cd $(CUR_DIR); \
	    echo ; \
	done
