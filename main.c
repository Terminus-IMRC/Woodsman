#include "common.h"
#include "X.h"
#include "tale.h"
#include "tale_draft.h"
#include "tale_index.h"
#include "msbits.h"
#include "weight.h"
#include "bits_utils.h"
#include "string_utils.h"
#include "bf.h"
#include "dpf.h"
#include <stdio.h>

int main()
{
	tale_draft_init();
	tale_read();
	tale_index_init();
	weight_init();
	msbits_init();
	bf_init();

	dpf("main: initialization finished\n");

	printf("weight: ");
	weight_print(weight);

	bf(0);

	dpf("main: final msbits:\n");
	dprint_bits_64(msbits);

	printf("main: final min_bf_count: %d\n", min_bf_count);
	printf("main: the best bf history:\n");
	bf_history_output(bf_history_best, tale, min_bf_count);
	printf("main: end of the sky fragile\n");

	return 0;
}
