LIB = -L/usr/local/lib -lwiringPi
CFLAGS = -g -O2 -Wall 
OBJ = main.o dht11.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ) $(LIB)

main.o: dht11.h stdinc.h
dht11.o: dht11.h stdinc.h

.PHONY: clean

clean:
	$(RM) dht11 $(OBJ)