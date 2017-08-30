ut: select_server fork_server client thread_server
	@:

select_server: select_server.cpp
	g++ -gdwarf-2 -g3 select_server.cpp -o select_server

fork_server: fork_server.cpp
	g++ -gdwarf-2 -g3 fork_server.cpp -o fork_server

thread_server: thread_server.cpp
	g++ -gdwarf-2 -g3 thread_server.cpp -o thread_server -lpthread

client: client.cpp
	g++ -gdwarf-2 -g3 client.cpp -o client

clean:
	rm -f fork_server select_server client thread_server
