#ifndef __MSBITS_H_INSIDE__
#define __MSBITS_H_INSIDE__

#include "common.h"
#include "tale_index.h"
#include "dpf.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint64_t msbits_t;

extern msbits_t msbits;

#define msbits_if_filled_all(m) (!((~((~(uint64_t)0)<<(X*X)))&(~((m)))))
#define substraction_base_if_adoptable_to_msbits(sb, m) if_factorial_of_2((((m))&((sb)))^((sb)))

void msbits_init();
void msbits_finalize();
void msbits_fill_element(int elem, msbits_t *m);
void msbits_adopt_tale_index(uint64_t ti, msbits_t *m);
void msbits_subtractive_fill_init();
uint64_t msbits_subtractive_fill_all(msbits_t *m);
void msbits_cp(msbits_t *dst, const msbits_t src);

#endif /* __MSBITS_H_INSIDE__ */
