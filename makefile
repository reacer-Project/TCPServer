CC=gcc
CFLAGS= -g -Wall
target=server client
objects=read_fd.o write_fd.o send_fd.o recv_fd.o tcp_listen.o tcp_connect.o child_process_function.o worker.o
$(target):server.o $(objects)
	$(CC) -o server server.o $(objects)
	$(CC) -o client client.o tcp_connect.o
$(objects):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
server.o :server.c
	$(CC) $(CFLAGS) -c $< -o $@
client.o:client.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm *.o 
