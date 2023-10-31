# Simply replace CC with your own compiler
# if it doesn't match the ones listed below.

#CC = i586-pc-msdosdjgpp-gcc
#CC = i686-w64-mingw32-gcc
#CC = x86_64-w64-mingw32-gcc
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -std=c2x -Ofast
RM = rm

BDIR = bin
ODIR = obj
SDIR = src

SOURCE = $(shell find src/*.c -printf "%f ")

# Update this line to change the name of target executable
TARGET = hide

BIN = $(TARGET:%=$(BDIR)/%)
OBJ = $(SOURCE:%.c=$(ODIR)/%.o)

.PHONY: all clean
all: $(BIN)
clean:
	$(RM) -f $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

$(OBJ): $(ODIR)/%.o: $(SDIR)/%.c
	$(CC) $^ -o $@ $(CFLAGS) -r
