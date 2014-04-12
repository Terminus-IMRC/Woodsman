#include "common.h"
#include "X.h"
#include "weight.h"
#include "will_and_die.h"

weight_t weight;

void weight_init();
void weight_finalize();
void weight_alloc();
void weight_destroy();
void weight_make();
long int weight_most_heavy_element(weight_t weight, msbits_t m);
void weight_subtract_by_tale_index(uint64_t ti, weight_t weight);

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
		will_and_die(errmsg, 1);
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

#pragma omp parallel for private(j,t)
	for(i=0; i<ntales; i++){
		t=tale_index[i];
		for(j=X*X-1; j>=0; j--){
			if(t&((uint64_t)1)){
#pragma omp atomic
				weight[j]++;
			}
			t>>=1;
		}
	}

	return;
}

long int weight_most_heavy_element(weight_t weight, msbits_t m)
{
	int i;
	long int most_heavy_element=-1;
	weight_element_t most_heavy_value=0;

	for(i=0; i<X*X; i++){
		if((!(m&((uint64_t)1<<(X*X-i-1)))) && weight[i]>most_heavy_value){
			most_heavy_element=i;
			most_heavy_value=weight[i];
		}
	}

	assert(most_heavy_element!=-1);

	return most_heavy_element;
}

void weight_subtract_by_tale_index(uint64_t ti, weight_t weight)
{
	int i;

	for(i=0; i<X*X; i++, ti>>=1)
		if(ti&((uint64_t)1))
			weight[i]--;
	
	return;
}

void weight_print(weight_t weight)
{
	int i;

	for(i=0; i<X*X; i++)
		printf("%ld%c", weight[i], i!=X*X-1?' ':'\n');

	return;
}
