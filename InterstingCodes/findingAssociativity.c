#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <time.h>

// 128Kib L1d Cache -> Intel i7 4710HQ 
#define CSIZE 1024*128

uint64_t rdtsc(void){
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "= a" (lo), "= d" (hi));
    return ((uint64_t)lo | ((uint64_t)hi << 32));
}

int main(){
    // Expected Max associativity to check for : 16 , so 16 + 1 = 17  
    int ways=17;
    int offset;
    // Time fns
    uint64_t t1, t2,lat[ways];
    t1 = 0; t2 = 0;
    // Char to access every byte
    char *arr = (char *)malloc(ways*CSIZE*sizeof(char));
    char tmp;
    // Initialise
    for(int i = 0; i < ways; i++)
        lat[i] = 0;
    // Run tests 100 times to remove noise
    for(int i = 0; i < 100; i++){
    // Bring to Cache : arr + 128Kb , arr + 2*128Kb , arr + 3*128Kb .... 
    // Expected behaviour of latency : low , low , low , low , high , high , high .... high 
    // The number of lows tell us the cache associativity , 
    // this is because we only keep replacing blocks of the same set.
    // Then we access in revere order that way we use the already existing data in cache creating the low
    // When we don't have it ( > associativity ) the L1 cache has to replace it from L2 / L3.
    // Creating the highs that happen after that
        for(int i = 0; i< ways; i++)
            tmp = arr[i*CSIZE];   
        
        for(int i = 0; i< ways; i++){
            offset = (ways-i)*CSIZE;
            t1 = rdtsc();
            _mm_mfence();
            tmp = arr[offset];
            _mm_mfence();
            t2 = rdtsc();
            _mm_mfence();
            lat[i] += (t2 - t1);
        }
    }
    for (int i = 0; i<ways; i++)
        printf("%d  %lu \n", i, lat[i]/100);
  
  free(arr);
  return 0;
}


// Result from one run on i7 
// 0  174		//cold miss
// 1  111
// 2  111
// 3  113
// 4  114
// 5  114
// 6  117
// 7  119
// 8  118
// 9  119		//constant from 9th strike
// 10  119
// 11  119
// 12  119
// 13  119
// 14  119
// 15  119
// 16  119