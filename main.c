#include "common.h"
#include "X.h"
#include "tale.h"
#include "tale_draft.h"
#include "tale_index.h"
#include "msbits.h"
#include "weight.h"
#include "bits_utils.h"
#include "string_utils.h"
#include <stdio.h>

int main()
{
	long int i;
	int elem;

	tale_draft_init();
	tale_read();
	tale_index_init();
	weight_init();
	msbits_init();

	printf("main: initialization finished\n");

	printf("weight: ");
	weight_print(weight);

	while(!msbits_if_filled_all(msbits)){
		printf("main: before adopt element: msbits:\n");
		print_bits_64(msbits);
		elem=weight_most_heavy_element(weight, msbits);
		printf("main: bruteforce element: %d\n", elem);
		msbits_fill_element(elem, &msbits);
		printf("main: after adopt element: msbits:\n");
		print_bits_64(msbits);
		msbits_subtractive_fill_all(&msbits);
		for(i=0; i<(long int)ntales; i++){
			if(tale_index_if_adoptable_to_msbits(tale_index[i], msbits)){
				printf("main: applying tale[%ld]: ", i);
				tale_print(tale[i]);
				printf("main: the tale_index[%ld]:\n", i);
				print_bits_64(tale_index[i]);
				msbits_adopt_tale_index(tale_index[i], &msbits);
				weight_subtract_by_tale_index(tale_index[i], weight);
				printf("main: after adopting: msbits:\n");
				print_bits_64(msbits);
				i=-1;
			}
			if(msbits_subtractive_fill_all(&msbits)){
				i=-1;
			}
		}
	}

	printf("main: final msbits:\n");
	print_bits_64(msbits);
	printf("main: end of the sky fragile\n");

	return 0;
}
