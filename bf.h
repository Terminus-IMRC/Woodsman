#ifndef __BF_H_INSIDE__
#define __BF_H_INSIDE__

#include "common.h"
#include "X.h"
#include "msbits.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

	typedef uint32_t bf_history_id_t;

#define BHI_BF ((bf_history_id_t)1<<0)
#define BHI_SFILL ((bf_history_id_t)1<<1)
#define BHI_TALE ((bf_history_id_t)1<<2)

	struct bf_history_t{
		bf_history_id_t id;
		int bf_elem;
		uint64_t m;
		long int num_tale_num;
		long int *tale_num;
	};
	typedef struct bf_history_t bf_history_t;

	extern int min_bf_count;
	extern bf_history_t *bf_history, *bf_history_best;

	void bf_init();
	void bf_history_part_clean(bf_history_t *t);
	void bf(int level);
	void bf_history_output(bf_history_t *h, int min);
	void bf_history_cp(bf_history_t *dst, bf_history_t *src, int n);

#endif /* __BF_H_INSIDE__ */
