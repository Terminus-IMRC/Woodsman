#include "common.h"
#include "weight.h"

weight_t weight;

void weight_init();
void weight_finalize();
void weight_alloc();
void weight_destroy();
void weight_make();

void weight_init()
{
	weight_alloc();
	weight_make();

	return;
}

void weight_finalize()
{
	weight_destroy();

	return;
}

void weight_alloc()
{
	char errmsg[0xffff];

	weight=(weight_t)calloc(X*X, sizeof(weight_element_t));
	if(!weight){
		sprintf(errmsg, "weight_init: calloc: %s", strerror(errno));
		will_and_die(errmsg);
	}

	return;
}

void weight_destroy()
{
	free(weight);

	return;
}

void weight_make()
{
	int i, j;
	uint64_t t;

	for(i=0; i<ntale; i++){
		t=tale_index[i];
		for(j=X*X-1; j>=0; j--){
			if(t&((uint64_t)1)){
				weight[j]++;
			}
			t>>=1;
		}
	}

	return;
}
