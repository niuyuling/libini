CROSS_COMPILE ?= 
CC := $(CROSS_COMPILE)gcc
STRIP := $(CROSS_COMPILE)strip
AR := $(CROSS_COMPILE)ar
CFLAGS += -g -Wall
LIBS = libini.so
SLIB = libini.a

all: libini.o
	$(CC) $(CFLAGS) -FPIC -shared $^ -o $(LIBS)
	$(AR) -rc $(SLIB) $^

clean:
	rm -rf *.o
	rm $(LIBS) $(SLIB)
