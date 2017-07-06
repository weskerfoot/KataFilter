default: bfilter.c bfilter.h
	$(CC) -g -Wall -Wextra -std=gnu99 -Wpointer-arith -Wmissing-prototypes -lm -L. -O3 ./bfilter.c -o test --static `pkg-config --libs --cflags libfnv` -Wl,-rpath,/home/wes/bfilter;

lib: bfilter.c bfilter.h
	$(CC) -g -DLIB -c -fpic -Wall -Wextra -pedantic -Wpointer-arith -Werror -std=c99 -lm -L. -O3 ./bfilter.c --static `pkg-config --libs --cflags libfnv` -Wl,-rpath,/home/wes/bfilter;
	$(CC) -shared -o bfilter.so bfilter.o;
