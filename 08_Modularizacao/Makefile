CFLAGS = -Wall -g # todos os avisos, com infos de debug

PROG = main
FONTES = main.c bibfunc.c
OBJETOS = $(FONTES:.c=.o) # main.o bibfunc.o

$(PROG): $(OBJETOS)  # main.o bibfunc.o
	gcc $(CFLAGS) $(OBJETOS) -o $@

clean:
	rm -f $(OBJETOS) $(PROG)
