#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ offline_state; int /*<<< orphan*/  cache_fd; int /*<<< orphan*/  mmap; int /*<<< orphan*/  offline_thread; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ OFFLINE_JOINED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ mmap_cache_got_sigbus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int journal_file_set_offline_thread_join(JournalFile *f) {
        int r;

        assert(f);

        if (f->offline_state == OFFLINE_JOINED)
                return 0;

        r = pthread_join(f->offline_thread, NULL);
        if (r)
                return -r;

        f->offline_state = OFFLINE_JOINED;

        if (mmap_cache_got_sigbus(f->mmap, f->cache_fd))
                return -EIO;

        return 0;
}