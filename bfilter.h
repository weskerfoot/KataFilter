typedef
  struct {
    size_t num_elems;
    size_t num_ints;
    uint32_t *arr;
  }
  bit_array_t;

int printbits(uint32_t, size_t);

int print_barray(bit_array_t*);

bit_array_t* new_bitarray(int);

int setbit(bit_array_t*, int);
int unsetbit(bit_array_t*, int);
