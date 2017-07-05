#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <fnv.h>

#include "error.h"
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
  int i = c-1;

  while (n >= 2) {
    printf("%d", n & 1);
    i--;
    n >>= 1;
  }
  printf("%d\n", n & 1);
  return 0;
}

int*
new_bitarray(int size) {
  int *barray = malloc((sizeof (int)) * size);

  for(int i = 0; i < size; i++) {
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

uint64_t
get_index(int size, const char* value) {
  uint64_t hval;

  fnv64Init(&hval);

  fnv64UpdateBuffer(&hval, value, 6);
  return hval;
}

int
main (void) {
  int *test = new_bitarray(5);
  printbits(test[0]);
  setbit(test, 6);
  printbits(test[0]);

  const char *test_string = "foobar";
  printf("%zu\n", get_index(12, test_string));

  return EXIT_SUCCESS;
}
