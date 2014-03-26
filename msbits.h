#ifndef __MSBITS_H_INSIDE__
#define __MSBITS_H_INSIDE__

#include "common.h"
#include <stdint.h>

typedef uint64_t msbits_t;

extern msbits_t msbits;

#define msbits_if_filled_all(m) (!((~((~(uint64_t)0)<<(X*X)))&((m))))

void msbits_init();
void msbits_finalize();

#endif /* __MSBITS_H_INSIDE__ */
