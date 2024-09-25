.PHONY:= clean

CC:= gcc
CFLAG:= -Wall -g

SERVER = server
CLIENT = client 

all: $(SERVER) $(CLIENT)

$(SERVER): unix_dgram_server.c
	$(CC) $(CFLAG) -o $(SERVER) $^

$(CLIENT): unix_dgram_client.c
	$(CC) $(CFLAG) -o $(CLIENT) $^	

clean:
	rm -f $(SERVER) $(CLIENT) *.o