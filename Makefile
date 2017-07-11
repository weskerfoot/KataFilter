default:
	$(MAKE) lib

lib: bfilter.c bfilter.h
	$(CC) -g -DLIB -c -fpic -Wall -Wextra -pedantic -Wpointer-arith -std=c99 -lfnv -lm -L. -O3 ./bfilter.c -Wl,-rpath./;
	$(CC) -shared -o bfilter.so bfilter.o;
