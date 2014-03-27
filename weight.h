#ifndef __WEIGHT_H_INSIDE__
#define __WEIGHT_H_INSIDE__

#include "tale_index.h"
#include <stdio.h>
#include <stdlib.h>

	typedef long int weight_element_t;
	typedef weight_element_t* weight_t;

	extern weight_t weight;

	void weight_init();
	void weight_finalize();
	void weight_alloc();
	void weight_destroy();
	void weight_make();
	long int weight_most_heavy_element(weight_t weight);
	void weight_subtract_by_tale_index(uint64_t ti, weight_t weight);
	void weight_print(weight_t weight);

#endif /* __WEIGHT_H_INSIDE__ */
