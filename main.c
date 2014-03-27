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

	while(!msbits_if_filled_all(msbits)){
		elem=weight_most_heavy_element(weight);
		printf("Bruteforce element:%d\n", elem);
		msbits_fill_element(elem, &msbits);
		msbits_subtractive_fill_all(&msbits);
		for(i=0; i<(long int)ntales; i++){
			if(tale_index_if_adoptable_to_msbits(msbits, tale_index[i])){
				/*tale_index_print(tale_index[i]);*/
				msbits_adopt_tale_index(tale_index[i], &msbits);
				weight_subtract_by_tale_index(tale_index[i], weight);
				i=-1;
			}
			if(msbits_subtractive_fill_all(&msbits)){
				i=-1;
			}
		}
	}

	return 0;
}
