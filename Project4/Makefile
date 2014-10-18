GCC = gcc
CFLAGS = -g -Werror -Wbad-function-cast -Wall -Wshadow -Werror -O3 
LIBS = -lm
SOURCES = reroot.c 
TARGET = proj4

build: $(TARGET) 

all:
	gcc -Werror -Wbad-function-cast -Wall -Wshadow -O3 reroot.c -o proj4

$(TARGET): $(OBJS) | environment 
	$(GCC) $(CFLAGS) -o 
