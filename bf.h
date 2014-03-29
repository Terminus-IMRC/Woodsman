#ifndef __BF_H_INSIDE__
#define __BF_H_INSIDE__

#include "common.h"
#include "X.h"
#include "msbits.h"
#include <stdio.h>

	extern int min_bf_count;
	extern int *elem_history, *history_best;

	void bf_init();
	void bf(int level);
	void bf_history_output(int *h);
	void bf_history_cp(int *dst, int *src);

#endif /* __BF_H_INSIDE__ */
