#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CC = arm-cortexm3-uclinuxeabi-gcc
CFLAGS += -O2 -g -Wall -std=c99 #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS +=


all: game
game: display.o input.o

%.o: %.c
	${CC} ${CFLAGS} -c $<

clean:
	-rm -f game *.o

install:


.PHONY: all install clean

# end of development makefile
