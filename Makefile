default: bfilter.c bfilter.h
	$(CC) -g -Wall -Wextra -std=gnu99 -Wpointer-arith -Wmissing-prototypes -lmaa -lfnv -lm -L. -O0 ./bfilter.c -o test -Wl,-rpath,/home/wes/bfilter;

lib: bfilter.c bfilter.h
	$(CC) -g -DLIB -c -fpic -Wall -Wextra -pedantic -Wpointer-arith -Werror -std=c99 -lmaa -lfnv -lm -L. -O0 ./bfilter.c -Wl,-rpath,/home/wes/bfilter;
	$(CC) -shared -o bfilter.so bfilter.o;
