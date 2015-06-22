LIB = -L/usr/local/lib -lwiringPi
CFLAGS = -g -O2 -Wall 
OBJ = dht11.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o dht11 $(LIB)

.PHONY: clean

clean:
	$(RM) dht11 $(OBJ)