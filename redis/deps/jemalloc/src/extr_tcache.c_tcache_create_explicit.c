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
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 int /*<<< orphan*/  CACHELINE ; 
 size_t PTR_CEILING (size_t) ; 
 int /*<<< orphan*/  TSDN_NULL ; 
 int /*<<< orphan*/  arena_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arena_ichoose (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ipallocztm (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int stack_nelms ; 
 size_t sz_sa2u (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcache_arena_associate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  tsd_tsdn (int /*<<< orphan*/ *) ; 

tcache_t *
tcache_create_explicit(tsd_t *tsd) {
	tcache_t *tcache;
	size_t size, stack_offset;

	size = sizeof(tcache_t);
	/* Naturally align the pointer stacks. */
	size = PTR_CEILING(size);
	stack_offset = size;
	size += stack_nelms * sizeof(void *);
	/* Avoid false cacheline sharing. */
	size = sz_sa2u(size, CACHELINE);

	tcache = ipallocztm(tsd_tsdn(tsd), size, CACHELINE, true, NULL, true,
	    arena_get(TSDN_NULL, 0, true));
	if (tcache == NULL) {
		return NULL;
	}

	tcache_init(tsd, tcache,
	    (void *)((uintptr_t)tcache + (uintptr_t)stack_offset));
	tcache_arena_associate(tsd_tsdn(tsd), tcache, arena_ichoose(tsd, NULL));

	return tcache;
}