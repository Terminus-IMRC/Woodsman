#include "common.h"
#include "X.h"
#include "tale.h"
#include "tale_draft.h"

tale_draft_chain_t *tale_draft_chain;
tale_draft_chain_t *tale_draft_chain_orig;

void tale_draft_init();
void tale_draft_finalize();
tale_draft_chain_t* tale_draft_chain_alloc();
void tale_draft_chain_destroy(tale_draft_chain_t *p);
void tale_draft_chain_append_entry(tale_draft_chain_t *p);
void str_to_tale(int *t, char *str);
size_t probe_tale_draft_chain_len();
void tale_draft_chain_to_tale();

void tale_draft_init()
{
	tale_draft_chain=NULL;
	tale_draft_chain_orig=NULL;

	return;
}

void tale_draft_finalize()
{
	return;
}

tale_draft_chain_t* tale_draft_chain_alloc()
{
	tale_draft_chain_t *p;

	p=(tale_draft_chain_t*)malloc(sizeof(tale_draft_chain_t));
	assert(p);

	p->t=(int*)malloc(((X*X)*sizeof(int)));
	assert(p->t);

	p->next=NULL;

	return p;
}

void tale_draft_chain_destroy(tale_draft_chain_t *p)
{
	free(p->t);
	free(p);

	return;
}

void tale_draft_chain_append_entry(tale_draft_chain_t *p)
{
	if(!tale_draft_chain)
		tale_draft_chain_orig=p;
	else
		tale_draft_chain->next=p;
	tale_draft_chain=p;

	return;
}

void str_to_tale(int *t, char *str)
{
        int i;

        for(i=0; i<X*X; i++, str++){
                /* isdigit() may be macros so *str should not be *str++ */
                while((str) && (!isdigit(*str)))
                        str++;

                t[i]=(int)atoi(str);
        }

        return;
}

size_t probe_tale_draft_chain_len()
{
	size_t count=1;
	tale_draft_chain_t *p=tale_draft_chain_orig;

	while((p=p->next))
		count++;
	
	return count;
}

void tale_draft_chain_to_tale()
{
	int i;

	tale_draft_chain_t *p;
	tale_element_t t1;

	ntales=probe_tale_draft_chain_len();
	tale_alloc();

	t1=tale_1dim;

        while(tale_draft_chain_orig){
                for(i=0; i<X*X; i++)
                        *t1++=tale_draft_chain_orig->t[i];
                p=tale_draft_chain_orig;
                tale_draft_chain_orig=tale_draft_chain_orig->next;
                tale_draft_chain_destroy(p);
        }

        return;
}
