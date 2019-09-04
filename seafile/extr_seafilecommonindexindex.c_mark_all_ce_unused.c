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
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct TYPE_2__ {int ce_flags; } ;

/* Variables and functions */
 int CE_ADDED ; 
 int CE_NEW_SKIP_WORKTREE ; 
 int CE_UNPACKED ; 

void mark_all_ce_unused(struct index_state *index)
{
    int i;
    for (i = 0; i < index->cache_nr; i++)
        index->cache[i]->ce_flags &= ~(CE_UNPACKED | CE_ADDED | CE_NEW_SKIP_WORKTREE);
}