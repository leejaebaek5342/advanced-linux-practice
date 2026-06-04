RASPI = jambaek@100.113.15.114:~/final
CC = gcc
CFLAG = -fPIC -c
SHARE = -shared -lwiringPi
OPT = -lwiringPi -ldl -lpthread

LIBLED = libled.so
LIBBUZZER = libbuzzer.so
LIBCDS = libcds.so
LIBSEG = libseg.so
LIBTEMP = libtemp.so


all: $(LIBLED) $(LIBBUZZER) $(LIBCDS) $(LIBSEG) $(LIBTEMP)	server client

$(LIBLED): led.o
	$(CC) -o $@ $< $(SHARE)
	scp $(LIBLED) $(RASPI)

$(LIBBUZZER): buzzer.o
	$(CC) -o $@ $< $(SHARE)
	scp $(LIBBUZZER) $(RASPI)
	
$(LIBCDS): cds.o
	$(CC) -o $@ $< $(SHARE)
	scp $(LIBCDS) $(RASPI)

$(LIBSEG): segment.o
	$(CC) -o $@ $< $(SHARE)
	scp $(LIBSEG) $(RASPI)

$(LIBTEMP): temperature.o
	$(CC) -o $@ $< $(SHARE)
	scp $(LIBTEMP) $(RASPI)

%.o: %.c
	$(CC) $(CFLAG) $< -o $@

server: server.c
	$(CC) server.c -o $@ $(OPT)
	scp $@ $(RASPI)

client: client.c
	$(CC) client.c -o $@

clean:
	rm -f *.o *.so server client