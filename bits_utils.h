#ifndef __BITS_UTILS_H_INSIDE__
#define __BITS_UTILS_H_INSIDE__

#include <stdio.h>

#ifndef if_factorial_of_2
#define if_factorial_of_2(v) ( ((v)) && (!(((v))&(((v))-1))) )
#endif /* if_factorial_of_2 */

	void print_bits_64(uint64_t b);

#endif /* __BITS_UTILS_H_INSIDE__ */
