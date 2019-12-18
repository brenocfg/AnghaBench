#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  fd; TYPE_1__* cache; scalar_t__ windows; } ;
struct TYPE_9__ {int /*<<< orphan*/  fds; } ;
typedef  TYPE_2__ MMapFileDescriptor ;
typedef  TYPE_2__ MMapCache ;

/* Variables and functions */
 int /*<<< orphan*/  FD_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmap_cache_process_sigbus (TYPE_2__*) ; 
 int /*<<< orphan*/  window_free (scalar_t__) ; 

void mmap_cache_free_fd(MMapCache *m, MMapFileDescriptor *f) {
        assert(m);
        assert(f);

        /* Make sure that any queued SIGBUS are first dispatched, so
         * that we don't end up with a SIGBUS entry we cannot relate
         * to any existing memory map */

        mmap_cache_process_sigbus(m);

        while (f->windows)
                window_free(f->windows);

        if (f->cache)
                assert_se(hashmap_remove(f->cache->fds, FD_TO_PTR(f->fd)));

        free(f);
}