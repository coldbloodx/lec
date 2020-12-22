

.PHONY: all clean


all: server client cclient

cclient: cclient.c
	gcc -o cclient -g cclient.c

client: goclient.go
	go build -o client goclient.go

server: goserver.go
	go build -o server goserver.go


clean:
	rm -fr server client cclient
