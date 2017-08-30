.PHONY: all
.PHONY: clean


all:	
	for dir in `ls` ; do if [ -d $$dir ]; then  cd $$dir ; make ; cd - ; fi done

clean:
	for dir in `ls` ; do if [ -d $$dir ]; then  cd $$dir ; make clean ; cd - ; fi done
