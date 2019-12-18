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
struct TYPE_4__ {scalar_t__ out_buffer_full; int /*<<< orphan*/  master; scalar_t__ master_readable; } ;
typedef  TYPE_1__ PTYForward ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCINQ ; 
 int /*<<< orphan*/  TIOCOUTQ ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  log_debug_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool drained(PTYForward *f) {
        int q = 0;

        assert(f);

        if (f->out_buffer_full > 0)
                return false;

        if (f->master_readable)
                return false;

        if (ioctl(f->master, TIOCINQ, &q) < 0)
                log_debug_errno(errno, "TIOCINQ failed on master: %m");
        else if (q > 0)
                return false;

        if (ioctl(f->master, TIOCOUTQ, &q) < 0)
                log_debug_errno(errno, "TIOCOUTQ failed on master: %m");
        else if (q > 0)
                return false;

        return true;
}