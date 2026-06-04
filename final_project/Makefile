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
LIB = libled.so libbuzzer.so libcds.so libseg.so libtemp.so

all: $(LIB)	server client
	tar -czf final.tar.gz $(LIB) server
	scp final.tar.gz $(RASPI)
	ssh $(RASPI_HOST) "cd ~/final && tar -xzf final.tar.gz && rm -f final.tar.gz"
	rm -f final.tar.gz

$(LIBLED): led.o
	$(CC) -o $@ $< $(SHARE)

$(LIBBUZZER): buzzer.o
	$(CC) -o $@ $< $(SHARE)
	
$(LIBCDS): cds.o
	$(CC) -o $@ $< $(SHARE)

$(LIBSEG): segment.o
	$(CC) -o $@ $< $(SHARE)

$(LIBTEMP): temperature.o
	$(CC) -o $@ $< $(SHARE)

%.o: %.c
	$(CC) $(CFLAG) $< -o $@

server: server.c
	$(CC) server.c -o $@ $(OPT)

client: client.c
	$(CC) client.c -o $@

clean:
	rm -f *.o *.so server client 