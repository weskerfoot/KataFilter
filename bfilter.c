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
printbits(uint32_t n, size_t c) {
  uint32_t i = c-1;

  while (n >= 2) {
    printf("%d", n & 1);
    i--;
    n >>= 1;
  }
  printf("%d", n & 1);
  return 0;
}

int
print_barray(bit_array_t *arr) {
  for(uint32_t i = 0; i < arr->num_ints; i++) {
    printbits(arr->arr[i], arr->num_elems/arr->num_ints);
  }
  printf("\n");
  return 0;
}

bit_array_t*
new_bitarray(int size) {
  int width = (size/32) + 1;
  uint32_t *barray = malloc((sizeof (int)) * width);

  bit_array_t *result = malloc(sizeof (bit_array_t));

  result->num_ints = width;
  result->num_elems = width*32;

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
  setbit(test, 31);
  setbit(test, 63);
  setbit(test, 95);
  setbit(test, 127);
  print_barray(test);

  const char *test_string = "what is this I can't even, lololol";
  printf("%zu\n", get_index(5*32, test_string));

  return EXIT_SUCCESS;
}
