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

int
printbits(bit_array_t *barr) {
  int c = barr->num_elems;
  int n = barr->arr[0];
  int i = c-1;

  while (n >= 2) {
    printf("%d", n & 1);
    i--;
    n >>= 1;
  }
  printf("%d\n", n & 1);
  return 0;
}

bit_array_t*
new_bitarray(int size) {
  int width = (size/32) + 1;
  int *barray = malloc((sizeof (int)) * width);

  bit_array_t *result = malloc(sizeof (bit_array_t));

  result->num_ints = width;
  result->num_elems = size;

  for(int i = 0; i < width; i++) {
    barray[i] = 0;
  }

  result->arr = barray;

  return result;
}

int
setbit(bit_array_t* arr, int k) {
  /* The position in the array of the int we're looking at */
  int i = k/32;

  /* The position of the bit in the int itself */
  int pos = k % 32;

  unsigned int flag = 1;

  /* Shift the flag to the position of the bit we want to set */
  flag = flag << pos;

  arr->arr[i] = arr->arr[i] | flag;

  return 0;
}

int
unsetbit(bit_array_t* arr, int k) {
  int i = k/32;

  int pos = k % 32;

  unsigned int flag = 1;

  flag = ~(flag << pos);

  arr->arr[i] = arr->arr[i] & flag;

  return 0;
}

uint64_t
get_index(int size, const char* value) {
  uint64_t hval;

  fnv64Init(&hval);

  fnv64UpdateBuffer(&hval, value, strlen(value));
  return hval % size;
}

int
main (void) {
  bit_array_t *test = new_bitarray(100);
  printbits(test);
  setbit(test, 6);
  printbits(test);

  const char *test_string = "what is this I can't even, lololol";
  printf("%zu\n", get_index(5*32, test_string));

  return EXIT_SUCCESS;
}
