all: sax dom
	@:

sax: saxreader.c
	gcc -g saxreader.c -o sax -I"/usr/include/libxml2" -lxml2

dom: domreader.c
	gcc -g domreader.c -o dom -I"/usr/include/libxml2" -lxml2

clean:
	rm -f sax dom
