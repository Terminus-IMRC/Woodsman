#include "common.h"
#include "bits_utils.h"

void print_bits_64(uint64_t b)
{
	uint64_t base=(uint64_t)1<<(64-1);

	while(base){
		printf("%d", b&base?1:0);
		base>>=1;
	}
	putchar('\n');

	return;
}
