#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int in_unused; int /*<<< orphan*/  keep_always; int /*<<< orphan*/  contexts; } ;
typedef  TYPE_2__ Window ;
struct TYPE_12__ {TYPE_1__* cache; int /*<<< orphan*/  window; } ;
struct TYPE_10__ {TYPE_2__* last_unused; int /*<<< orphan*/  unused; } ;
typedef  TYPE_3__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* TAKE_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  by_window ; 
 int /*<<< orphan*/  unused ; 
 int /*<<< orphan*/  window_free (TYPE_2__*) ; 

__attribute__((used)) static void context_detach_window(Context *c) {
        Window *w;

        assert(c);

        if (!c->window)
                return;

        w = TAKE_PTR(c->window);
        LIST_REMOVE(by_window, w->contexts, c);

        if (!w->contexts && !w->keep_always) {
                /* Not used anymore? */
#if ENABLE_DEBUG_MMAP_CACHE
                /* Unmap unused windows immediately to expose use-after-unmap
                 * by SIGSEGV. */
                window_free(w);
#else
                LIST_PREPEND(unused, c->cache->unused, w);
                if (!c->cache->last_unused)
                        c->cache->last_unused = w;

                w->in_unused = true;
#endif
        }
}