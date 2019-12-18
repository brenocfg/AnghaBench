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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_4__ {scalar_t__ n_groups; scalar_t__ lru_tail; } ;
typedef  TYPE_1__ JournalRateLimit ;

/* Variables and functions */
 scalar_t__ GROUPS_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ journal_ratelimit_group_expired (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_ratelimit_group_free (scalar_t__) ; 

__attribute__((used)) static void journal_ratelimit_vacuum(JournalRateLimit *r, usec_t ts) {
        assert(r);

        /* Makes room for at least one new item, but drop all
         * expored items too. */

        while (r->n_groups >= GROUPS_MAX ||
               (r->lru_tail && journal_ratelimit_group_expired(r->lru_tail, ts)))
                journal_ratelimit_group_free(r->lru_tail);
}