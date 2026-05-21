# Makefile multiplataforma

PROG = desenho

# Compilador
CC = gcc

# Flags
CFLAGS = -Iinclude -g -O3 -fPIC # -Wall -g  # Todas as warnings, infos de debug
LDFLAGS  =
LIBS     = -L. -lshapes

# Detecta SO and e ajusta extensao se necessario
ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    EXEEXT  = .exe
    OSNAME  = Windows
    LIBS    += -lm
else
    UNAME_S := $(shell uname -s)
    EXEEXT  =
    ifeq ($(UNAME_S),Linux)
        OSNAME  = Linux
        LIBS    += -lm 
    endif
    ifeq ($(UNAME_S),Darwin)
        OSNAME  = macOS
        CFLAGS  += -Wno-deprecated
        LIBS    += -lm
    endif
endif

# Fontes
FONTES = main.c 
OBJ = $(FONTES:.c=.o)

FONTES2 = shapes.c
OBJ2 = $(FONTES2:.c=.o) # shapes.o

# Target (com extensao se necessario)
TARGET = $(PROG)$(EXEEXT)

# Regras
all: $(TARGET)
	@echo "Build completado para $(OSNAME). Saida: $(TARGET)"

$(TARGET): $(OBJ) libshapes.a
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)

libshapes.a: $(OBJ2) # shapes.o
	ar rcs libshapes.a $(OBJ2)

libshapes2.so: $(OBJ2)
	gcc -fPIC -shared -o libshapes2.so $(OBJ2) $(LDFLAGS)

desenho-shared: $(OBJ) libshapes2.so
	gcc $(OBJ) -o desenho-shared -L. -lshapes2 -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(OBJ)) $(TARGET) 2>nul || true
else
	rm -f $(OBJ) $(TARGET) $(OBJ2) libshapes.a libshapes2.so desenho-shared
endif

# Mostra infos do SO detectado
info:
	@echo "SO detectado: $(OSNAME)"
	@echo "Compilador:   $(CC)"
	@echo "CFLAGS:       $(CFLAGS)"
	@echo "LIBS:        $(LIBS)"
	@echo "Target:       $(TARGET)"

.PHONY: all clean info

