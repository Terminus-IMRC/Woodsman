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
#define msbits_fill_element(elem, mp) (*((mp)))|=((msbits_t)1)<<(X*X-elem-1)
#define msbits_adopt_tale_index(ti, mp) (*((mp)))|=((ti))
#define msbits_cp(dstp, src) (*((dstp)))=((src))

void msbits_init();
void msbits_finalize();
void msbits_subtractive_fill_init();
uint64_t msbits_subtractive_fill_all(msbits_t *m);

#endif /* __MSBITS_H_INSIDE__ */
