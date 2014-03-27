#include "common.h"
#include "X.h"
#include "tale.h"
#include "tale_draft.h"
#include "tale_index.h"
#include "string_utils.h"
#include <stdio.h>

long int ntales;
tale_element_t tale_1dim;
tale_t tale;

void tale_init();
void tale_finalize();
void tale_destroy(tale_t t);
void tale_read();
void tale_alloc();

void tale_init()
{
	return;
}

void tale_finalize()
{
	return;
}

void tale_destroy(tale_t t)
{
	free(t);

	return;
}

void tale_read()
{
	char str[0xffff];
	tale_draft_chain_t *td;

	fgets(str, 0xffff, stdin);
	/*TODO:if ((int)sqrt(Ceilings))**2!=Ceilings then say error*/
	Ceilings=count_number_of_elements_in_string(str);
	X=sqrt(Ceilings);

	do{
		td=tale_draft_chain_alloc();
		str_to_tale(td->t, str);
		tale_draft_chain_append_entry(td);
		fgets(str, 0xffff, stdin);
	}while(!feof(stdin));

	tale_draft_chain_to_tale();

	return;
}

/* note that this function must be called after ntales is set */
void tale_alloc()
{
	int i;

	tale_1dim=(int*)malloc((X*X)*ntales*sizeof(int));
	assert(tale_1dim);
	tale=(tale_t)malloc(ntales*sizeof(tale_element_t));
	assert(tale);

	for(i=0; i<ntales; i++)
		tale[i]=tale_1dim+i*(X*X);

	return;
}
