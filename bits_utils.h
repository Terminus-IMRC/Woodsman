#ifndef __BITS_UTILS_H_INSIDE__
#define __BITS_UTILS_H_INSIDE__

#include <stdio.h>

#ifndef if_factorial_of_2
#define if_factorial_of_2(v) ( ((v)) && (!(((v))&(((v))-1))) )
#endif /* if_factorial_of_2 */

#ifdef DEBUG
#define dprint_bits_64(b) print_bits_64(b)
#else
#define dprint_bits_64(b)
#endif

	void print_bits_64(uint64_t b);

#endif /* __BITS_UTILS_H_INSIDE__ */
