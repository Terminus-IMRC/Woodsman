#include "common.h"
#include "tale_index.h"

tale_index_t *tale_index;

void tale_index_init();
void tale_index_finalize();
void tale_index_alloc();
void tale_index_destroy();
void tale_index_make();

void tale_index_init()
{
	tale_index_alloc();
	tale_index_make();

	return;
}

void tale_index_finalize()
{
	tale_index_destroy();

	return;
}

void tale_index_alloc()
{
	int i;

	tale_index=(tale_index_t)calloc(ntales, sizeof(uint64_t));
	assert(tale_index);

	return;
}

void tale_index_destroy()
{
	free(tale_index);

	return;
}

void tale_index_make()
{
	int i, j;

	for(i=0; i<ntales; i++){
		for(j=0; j<X*X; j++){
			tale_index[i]<<=1;
			if(tale[i][j]){
				tale_index[i]|=(uint64_t)1;
			}
		}
	}

	return;
}
