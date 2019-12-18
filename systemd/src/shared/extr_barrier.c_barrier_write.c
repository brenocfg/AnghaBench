#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {scalar_t__ me; void* barriers; int /*<<< orphan*/  pipe; } ;
typedef  TYPE_1__ Barrier ;

/* Variables and functions */
 scalar_t__ BARRIER_ABORTION ; 
 void* BARRIER_I_ABORTED ; 
 void* BARRIER_WE_ABORTED ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINTR ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ barrier_i_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  barrier_is_aborted (TYPE_1__*) ; 
 scalar_t__ barrier_they_aborted (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 
 int write (scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static bool barrier_write(Barrier *b, uint64_t buf) {
        ssize_t len;

        /* prevent new sync-points if we already aborted */
        if (barrier_i_aborted(b))
                return false;

        assert(b->me >= 0);
        do {
                len = write(b->me, &buf, sizeof(buf));
        } while (len < 0 && IN_SET(errno, EAGAIN, EINTR));

        if (len != sizeof(buf))
                goto error;

        /* lock if we aborted */
        if (buf >= (uint64_t)BARRIER_ABORTION) {
                if (barrier_they_aborted(b))
                        b->barriers = BARRIER_WE_ABORTED;
                else
                        b->barriers = BARRIER_I_ABORTED;
        } else if (!barrier_is_aborted(b))
                b->barriers += buf;

        return !barrier_i_aborted(b);

error:
        /* If there is an unexpected error, we have to make this fatal. There
         * is no way we can recover from sync-errors. Therefore, we close the
         * pipe-ends and treat this as abortion. The other end will notice the
         * pipe-close and treat it as abortion, too. */

        safe_close_pair(b->pipe);
        b->barriers = BARRIER_WE_ABORTED;
        return false;
}