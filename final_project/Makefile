RASPI_HOST = jambaek@100.113.15.114
RASPI_DIR = ~/final
RASPI = $(RASPI_HOST):$(RASPI_DIR)
CC = gcc
CFLAG = -fPIC -c
SHARE = -shared -lwiringPi
OPT = -lwiringPi -ldl -lpthread -rdynamic

LIBLED = libled.so
LIBBUZZER = libbuzzer.so
LIBCDS = libcds.so
LIBSEG = libseg.so
LIBTEMP = libtemp.so
LIB = $(LIBLED) $(LIBBUZZER) $(LIBCDS) $(LIBSEG) $(LIBTEMP)

all: $(LIB) server client

$(LIBLED): led.o
	$(CC) -o $@ $< $(SHARE)
	scp $@ $(RASPI)

$(LIBBUZZER): buzzer.o
	$(CC) -o $@ $< $(SHARE)
	scp $@ $(RASPI)

$(LIBCDS): cds.o
	$(CC) -o $@ $< $(SHARE)
	scp $@ $(RASPI)

$(LIBSEG): segment.o
	$(CC) -o $@ $< $(SHARE)
	scp $@ $(RASPI)

$(LIBTEMP): temperature.o
	$(CC) -o $@ $< $(SHARE)
	scp $@ $(RASPI)

%.o: %.c
	$(CC) $(CFLAG) $< -o $@

server: server.c
	$(CC) server.c -o $@ $(OPT)
	scp $@ $(RASPI)

client: client.c
	$(CC) client.c -o $@

clean:
	rm -f *.o *.so server client 