#include "common.h"
#include "bf.h"

int min_bf_count;
bf_history_t *bf_history, *bf_history_best;

void bf_init();
void bf(int level);

void bf_init()
{
	int i;

	min_bf_count=X*X;
	bf_history=(bf_history_t*)malloc((X*X)*sizeof(bf_history_t));
	assert(bf_history);
	bf_history_best=(bf_history_t*)malloc((X*X)*sizeof(bf_history_t));
	assert(bf_history_best);

	for(i=0; i<X*X; i++){
		bf_history[i].num_tale_num=0;
		/* at most ceil((double)(X*X)/2 tales because 1 tale must have at least 2 sets */
		bf_history[i].tale_num=(long int*)malloc(ceil((double)(X*X)/2)*sizeof(long int));
		assert(bf_history[i].tale_num);
		bf_history_best[i].tale_num=(long int*)malloc(((X*X)/2)*sizeof(long int));
		assert(bf_history_best[i].tale_num);
	}

	return;
}

void bf_history_part_clean(bf_history_t *t)
{
	t->id=(bf_history_id_t)0;
	t->m=(uint64_t)0;
	t->num_tale_num=0;

	return;
}

void bf(int level)
{
	int elem;
	long int i;
	uint64_t m_orig;
	uint64_t ret_tmp;

	msbits_cp(&m_orig, msbits);

	for(elem=level!=0?bf_history[level-1].bf_elem+1:0; elem<X*X; elem++){
		bf_history_part_clean(&bf_history[level]);
		printf("bf: bruteforce element: %d\n", elem);
		msbits_fill_element(elem, &msbits);
		bf_history[level].id|=BHI_BF;
		bf_history[level].bf_elem=elem;
		printf("bf: after adopt element: msbits:\n");
		print_bits_64(msbits);
		ret_tmp=msbits_subtractive_fill_all(&msbits);
		if(ret_tmp){
			bf_history[level].id|=BHI_SFILL;
			bf_history[level].m|=ret_tmp;
		}
		for(i=0; i<(long int)ntales; i++){
			if(tale_index_if_adoptable_to_msbits(tale_index[i], msbits)){
				printf("bf: applying tale[%ld]: ", i);
				tale_print(tale[i]);
				bf_history[level].id|=BHI_TALE;
				bf_history[level].tale_num[bf_history[level].num_tale_num++]=i;
				printf("bb: the tale_index[%ld]:\n", i);
				print_bits_64(tale_index[i]);
				msbits_adopt_tale_index(tale_index[i], &msbits);
				/*weight_subtract_by_tale_index(tale_index[i], weight);*/
				printf("bf: after adopting: msbits:\n");
				print_bits_64(msbits);
				i=-1;
			}
			if((ret_tmp=msbits_subtractive_fill_all(&msbits))){
				i=-1;
				bf_history[level].id|=BHI_SFILL;
				bf_history[level].m|=ret_tmp;
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
				bf_history_output(bf_history, tale, min_bf_count);
				bf_history_cp(bf_history_best, bf_history, min_bf_count);
			}else{
				printf("bf: rejected(min_bf_count:%d, level:%d\n", min_bf_count, level);
			}
		}
		msbits_cp(&msbits, m_orig);
	}

	return;
}

void bf_history_output(bf_history_t *h, tale_t t, int min)
{
	int i, j;

	for(i=0; i<min; i++){
		printf("id[%d]:", i);
		if(h[i].id & BHI_BF)
			printf(" BHI_BF");
		if(h[i].id & BHI_SFILL)
			printf(" BHI_SFILL");
		if(h[i].id & BHI_TALE)
			printf(" BHI_TALE");
		putchar('\n');

		if(h[i].id & BHI_BF)
			printf("bf_elem[%d]: %d\n", i, h[i].bf_elem);
		if(h[i].id & BHI_SFILL){
			printf("m[%d]:\n", i);
			print_bits_64(h[i].m);
		}
		if(h[i].id & BHI_TALE){
			printf("num_tale_num[%d]: %ld\n", i, h[i].num_tale_num);
			printf("tale_num[%d]#%ld:", i, h[i].num_tale_num);
			for(j=0; j<h[i].num_tale_num; j++){
				printf(" %ld: ", h[i].tale_num[j]);
				tale_print(t[h[i].tale_num[j]]);
			}
		}
	}

	return;
}

void bf_history_cp(bf_history_t *dst, bf_history_t *src, int n)
{
	int i;

	for(i=0; i<n; i++){
		dst[i].id=src[i].id;
		if(src[i].id | BHI_BF)
			dst[i].bf_elem=src[i].bf_elem;
		if(src[i].id | BHI_SFILL)
			dst[i].m=src[i].m;
		if(src[i].id | BHI_TALE){
			dst[i].num_tale_num=src[i].num_tale_num;
			memcpy(dst[i].tale_num, src[i].tale_num, src[i].num_tale_num*sizeof(long int));
		}
	}

	return;
}
