#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pool {size_t current_used; int /*<<< orphan*/ * header; int /*<<< orphan*/ * current; } ;

/* Variables and functions */
 size_t CHUNK_SIZE ; 
 void* pool_newchunk (struct pool*,size_t) ; 

__attribute__((used)) static void *
pool_alloc(struct pool *p, size_t sz) {
	// align by 8
	sz = (sz + 7) & ~7;
	if (sz >= CHUNK_SIZE) {
		return pool_newchunk(p, sz);
	}
	if (p->current == NULL) {
		if (pool_newchunk(p, CHUNK_SIZE) == NULL)
			return NULL;
		p->current = p->header;
	}
	if (sz + p->current_used <= CHUNK_SIZE) {
		void * ret = (char *)(p->current+1) + p->current_used;
		p->current_used += sz;
		return ret;
	}

	if (sz >= p->current_used) {
		return pool_newchunk(p, sz);
	} else {
		void * ret = pool_newchunk(p, CHUNK_SIZE);
		p->current = p->header;
		p->current_used = sz;
		return ret;
	}
}