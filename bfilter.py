#! /usr/bin/env python3

from cffi import FFI
from sys import stdout

ffi = FFI()

lib = ffi.dlopen("./bfilter.so")

ffi.cdef("""
typedef
  struct {
    size_t num_elems;
    size_t num_ints;
    uint32_t *arr;
  }
  bit_array_t;

typedef
  struct {
    uint32_t hash_1;
    uint32_t hash_2;
  }
  fnv_hashes_t;

typedef uint32_t* hashes_t;

int printbits(uint32_t, size_t);

int print_barray(bit_array_t*);

bit_array_t* empty_bfilter(int);

fnv_hashes_t hash_fnv(const char*);

uint32_t kth_hash(fnv_hashes_t, uint32_t, size_t);

hashes_t hash(const char *, uint32_t, size_t);

int setbit(bit_array_t*, int);
int unsetbit(bit_array_t*, int);

int bfilter_set(bit_array_t *, const char*, int);
int  bfilter_get(bit_array_t *, const char*, int);

int getbit(bit_array_t *, int);

int release_bfilter(bit_array_t *);
""")

class BloomFilter:
    def __init__(self, m=40000, k=10):
        self.m = m
        self.k = k

        self.bitset = ffi.gc(lib.empty_bfilter(m), lib.release_bfilter)

    def add(self, key):
        lib.bfilter_set(self.bitset, key.encode("UTF-8"), self.k)
        return True

    def __getitem__(self, key):
        return lib.bfilter_get(self.bitset, key.encode("UTF-8"), self.k) == 1
