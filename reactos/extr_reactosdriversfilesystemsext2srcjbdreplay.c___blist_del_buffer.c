#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct journal_head {TYPE_1__* b_tprev; struct journal_head* b_tnext; } ;
struct TYPE_2__ {struct journal_head* b_tnext; } ;

/* Variables and functions */

__attribute__((used)) static inline void
__blist_del_buffer(struct journal_head **list, struct journal_head *jh)
{
    if (*list == jh) {
        *list = jh->b_tnext;
        if (*list == jh)
            *list = NULL;
    }
    jh->b_tprev->b_tnext = jh->b_tnext;
    jh->b_tnext->b_tprev = jh->b_tprev;
}