typedef
  struct {
    size_t number;
    int *arr;
  }
  bit_array_t;

int countbits(int);

int printbits(int);

int *new_bitarray(int);

int setbit(int*, int);
int unsetbit(int*, int);
