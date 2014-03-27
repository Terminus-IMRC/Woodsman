#ifndef __TALE_DRAFT_H_INSIDE__
#define __TALE_DRAFT_H_INSIDE__

#include <math.h>
#include <stdlib.h>
#include <ctype.h>

	struct tale_draft_chain_t{
		struct tale_draft_chain_t *next;
		int *t;
	};
	typedef struct tale_draft_chain_t tale_draft_chain_t;

	extern tale_draft_chain_t *tale_draft_chain;
	extern tale_draft_chain_t *tale_draft_chain_orig;

	void tale_draft_init();
	void tale_draft_finalize();
	tale_draft_chain_t* tale_draft_chain_alloc();
	void tale_draft_chain_destroy(tale_draft_chain_t *p);
	void tale_draft_chain_append_entry(tale_draft_chain_t *p);
	void str_to_tale(int *t, char *str);
	size_t probe_tale_draft_chain_len();
	void tale_draft_chain_to_tale();

#endif /* __TALE_DRAFT_H_INSIDE__ */
