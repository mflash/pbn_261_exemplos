#
# Makefile para Linux e macOS
#

PROG = leituracsv
SOURCE  = leituracsv.c
OBJECTS = $(SOURCE:.c=.o)
CFLAGS = -Wall -g

all: $(PROG)

$(PROG): $(OBJECTS)
	gcc $(OBJECTS) -O3 -o $(PROG)

clean:
	-@ rm -f $(OBJECTS) $(PROG)
