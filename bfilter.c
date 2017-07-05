#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "error.h"
#include "maa.h"
#include "bfilter.h"

int countbits(int n) {
  int c = 0;
  while (n >>= 1) {
    c++;
  }
  return c+1;
}

int
printbits(int n) {
  int c = countbits(n);
  int i = c;
  int *bits = malloc((sizeof (int)) * c);

  while (n >= 2) {
    bits[i-1] = n & 1;
    i--;
    n >>= 1;
  }
  bits[i-1] = n & 1;
  for (int i = 0; i < c; i++) {
    printf("%d", bits[i]);
  }
  printf("\n");
  free(bits);
  return 0;
}

int*
new_bitarray(int size) {
  int *barray = malloc((sizeof (int)) * size);

  int i;
  for(i = 0; i < size; i++) {
    barray[i] = 0;
  }
  return barray;
}

int
setbit(int* arr, int k) {
  /* The position in the array of the int we're looking at */
  int i = k/32;

  /* The position of the bit in the int itself */
  int pos = k % 32;

  unsigned int flag = 1;

  /* Shift the flag to the position of the bit we want to set */
  flag = flag << pos;

  arr[i] = arr[i] | flag;

  return 0;
}

int
unsetbit(int* arr, int k) {
  int i = k/32;

  int pos = k % 32;

  unsigned int flag = 1;

  flag = ~(flag << pos);

  arr[i] = arr[i] & flag;

  return 0;
}

int
main (void) {
  int *test = new_bitarray(5);
  setbit(test, 6);
  setbit(test, 4);
  setbit(test, 2);
  unsetbit(test, 6);
  unsetbit(test, 4);
  unsetbit(test, 2);
  printbits(test[0]);
  return EXIT_SUCCESS;
}

