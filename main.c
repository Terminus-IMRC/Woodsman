#include "common.h"

int main()
{
	int i;

	msbits_init();
	tale_draft_init();
	tale_draft_read_tales();
	weight_init();
	index_init();

	while(!msbits_if_filled_all(msbits)){
		elem=weight_most_heavy_element(weight);
		msbits_fill_element(elem);
		msbits_auto_fill_by_subtract_all(msbits);
		do{
			for(i=0; i<ntales; i++){
				if(index_if_adoptable(index[i], msbits)){
					index_print_element(i);
					weight_subtract_by_index(index[i]);
					index_adopt_element(i);
					tale_destroy_element(i);
					i=-1;
				}
			}
		}while(msbits_auto_fill_by_subtract_all(msbits));
	}

	return 0;
}
