#ifndef __WEIGHT_H_INSIDE__
#define __WEIGHT_H_INSIDE__

#include "tale_index.h"

	typedef long int weight_element_t;
	typedef weight_element_t* weight_t;

	extern weight_t weight;

	void weight_init();
	void weight_finalize();
	void weight_alloc();
	void weight_destroy();
	void weight_make();

#endif /* __WEIGHT_H_INSIDE__ */
