all: main

CC = gcc
override CFLAGS = -g -fexec-charset=UTF-8 -finput-charset=UTF-8

SRCS = $(shell dir /s /b *.c)
HEADERS = $(shell dir /s /b *.h)
main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "Trabalho1.exe"

clean:
	del /f Trabalho1.exe