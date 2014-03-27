#ifndef __MSBITS_H_INSIDE__
#define __MSBITS_H_INSIDE__

#include "common.h"
#include "tale_index.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint64_t msbits_t;

extern msbits_t msbits;

#define msbits_if_filled_all(m) (!((~((~(uint64_t)0)<<(X*X)))&(~((m)))))

void msbits_init();
void msbits_finalize();
void msbits_fill_element(int elem, msbits_t *m);
void msbits_adopt_tale_index(uint64_t ti, msbits_t *m);
void msbits_subtractive_fill_init();
_Bool msbits_subtractive_fill_all(msbits_t *m);

#endif /* __MSBITS_H_INSIDE__ */
