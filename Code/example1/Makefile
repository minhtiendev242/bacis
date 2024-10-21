.PHONY: hello hellomake

CC := gcc
CFLAGS := -I.

INC_FILES := hello.h

%.o: %.c $(INC_FILES)
	$(CC) -c -o $@ $<

test: hello.h hello.c
	@echo $@
	@echo $< 
	@echo $^

hellomake: main.o hello.o
	$(CC) -o $@ main.o hello.o $(CFLAGS)

hello: 
	gcc -o hello main.c hello.c -I.

all:
	gcc -o exam hello.c main.c -I .

clean: 
	rm -rf exam
