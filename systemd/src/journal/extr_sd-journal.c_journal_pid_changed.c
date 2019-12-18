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
struct TYPE_4__ {scalar_t__ original_pid; } ;
typedef  TYPE_1__ sd_journal ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ getpid_cached () ; 

__attribute__((used)) static bool journal_pid_changed(sd_journal *j) {
        assert(j);

        /* We don't support people creating a journal object and
         * keeping it around over a fork(). Let's complain. */

        return j->original_pid != getpid_cached();
}