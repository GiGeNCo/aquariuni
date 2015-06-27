LIB = -L/usr/local/lib -lwiringPi
CFLAGS = -g -O2 -Wall 
OBJ = aquariuni.o dht11.o lcd.o slog.o info.o

BUILD = ../bin
INSTALL = /usr/local/bin

all: $(OBJ)
	$(CC) $(CFLAGS) -o aquariuni $(OBJ) $(LIB)

build:
	@test -d $(BUILD) || mkdir $(BUILD)
	@install -m 0755 aquariuni $(BUILD)/

install:
	@test -d $(INSTALL) || mkdir $(INSTALL)
	@install -m 0755 aquariuni $(INSTALL)/

aquariuni.o: dht11.h lcd.h slog.h info.h stdinc.h
dht11.o: dht11.h stdinc.h
lcd.o: lcd.h stdinc.h
slog.o: slog.h stdinc.h
info.o: info.h stdinc.h

.PHONY: clean

clean:
	$(RM) aquariuni $(OBJ)
