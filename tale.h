#ifndef __TALE_H_INSIDE__
#define __TALE_H_INSIDE__

	typedef int* tale_element_t;
	typedef tale_element_t* tale_t;

	extern size_t ntale;
	extern tale_t tale;

	void tale_init();
	void tale_finalize();
	void tale_destroy(tale_t t);
	void tale_read();
	void tale_alloc();

#endif /* __TALE_H_INSIDE__ */
