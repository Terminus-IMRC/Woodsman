#include "common.h"
#include "X.h"
#include "msbits.h"

msbits_t msbits;

static uint64_t *subtraction_base_vert;
static uint64_t *subtraction_base_hriz;
static uint64_t *subtraction_base_diag;
void msbits_subtractive_fill_init();
uint64_t msbits_subtractive_fill_all(msbits_t *m);

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
	tmp_hriz<<=X*X-X;

	for(i=0; i<X; i++){
		subtraction_base_vert[i]=tmp_vert<<(X-i-1);
		subtraction_base_hriz[i]=tmp_hriz>>(i*X);
	}

	for(i=0; i<X; i++){
		subtraction_base_diag[0]<<=(X+1);
		subtraction_base_diag[0]|=(uint64_t)1;
		subtraction_base_diag[1]<<=(X-1);
		subtraction_base_diag[1]|=(uint64_t)1;
	}
	subtraction_base_diag[1]<<=(X-1);

	for(i=0; i<X; i++){
		dpf("msbits_subtractive_fill_init: vert[%d]:\n", i);
		dprint_bits_64(subtraction_base_vert[i]);
	}
	for(i=0; i<X; i++){
		dpf("msbits_subtractive_fill_init: hriz[%d]:\n", i);
		dprint_bits_64(subtraction_base_hriz[i]);
	}
	for(i=0; i<2; i++){
		dpf("msbits_subtractive_fill_init: diag[%d]:\n", i);
		dprint_bits_64(subtraction_base_diag[i]);
	}

	return;
}

void msbits_finalize()
{
	return;
}

uint64_t msbits_subtractive_fill_all(msbits_t *m)
{
	int i;
	uint64_t ret=0;

	dpf("msbits_subtactive_fill_all: passed msbits: ");
	dprint_bits_64(*m);
	for(;;){
		for(i=0; i<X; i++){
			if(substraction_base_if_adoptable_to_msbits(subtraction_base_vert[i], (*m))){
				dpf("msbits_subtractive: applying vert[%d]\n", i);
				(*m)|=subtraction_base_vert[i];
				ret|=(uint64_t)1<<(X-i-1);
				goto contloop;
			}
			if(substraction_base_if_adoptable_to_msbits(subtraction_base_hriz[i], (*m))){
				dpf("msbits_subtractive: applying hriz[%d]\n", i);
				(*m)|=subtraction_base_hriz[i];
				ret|=(uint64_t)1<<(X+(X-i-1));
				goto contloop;
			}
		}
		for(i=0; i<2; i++){
			if(substraction_base_if_adoptable_to_msbits(subtraction_base_diag[i], (*m))){
				dpf("msbits_subtractive: applying diag[%d]\n", i);
				(*m)|=subtraction_base_diag[i];
				ret|=(uint64_t)1<<(2*X+(X-i-1));
				goto contloop;
			}
		}
		break;
contloop:	continue;
	}

	return ret;
}
