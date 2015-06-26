LIB = -L/usr/local/lib -lwiringPi
CFLAGS = -g -O2 -Wall 
OBJ = main.o dht11.o lcd.o

all: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ) $(LIB)

main.o: dht11.h lcd.h stdinc.h
dht11.o: dht11.h stdinc.h
lcd.o: lcd.h stdinc.h

.PHONY: clean

clean:
	$(RM) main $(OBJ)
