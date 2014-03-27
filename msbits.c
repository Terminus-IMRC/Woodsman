#include "common.h"
#include "X.h"
#include "msbits.h"

msbits_t msbits;

static uint64_t *subtraction_base_vert;
static uint64_t *subtraction_base_hriz;
static uint64_t *subtraction_base_diag;
void msbits_subtractive_fill_init();
_Bool msbits_subtractive_fill_all(msbits_t *m);

void msbits_init()
{
	msbits=(msbits_t)0;
	msbits_subtractive_fill_init();

	return;
}

void msbits_subtractive_fill_init()
{
	int i;
	uint64_t tmp_vert=0, tmp_hriz=0;

	subtraction_base_vert=(uint64_t*)calloc(X, sizeof(uint64_t));
	assert(subtraction_base_vert);
	subtraction_base_hriz=(uint64_t*)calloc(X, sizeof(uint64_t));
	assert(subtraction_base_hriz);
	subtraction_base_diag=(uint64_t*)calloc(2, sizeof(uint64_t));
	assert(subtraction_base_diag);

	for(i=0; i<X; i++){
		tmp_vert<<=X;
		tmp_vert|=(uint64_t)1;
		tmp_hriz<<=1;
		tmp_hriz|=(uint64_t)1;
	}

	for(i=0; i<X; i++){
		subtraction_base_vert[i]=tmp_vert<<(X-i-1);
		subtraction_base_hriz[i]=tmp_hriz<<(i*X);
	}

	for(i=0; i<X; i++){
		subtraction_base_diag[0]<<=(X+1);
		subtraction_base_diag[0]|=(uint64_t)1;
		subtraction_base_diag[1]<<=(X-1);
		subtraction_base_diag[1]|=(uint64_t)1;
	}
	subtraction_base_diag[1]<<=(X-1);

	return;
}

void msbits_finalize()
{
	return;
}

void msbits_fill_element(int elem, msbits_t *m)
{
	(*m)|=(msbits_t)1<<(elem);

	return;
}

void msbits_adopt_tale_index(uint64_t ti, msbits_t *m)
{
	(*m)|=ti;

	return;
}

_Bool msbits_subtractive_fill_all(msbits_t *m)
{
	int i;
	_Bool if_filled=0;

	for(;; if_filled=1){
		for(i=0; i<X; i++){
			if(tale_index_if_adoptable_to_msbits(subtraction_base_vert[i], (*m))){
				(*m)|=subtraction_base_vert[i];
				goto contloop;
			}
			if(tale_index_if_adoptable_to_msbits(subtraction_base_hriz[i], (*m))){
				(*m)|=subtraction_base_hriz[i];
				goto contloop;
			}
		}
		for(i=0; i<2; i++){
			if(tale_index_if_adoptable_to_msbits(subtraction_base_diag[i], (*m))){
				(*m)|=subtraction_base_diag[i];
				goto contloop;
			}
		}
contloop:	continue;
	}

	return if_filled;
}
