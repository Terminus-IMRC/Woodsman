#include "common.h"
#include "bf.h"

int min_bf_count;
int *elem_history, *history_best;

void bf_init();
void bf(int level);
void bf_output_history();

void bf_init()
{
	int i;

	min_bf_count=X*X;
	elem_history=(int*)malloc((X*X)*sizeof(int));
	assert(elem_history);
	history_best=(int*)malloc((X*X)*sizeof(int));
	assert(history_best);

	for(i=0; i<X*X; i++)
		history_best[i]=-1;

	return;
}

void bf(int level)
{
	int elem;
	long int i;
	uint64_t m_orig;

	msbits_cp(&m_orig, msbits);

	for(elem=level!=0?elem_history[level-1]+1:0; elem<X*X; elem++){
		printf("bf: bruteforce element: %d\n", elem);
		msbits_fill_element(elem, &msbits);
		elem_history[level]=elem;
		printf("bf: after adopt element: msbits:\n");
		print_bits_64(msbits);
		msbits_subtractive_fill_all(&msbits);
		for(i=0; i<(long int)ntales; i++){
			if(tale_index_if_adoptable_to_msbits(tale_index[i], msbits)){
				printf("bf: applying tale[%ld]: ", i);
				tale_print(tale[i]);
				printf("bb: the tale_index[%ld]:\n", i);
				print_bits_64(tale_index[i]);
				msbits_adopt_tale_index(tale_index[i], &msbits);
				/*weight_subtract_by_tale_index(tale_index[i], weight);*/
				printf("bf: after adopting: msbits:\n");
				print_bits_64(msbits);
				i=-1;
			}
			if(msbits_subtractive_fill_all(&msbits)){
				i=-1;
			}
		}
		if((!msbits_if_filled_all(msbits))&&(level+1<min_bf_count-1)){
			bf(level+1);
		}else{
			printf("bf: reached the bottom(level=%d)\n", level);
			if(min_bf_count-1>level+1){
				printf("bf: accepted\n");
				min_bf_count=level+1;
				printf("bf: current min_bf_count: %d\n", min_bf_count);
				printf("bf: the elem history:\n");
				bf_history_output(elem_history);
				bf_history_cp(history_best, elem_history);
			}else{
				printf("bf: rejected(min_bf_count:%d, level:%d\n", min_bf_count, level);
			}
		}
		msbits_cp(&msbits, m_orig);
	}

	return;
}

void bf_history_output(int *h)
{
	int i;

	for(i=0; i<min_bf_count; i++)
		printf("%d%c", h[i], i!=min_bf_count-1?' ':'\n');

	return;
}

void bf_history_cp(int *dst, int *src)
{
	memcpy(dst, src, (X*X)*sizeof(int));

	return;
}
