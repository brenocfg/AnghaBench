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
struct index_state {int cache_nr; int /*<<< orphan*/ * cache; } ;

/* Variables and functions */
 scalar_t__ ce_stage (int /*<<< orphan*/ ) ; 

int unmerged_index(const struct index_state *istate)
{
    int i;
    for (i = 0; i < istate->cache_nr; i++) {
        if (ce_stage(istate->cache[i]))
            return 1;
    }
    return 0;
}