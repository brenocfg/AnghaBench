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
typedef  int /*<<< orphan*/  FDSet ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_TO_FD (void*) ; 
 int /*<<< orphan*/  close_nointr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 void* set_steal_first (int /*<<< orphan*/ ) ; 

void fdset_close(FDSet *s) {
        void *p;

        while ((p = set_steal_first(MAKE_SET(s)))) {
                /* Valgrind's fd might have ended up in this set here, due to fdset_new_fill(). We'll ignore
                 * all failures here, so that the EBADFD that valgrind will return us on close() doesn't
                 * influence us */

                /* When reloading duplicates of the private bus connection fds and suchlike are closed here,
                 * which has no effect at all, since they are only duplicates. So don't be surprised about
                 * these log messages. */

                log_debug("Closing set fd %i", PTR_TO_FD(p));
                (void) close_nointr(PTR_TO_FD(p));
        }
}