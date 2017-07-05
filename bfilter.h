typedef
  struct {
    size_t num_elems;
    size_t num_ints;
    int *arr;
  }
  bit_array_t;

int printbits(bit_array_t*);

bit_array_t* new_bitarray(int);

int setbit(bit_array_t*, int);
int unsetbit(bit_array_t*, int);
