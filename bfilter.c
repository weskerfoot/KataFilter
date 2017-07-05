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
  if ((uint32_t)k >= arr->num_elems) {
    printf("Tried to set a bit beyond the current limit, limit = %zu, k = %d\nExiting...\n", arr->num_elems, k);
    exit(1);
  }
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

fnv_hashes_t
hash_fnv(const char* value) {
  uint64_t hval;

  fnv_hashes_t hashes;

  fnv64Init(&hval);

  fnv64UpdateBuffer(&hval, value, strlen(value));

  uint32_t n_0 = hval >> 32;
  uint32_t n_1 = hval & 0x00000000ffffffff;

  hashes.hash_1 = n_0;
  hashes.hash_2 = n_1;

  return hashes;
}

uint32_t
kth_hash(fnv_hashes_t hashes,
         uint32_t i,
         size_t m) {
  return (hashes.hash_1 + hashes.hash_2 * i) % m;
}

hashes_t
hash(const char *input, uint32_t k, size_t m) {
  fnv_hashes_t fnv = hash_fnv(input);
  hashes_t hashes = malloc((sizeof (uint32_t)) * k);

  hashes[0] = fnv.hash_1 % m;
  hashes[1] = fnv.hash_2 % m;

  for(uint32_t i = 0; i < (k-2); i++) {
    hashes[i+2] = kth_hash(fnv, i+2, m);
  }
  return hashes;
}

int
main (void) {
  bit_array_t *test = new_bitarray(100);
  const char *test_string = "what tf is this I can't even, lololol";
  hashes_t hashes = hash(test_string, 5, 100);
  for(int i = 0; i < 5; i++) {
    printf("%zu\n", hashes[i]);
  }

  return EXIT_SUCCESS;
}
