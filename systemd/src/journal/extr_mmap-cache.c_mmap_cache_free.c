#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ unused; int /*<<< orphan*/  fds; scalar_t__* contexts; } ;
typedef  TYPE_1__ MMapCache ;

/* Variables and functions */
 int MMAP_CACHE_MAX_CONTEXTS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  context_free (scalar_t__) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  window_free (scalar_t__) ; 

__attribute__((used)) static MMapCache *mmap_cache_free(MMapCache *m) {
        int i;

        assert(m);

        for (i = 0; i < MMAP_CACHE_MAX_CONTEXTS; i++)
                if (m->contexts[i])
                        context_free(m->contexts[i]);

        hashmap_free(m->fds);

        while (m->unused)
                window_free(m->unused);

        return mfree(m);
}