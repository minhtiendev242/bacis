

static: 
	ar rcs lib/static/libhello.a obj/helloKhanh.o obj/helloWorld.o

link:
	gcc obj/main.o -Llib/static -lhello -o bin/exam

all:
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c src/helloKhanh.c -o obj/helloKhanh.o -I./inc
	gcc -c src/helloWorld.c -o obj/helloWorld.o -I./inc

clean: 
	rm -rf obj/* bin/*

shared:
	gcc -shared obj_shared/helloKhanh.o obj_shared/helloWorld.o -o lib/shared/libshared.so

link_shared: 
	gcc obj_shared/main.o -Llib/shared -lshared -o bin/exam_shared

all_shared:
	gcc -c main.c -o obj_shared/main.o -I./inc
	gcc -c -fPIC src/helloKhanh.c -o obj_shared/helloKhanh.o -I./inc
	gcc -c -fPIC src/helloWorld.c -o obj_shared/helloWorld.o -I./inc

move_default_location:
	sudo mv lib/shared/libshared.so /usr/lib
	sudo chmod 755 /usr/lib/libshared.so

use_with_default_location:
	bin/exam_shared

clean_shared:
	rm -rf obj_shared/* bin/*
