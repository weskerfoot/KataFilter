default: bfilter.c bfilter.h
	$(CC) -g -DTOK_LIB -Wall -Wextra -std=gnu99 -Wpointer-arith -Wmissing-prototypes -lmaa -lm -L. -O3 ./bfilter.c -o test -Wl,-rpath,/home/wes/bfilter;

unsafe: bfilter.c  bfilter.h
	$(CC) -DNDEBUG -DTOK_LIB -Wall -std=gnu99 -Wextra -Wpointer-arith -Wmissing-prototypes -lmaa -lm -L. -O3 ./bfilter.c -o bfilter -Wl,-rpath,/home/wes/bfilter;
