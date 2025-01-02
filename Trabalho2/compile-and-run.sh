#!/bin/bash

SOURCE_FILES=$(find . -iname "*.c" -print)

if [ -z "$SOURCE_FILES" ]; then
    echo "no source files found."
    exit 1
fi

gcc -g -fexec-charset=UTF-8 -finput-charset=UTF-8 $SOURCE_FILES -o Trabalho2

if [ $? -ne 0 ]; then
    echo "compilation failed."
    exit 1
fi

# Run the program
./Trabalho2
