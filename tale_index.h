#ifndef __TALE_INDEX_H_INSIDE__
#define __TALE_INDEX_H_INSIDE__

#include "common.h"
#include "bits_utils.h"
#include "tale.h"
#include <stdint.h>

	typedef uint64_t* tale_index_t;

	extern tale_index_t tale_index;

#ifndef tale_index_if_adoptable_to_msbits
#define tale_index_if_adoptable_to_msbits(ti, m) if_factorial_of_2((((m))&((ti)))^((ti)))
#endif /* tale_index_if_adoptable_to_msbits */

	void tale_index_init();
	void tale_index_finalize();
	void tale_index_alloc();
	void tale_index_destroy();
	void tale_index_make();

#endif /* __TALE_INDEX_H_INSIDE__ */
